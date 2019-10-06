//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_CONNECTION_MANAGER_HPP
#define CACTUS_CONNECTION_MANAGER_HPP

#include <set>
#include "connection.hpp"
#include "master/master.h"

namespace HTTP {
    namespace HttpServer {

/// Manages open connections so that they may be cleanly stopped when the server
/// needs to shut down.
        class TConnectionManager
        {
        public:
            TConnectionManager(const TConnectionManager&) = delete;
            TConnectionManager& operator=(const TConnectionManager&) = delete;

            /// Construct a connection manager.
            TConnectionManager();
            TConnectionManager(TMaster* master) : MasterPtr(master) {}

            /// Add the specified connection to the manager and start it.
            void Start(TConnectionPtr c);

            /// Stop the specified connection.
            void Stop(TConnectionPtr c);

            /// Stop all connections.
            void StopAll();

        private:
            /// The managed connections.
            std::set<TConnectionPtr> Connections;
            TMaster* MasterPtr;
        };

    } // namespace Server
} // namespace http

#endif //CACTUS_CONNECTION_MANAGER_HPP
