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
        //boost::asio::read_some(Socket, Responce);
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



    void HandleResolve(const boost::system::error_code& err, const tcp::resolver::results_type& endpoints) {
        std::cout << "Resolving" << std::endl;
        if (!err) {
            // Attempt a connection to each endpoint in the list until we
            // successfully establish a connection.
            boost::asio::async_connect(Socket, endpoints,
                                       boost::bind(&HttpClient::HandleConnect, this,
                                                   boost::asio::placeholders::error));
        } else {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void HandleConnect(const boost::system::error_code& err) {
        std::cout << "Connecting" << std::endl;
        if (!err)
        {
            // The connection was successful. Send the request.
            boost::asio::async_write(Socket, Request,
                                     boost::bind(&HttpClient::HandleWriteRequest, this,
                                                 boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void HandleWriteRequest(const boost::system::error_code& err)
    {
        std::cout << "Sending..." << std::endl;
        if (!err)
        {
            // Read the response status line. The response_ streambuf will
            // automatically grow to accommodate the entire line. The growth may be
            // limited by passing a maximum size to the streambuf constructor.
            std::cout << "Async read" << std::endl;
            boost::asio::async_read(Socket, Responce,
                                          boost::bind(&HttpClient::HandleRead, this,
                                                      boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void HandleRead(const boost::system::error_code& err)
    {
        std::cout << "Reading..." << std::endl;
        if (!err)
        {
            std::cout << "Got responce" << std::endl;
            // Check that response is OK.
                std::istream responseStream(&Responce);
                TMessage message;
                message.Parse(&responseStream);
                std::cout << message.Content << std::endl;
        }
        else
        {
            std::cout << "Error: " << err << "\n";
        }
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
