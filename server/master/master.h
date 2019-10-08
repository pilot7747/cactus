//
// Created by Nikita Pavlichenko on 2019-08-24.
//

#ifndef CACTUS_MASTER_H
#define CACTUS_MASTER_H

#include <deque>

#include "worker_config_for_master.h"
#include "../../message/message.h"

class TMaster {
public:
    template <class WorkerU>
    void AddWorker(WorkerU&& workerConfig) {
        Workers.push_back(std::forward<WorkerU>(workerConfig));
    }

    TMessage HandleMessange(const TMessage& message, std::string_view clientIt = "") {
        TMessage answer;
        if (message.Message == MessageType::STATUS) {
            answer.Message = MessageType::STATUS;
            answer.Content = "Ok";
        } else if (message.Message == MessageType::ADD_WORKER) {

        }
        return answer;
    }

private:
    std::deque<TWorkerConfigForMaster> Workers;
};
#endif //CACTUS_MASTER_H
