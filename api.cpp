#include <cstdlib>
#include <cstring>
#include <iostream>

#include <boost/asio.hpp>

#include "client/http_client.h"
#include "server/task/executor.h"

int main(int argc, char* argv[]) {
    HttpClient client;
    client.Send("Are you fine?");
    TExecutor executor;
    executor.Run("ls ~/Downloads");
    std::cout << executor.Stdout;
}
