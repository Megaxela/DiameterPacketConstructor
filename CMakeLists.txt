cmake_minimum_required(VERSION 3.8)
project(DiameterPacketConstructor)

set(CMAKE_CXX_STANDARD 11)

option(DIAMETER_BUILD_TESTS "Build tests for packet constructor" OFF)

include_directories(
        include
        libraries/ByteArray/include
)

add_subdirectory(libraries/ByteArray)

if (${DIAMETER_BUILD_TESTS})
    add_subdirectory(tests)
endif()

set(INCLUDE_FILES
        include/Packet.hpp
        include/AVP.hpp)

set(SOURCE_FILES
        src/Packet.cpp
        src/AVP.cpp
        src/PacketHeader.cpp
        src/PacketHeaderFlags.cpp
        src/AVPHeader.cpp
        src/AVPHeaderFlags.cpp
        src/AVPData.cpp
        )

add_library(DiameterPacketConstructor STATIC
        ${INCLUDE_FILES}
        ${SOURCE_FILES}
)

target_link_libraries(DiameterPacketConstructor ByteArray)
