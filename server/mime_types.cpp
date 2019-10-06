#include "mime_types.hpp"

namespace HTTP {
    namespace HttpServer {
        namespace NMimeTypes {

            struct mapping
            {
                const char* extension;
                const char* mime_type;
            } mappings[] =
                    {
                            { "gif", "image/gif" },
                            { "htm", "text/html" },
                            { "html", "text/html" },
                            { "jpg", "image/jpeg" },
                            { "png", "image/png" }
                    };

            std::string ExtensionToType(const std::string &extension)
            {
                for (mapping m: mappings)
                {
                    if (m.extension == extension)
                    {
                        return m.mime_type;
                    }
                }

                return "text/plain";
            }

        } // namespace NMimeTypes
    } // namespace Server
} // namespace http