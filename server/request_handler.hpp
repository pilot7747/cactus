//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_REQUEST_HANDLER_HPP
#define CACTUS_REQUEST_HANDLER_HPP

#include <string>

namespace HTTP {
    namespace HttpServer {

        struct TReply;
        struct TRequest;

/// The common handler for all incoming requests.
        class TRequestHandler
        {
        public:
            TRequestHandler(const TRequestHandler&) = delete;
            TRequestHandler& operator=(const TRequestHandler&) = delete;

            /// Construct with a directory containing files to be served.
            explicit TRequestHandler(const std::string& doc_root);

            /// Handle a request and produce a reply.
            void HandleRequest(const TRequest &req, TReply &rep);

        private:
            /// The directory containing the files to be served.
            std::string DocRoot;

            /// Perform URL-decoding on a string. Returns false if the encoding was
            /// invalid.
            static bool UrlDecode(const std::string &in, std::string &out);
        };

    } // namespace Server
} // namespace http
#endif //CACTUS_REQUEST_HANDLER_HPP
