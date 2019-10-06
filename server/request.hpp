//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_REQUEST_HPP
#define CACTUS_REQUEST_HPP
#include <string>
#include <vector>
#include "header.hpp"

namespace HTTP {
    namespace HttpServer {

/// A request received from a client.
        struct TRequest
        {
            std::string method;
            std::string uri;
            int http_version_major;
            int http_version_minor;
            std::vector<header> headers;
        };

    } // namespace Server
} // namespace http

#endif //CACTUS_REQUEST_HPP
