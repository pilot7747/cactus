//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_HEADER_HPP
#define CACTUS_HEADER_HPP

#include <string>

namespace HTTP {
    namespace HttpServer {

        struct header
        {
            std::string name;
            std::string value;
        };

    } // namespace Server
} // namespace http

#endif //CACTUS_HEADER_HPP
