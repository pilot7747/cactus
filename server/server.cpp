#include "server.hpp"
#include <signal.h>
#include <utility>

namespace HTTP {
    namespace HttpServer {

        Server::Server(const std::string& address, const std::string& port,
                       const std::string& doc_root)
                : IOContext(1),
                  Signals(IOContext),
                  Acceptor(IOContext),
                  ConnectionManager(&Master),
                  RequestHandler(doc_root)
        {
            // Register to handle the signals that indicate when the Server should exit.
            // It is safe to register for the same signal multiple times in a program,
            // provided all registration for the specified signal is made through Asio.
            Signals.add(SIGINT);
            Signals.add(SIGTERM);
#if defined(SIGQUIT)
            Signals.add(SIGQUIT);
#endif // defined(SIGQUIT)

            DoAwaitStop();

            // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
            boost::asio::ip::tcp::resolver resolver(IOContext);
            boost::asio::ip::tcp::endpoint endpoint =
                    *resolver.resolve(address, port).begin();
            Acceptor.open(endpoint.protocol());
            Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            Acceptor.bind(endpoint);
            Acceptor.listen();

            DoAccept();
        }

        void Server::Run()
        {
            // The io_context::run() call will block until all asynchronous operations
            // have finished. While the Server is running, there is always at least one
            // asynchronous operation outstanding: the asynchronous accept call waiting
            // for new incoming connections.
            IOContext.run();
        }

        void Server::DoAccept()
        {
            Acceptor.async_accept(
                    [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
                    {
                        // Check whether the Server was stopped by a signal before this
                        // completion handler had a chance to run.
                        if (!Acceptor.is_open())
                        {
                            return;
                        }

                        if (!ec)
                        {
                            ConnectionManager.Start(std::make_shared<TConnection>(
                                    std::move(socket), ConnectionManager, RequestHandler, &Master));
                        }

                        DoAccept();
                    });
        }

        void Server::DoAwaitStop()
        {
            Signals.async_wait(
                    [this](boost::system::error_code /*ec*/, int /*signo*/)
                    {
                        // The Server is stopped by cancelling all outstanding asynchronous
                        // operations. Once all operations have finished the io_context::run()
                        // call will exit.
                        Acceptor.close();
                        ConnectionManager.StopAll();
                    });
        }

    } // namespace Server
} // namespace http