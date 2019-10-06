//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_CONNECTION_HPP
#define CACTUS_CONNECTION_HPP

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include "reply.hpp"
#include "request.hpp"
#include "request_handler.hpp"
#include "request_parser.hpp"
#include "master/master.h"

namespace HTTP {
    namespace HttpServer {

        class TConnectionManager;

/// Represents a single connection from a client.
        class TConnection
                : public std::enable_shared_from_this<TConnection>
        {
        public:
            TConnection(const TConnection&) = delete;
            TConnection& operator=(const TConnection&) = delete;

            /// Construct a connection with the given socket.
            explicit TConnection(boost::asio::ip::tcp::socket socket,
                                TConnectionManager& manager, TRequestHandler& handler, TMaster* master);

            /// Start the first asynchronous operation for the connection.
            void Start();

            /// Stop all asynchronous operations associated with the connection.
            void Stop();

        private:
            /// Perform an asynchronous read operation.
            void DoRead();

            /// Perform an asynchronous write operation.
            void DoWrite();

            /// Socket for the connection.
            boost::asio::ip::tcp::socket Socket;

            /// The manager for this connection.
            TConnectionManager& ConnectionManager;

            /// The handler used to process the incoming request.
            TRequestHandler& RequestHandler;

            /// Buffer for incoming data.
            std::array<char, 8192> Buffer;
            boost::asio::streambuf Streambuf;

            /// The incoming request.
            TRequest Request;

            /// The parser for the incoming request.
            TRequestParser TRequestParser;

            /// The reply to be sent back to the client.
            //TReply Reply;
            TMessage Reply;
            TMaster* MasterPtr;
        };

        typedef std::shared_ptr<TConnection> TConnectionPtr;

    } // namespace Server
} // namespace http


#endif //CACTUS_CONNECTION_HPP
