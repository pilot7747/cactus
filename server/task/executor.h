//
// Created by Nikita Pavlichenko on 2019-10-07.
//

#ifndef CACTUS_EXECUTOR_H
#define CACTUS_EXECUTOR_H
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <fstream>

class TExecutor {
public:
    int Run(const std::string& cmd) {
        std::string cmdRedirected = cmd + " > stdout 2> stderr";
        int i, ret = system(cmdRedirected.c_str());
        i = WEXITSTATUS(ret);

        std::ifstream stdout("stdout", std::fstream::in);
        getline(stdout, Stdout, '\0');
        stdout.close();
        std::ifstream stderr("stderr", std::fstream::in);
        getline(stderr, Stderr, '\0');
        stderr.close();
        return i;
    }

    std::string Stdout;
    std::string Stderr;
};
#endif //CACTUS_EXECUTOR_H
