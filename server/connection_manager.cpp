#include "connection_manager.hpp"

namespace HTTP {
    namespace HttpServer {

        TConnectionManager::TConnectionManager() {
        }

        void TConnectionManager::Start(TConnectionPtr c) {
            Connections.insert(c);
            c->Start();
        }

        void TConnectionManager::Stop(TConnectionPtr c) {
            std::cout << "Stopping connection" << std::endl;
            Connections.erase(c);
            c->Stop();
        }

        void TConnectionManager::StopAll() {
            for (auto&& c : Connections) {
                c->Stop();
            }

            Connections.clear();
        }

    } // namespace Server
} // namespace http