//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_MIME_TYPES_HPP
#define CACTUS_MIME_TYPES_HPP

#include <string>

namespace HTTP {
    namespace HttpServer {
        namespace NMimeTypes {

/// Convert a file extension into a MIME type.
            std::string ExtensionToType(const std::string &extension);

        } // namespace NMimeTypes
    } // namespace Server
} // namespace http

#endif //CACTUS_MIME_TYPES_HPP
