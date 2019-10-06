//
// Created by Nikita Pavlichenko on 2019-08-24.
//

#ifndef CACTUS_WORKER_CONFIG_FOR_MASTER_H
#define CACTUS_WORKER_CONFIG_FOR_MASTER_H

#include <boost/asio.hpp>

struct TWorkerConfigForMaster {
    std::string Ip;
    size_t Performance;
    size_t Memory;
    size_t CpuCores;
    size_t Platform;
    size_t CurrentJobNum;
};
#endif //CACTUS_WORKER_CONFIG_FOR_MASTER_H
