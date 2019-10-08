//
// Created by Nikita Pavlichenko on 2019-08-23.
//

#ifndef CACTUS_MESSAGE_H
#define CACTUS_MESSAGE_H

#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include "message.pb.h"

enum class MessageType {
    STATUS,
    EXECUTE,
    ADD_WORKER,
    JOB_ERROR,
    JOB_UPDATE_STATUS,
    JOB_COMPLETE,
    MASTER_RESPONCE
};

class TMessage {
public:
    void Parse(const char* data, size_t len) {
        cactus::CactusMessage request;
        request.ParseFromArray(data, len);
        Message = MessageType(request.message_type());
        Content = request.content();

        if (request.has_command()) {
            WithCommand = true;
            Command = request.command();
        }

        if (request.has_files()) {
            FilesAttached = true;
            Files = memcpy(Files, request.files().c_str(), request.files().size());
        }
        std::cerr << "---Got message---" << std::endl << "Type: " << static_cast<int>(Message) << std::endl << "Content: " << Content << std::endl << "-----\n";
    }

    void Parse(std::istream* stream) {
        cactus::CactusMessage request;
        request.ParseFromIstream(stream);
        Message = MessageType(request.message_type());
        Content = request.content();

        if (request.has_command()) {
            WithCommand = true;
            Command = request.command();
        }

        if (request.has_files()) {
            FilesAttached = true;
            Files = memcpy(Files, request.files().c_str(), request.files().size());
        }
    }

    boost::asio::const_buffer ToBuffer() const {
        cactus::CactusMessage message;
        message.set_message_type(static_cast<int>(Message));
        message.set_command(Command);
        message.set_content(Content);
        return boost::asio::buffer(message.SerializeAsString());
    }

    std::vector<boost::asio::const_buffer> ToBuffers() const  {
        std::vector<boost::asio::const_buffer> result;
        result.push_back(ToBuffer());
        TMessage request;
        request.Parse(static_cast<const char*>(result[0].data()), result[0].size());
        return result;
    }

    void ToStreamBuf(boost::asio::streambuf* streambuf) const {
        cactus::CactusMessage message;
        message.set_message_type(static_cast<int>(Message));
        message.set_command(Command);
        message.set_content(Content);
        std::ostream os(streambuf);
        message.SerializeToOstream(&os);
    }

    MessageType Message;
    std::string Content;
    std::string Command;
    void* Files;

    bool WithCommand;
    bool FilesAttached;
};
#endif //CACTUS_MESSAGE_H
