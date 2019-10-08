//
// Created by Nikita Pavlichenko on 2019-08-22.
//

#ifndef CACTUS_HTTP_CLIENT_H
#define CACTUS_HTTP_CLIENT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>

#include "../message/message.h"


using boost::asio::ip::tcp;

enum { max_length = 1024 };


class HttpClient {
public:
    HttpClient(const std::string ip = "0::0", short port = 80)
    : IOContext(), Ip(ip), Port(port), Resolver(IOContext), Socket(IOContext) {
    }

    void Send(const std::string& message) {
        std::cout << "Starting" << std::endl;
        std::ostream requestStream(&Request);
        cactus::CactusMessage cactusMessage;
        cactusMessage.set_message_type(static_cast<int>(MessageType::STATUS));
        cactusMessage.set_content(message);
        requestStream << cactusMessage.SerializeAsString();
        tcp::resolver::iterator iterator = Resolver.resolve(Ip, std::to_string(Port));
        std::cout << "Connecting..\n";
        boost::asio::connect(Socket, iterator);
        std::cout << "Sending..\n";
        boost::asio::write(Socket, Request);
        std::cout << "Reading..\n";
        boost::asio::streambuf::mutable_buffers_type mutableBuffer =
                Responce.prepare(max_length);
        size_t responceSize = Socket.receive(mutableBuffer);
        Responce.commit(responceSize);
        std::cout << "Done!\n";
        std::istream responseStream(&Responce);
        TMessage responseMessage;
        responseMessage.Parse(&responseStream);
        std::cout << responseMessage.Content << std::endl;
    }

private:
    boost::asio::io_context IOContext;
    std::string Ip;
    short Port;
    tcp::resolver Resolver;
    tcp::socket Socket;
    boost::asio::streambuf Request;
    boost::asio::streambuf Responce;
};
#endif //CACTUS_HTTP_CLIENT_H
