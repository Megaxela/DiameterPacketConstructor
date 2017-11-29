cmake_minimum_required(VERSION 3.8)
project(DiameterPacketConstructor)

set(CMAKE_CXX_STANDARD 11)

option(DIAMETER_BUILD_TESTS "Build tests for packet constructor" OFF)

include_directories(include)

if (EXISTS ${CMAKE_SOURCE_DIR}/libraries/ByteArray/CMakeLists.txt)
    add_subdirectory(libraries/ByteArray)
    include_directories(libraries/ByteArray/include)
else()
    message("ByteArray submodule was not presented. Parent project has to present one.")
endif()

if (${DIAMETER_BUILD_TESTS})
    add_subdirectory(tests)
endif()

set(INCLUDE_FILES
        include/Diameter/Packet.hpp
        include/Diameter/AVP.hpp)

set(SOURCE_FILES
        src/Diameter/Packet.cpp
        src/Diameter/AVP.cpp
        src/Diameter/PacketHeader.cpp
        src/Diameter/PacketHeaderFlags.cpp
        src/Diameter/AVPHeader.cpp
        src/Diameter/AVPHeaderFlags.cpp
        src/Diameter/AVPData.cpp
        )

add_library(DiameterPacketConstructor STATIC
        ${INCLUDE_FILES}
        ${SOURCE_FILES}
)

target_link_libraries(DiameterPacketConstructor ByteArray)
