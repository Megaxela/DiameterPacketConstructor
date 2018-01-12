
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/googletest/googletest")
    add_subdirectory(googletest)
endif()

include_directories(../include)

# Setting compile warnings
set(CMAKE_CXX_FLAGS "-ansi \
                     -pedantic \
                     -Wabi \
                     -Wall \
                     -Wextra \
                     -Weffc++ \
                     -Woverloaded-virtual \
                     -Winit-self \
                     -Wunreachable-code ")

file(GLOB TESTS_SRCS *.cpp)

add_executable(UnitTests ${TESTS_SRCS})

target_link_libraries(UnitTests
        DiameterPacketConstructor
        gtest
)