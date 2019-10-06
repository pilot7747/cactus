#include "connection.hpp"
#include <utility>
#include <vector>
#include "connection_manager.hpp"
#include "request_handler.hpp"

#include "../message/message.h"


namespace HTTP {
    namespace HttpServer {

        TConnection::TConnection(boost::asio::ip::tcp::socket socket,
                               TConnectionManager& manager, TRequestHandler& handler, TMaster* master)
                : Socket(std::move(socket)),
                  ConnectionManager(manager),
                  RequestHandler(handler),
                  MasterPtr(master)
        {
        }

        void TConnection::Start()
        {
            DoRead();
        }

        void TConnection::Stop()
        {
            Socket.close();
        }

        void TConnection::DoRead() {
            std::cout << "Reading data" << std::endl;
            auto self(shared_from_this());
            Socket.async_read_some(boost::asio::buffer(Buffer),
                                    [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
                                    {
                                        if (!ec) {
                                            TRequestParser::ResultType result;
                                            TMessage request;
                                            request.Parse(Buffer.data(), bytes_transferred);
                                            Reply = MasterPtr->HandleMessange(request);
                                            std::cout << "Replying: " << Reply.Content << std::endl;
                                            DoWrite();
                                        } else if (ec != boost::asio::error::operation_aborted) {
                                            ConnectionManager.Stop(shared_from_this());
                                        }
                                    });
        }

        void TConnection::DoWrite() {
            std::cout << "Writing data" << std::endl;
            auto self(shared_from_this());
            std::cout << "Replying2: " << Reply.Content << std::endl;
            Reply.ToStreamBuf(&Streambuf);
            std::cout << "Now I'm gonna write" << std::endl;
            std::cout << Streambuf.size() << std::endl;
            boost::asio::async_write(Socket, Streambuf,
                                     [this, self](boost::system::error_code ec, std::size_t)
                                     {
                                         std::cout << "Oh, handled" << std::endl;
                                         if (!ec)
                                         {
                                             std::cout << "No error code\n";
                                             // Initiate graceful connection closure.
                                             boost::system::error_code ignored_ec;
                                             /*Socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                                              ignored_ec);*/
                                         }
                                         else if (ec != boost::asio::error::operation_aborted)
                                         {
                                             std::cout << "Got error code\n";
                                             ConnectionManager.Stop(shared_from_this());
                                         }
                                     });
        }

    } // namespace Server
} // namespace http