//
// Created by Nikita Pavlichenko on 2019-08-22.
//

#ifndef CACTUS_HTTP_SERVER_H
#define CACTUS_HTTP_SERVER_H

#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;
using IOService = boost::asio::io_service;

class HttpServer
{
public:
    HttpServer(short port)
            : Service(), Socket(Service, udp::endpoint(udp::v4(), port))
    {
        DoRecieve();
    }

    void Run() {
        Service.run();
    }

private:
    void DoRecieve() {
        Socket.async_receive_from(
                boost::asio::buffer(data_, max_length), SenderEndpoint,
                [this](boost::system::error_code ec, std::size_t bytes_recvd)
                {
                    if (!ec && bytes_recvd > 0) {
                        DoSend(bytes_recvd);
                    } else {
                        DoRecieve();
                    }
                });
    }

    void DoSend(std::size_t length) {
        Socket.async_send_to(
                boost::asio::buffer(data_, length), SenderEndpoint,
                [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
                {
                    DoRecieve();
                });
    }

private:
    IOService Service;
    udp::socket Socket;
    udp::endpoint SenderEndpoint;
    enum { max_length = 1024 };
    char data_[max_length];
};

#endif //CACTUS_HTTP_SERVER_H
