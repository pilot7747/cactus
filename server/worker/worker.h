//
// Created by Nikita Pavlichenko on 2019-10-07.
//

#ifndef CACTUS_WORKER_H
#define CACTUS_WORKER_H

#include "../../message/message.pb.h"
#include "../../message/message.h"
#include "../server.hpp"
#include "../task/task.h"

#include <deque>

class TWorker {
public:
    TWorker() = default;

private:
    void RunTasks() {
        while (true) {
            if (!Tasks.empty()) {
                Tasks.front().Run();
                Tasks.pop_front();
            }
        }
    }

    std::deque<TTask> Tasks;

};
#endif //CACTUS_WORKER_H
