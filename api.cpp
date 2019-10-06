#include <cstdlib>
#include <cstring>
#include <iostream>

#include <boost/asio.hpp>

#include "client/http_client.h"

int main(int argc, char* argv[]) {
    HttpClient client;
    client.Send("Are you fine?");
}
