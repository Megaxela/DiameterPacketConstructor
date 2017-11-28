add_subdirectory(googletest)

include_directories(../include)

file(GLOB TESTS_SRCS *.cpp)

add_executable(UnitTests ${TESTS_SRCS})

target_link_libraries(UnitTests DiameterPacketConstructor gtest)