//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_SERVER_HPP
#define CACTUS_SERVER_HPP
#include <boost/asio.hpp>
#include <string>
#include "connection.hpp"
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include "master/master.h"

namespace HTTP {
    namespace HttpServer {

/// The top-level class of the HTTP server.
        class Server
        {
        public:
            Server(const Server&) = delete;
            Server& operator=(const Server&) = delete;

            /// Construct the server to listen on the specified TCP address and port, and
            /// serve up files from the given directory.
            explicit Server(const std::string& address, const std::string& port,
                            const std::string& doc_root);

            /// Run the server's io_context loop.
            void Run();

        private:
            /// Perform an asynchronous accept operation.
            void DoAccept();

            /// Wait for a request to stop the server.
            void DoAwaitStop();

            /// The io_context used to perform asynchronous operations.
            boost::asio::io_context IOContext;

            /// The signal_set is used to register for process termination notifications.
            boost::asio::signal_set Signals;

            /// Acceptor used to listen for incoming connections.
            boost::asio::ip::tcp::acceptor Acceptor;

            TMaster Master;

            /// The connection manager which owns all live connections.
            TConnectionManager ConnectionManager;

            /// The handler for all incoming requests.
            TRequestHandler RequestHandler;

        };

    } // namespace Server
} // namespace http
#endif //CACTUS_SERVER_HPP
