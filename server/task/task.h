//
// Created by Nikita Pavlichenko on 2019-10-07.
//

#ifndef CACTUS_TASK_H
#define CACTUS_TASK_H

#include <string>
#include "executor.h"

class TTask {
public:
    int Run() {
        return Executor.Run(Command);
    }

    std::string GetStdout() const {
        return Executor.Stdout;
    }

    std::string GetStderr() const {
        return Executor.Stderr;
    }

    std::string Command;
private:
    TExecutor Executor;
};
#endif //CACTUS_TASK_H
