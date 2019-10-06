cmake_minimum_required(VERSION 3.14)
project(cactus)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.70.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

include(FindProtobuf)
find_package(Protobuf REQUIRED)
#set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
#set(${CMAKE_INCLUDE_CURRENT_DIR}_PROTOS/message message.proto)
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS message.proto)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS message/message.proto)


add_executable(cactus-master start_master.cpp server/connection.cpp server/connection_manager.cpp server/mime_types.cpp server/reply.cpp server/request_handler.cpp server/request_parser.cpp server/server.cpp message/message.proto ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(cactus api.cpp message/message.proto ${PROTO_SRCS} ${PROTO_HDRS})


if(Boost_FOUND AND Protobuf_FOUND)
    target_link_libraries(cactus-master ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})
    target_link_libraries(cactus ${Boost_LIBRARIES} ${PROTOBUF_LIBRARY})
endif()

if(NOT Boost_FOUND OR NOT Protobuf_FOUND)
    message(FATAL_ERROR "Could not find packages!")
endif()