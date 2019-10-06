#include <iostream>
#include "server/server.hpp"
//#include "server2/server.h"

int main(int argc, char* argv[]) {
    //HttpServer Server(1489);
    //Server.Run();
    std::string address =  "0::0";
    std::string port = "1488";
    std::string docRoot = "/Users/pavlichenko/Downloads";
    try {
        // Check command line arguments.
        if (argc != 4) {
            std::cerr << "Usage: http_server <address> <port> <doc_root>\n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 0.0.0.0 80 .\n";
            std::cerr << "  For IPv6, try:\n";
            std::cerr << "    receiver 0::0 80 .\n";
            return 1;
        }

        // Initialise the Server.
        HTTP::HttpServer::Server s(argv[1], argv[2], argv[3]);
        s.Run();
    }
    catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << "\n";
    }
    return 0;
}