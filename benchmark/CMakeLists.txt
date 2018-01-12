
# Disable benchmark tests
set(BENCHMARK_ENABLE_TESTING Off)

# Disable benchmark library installation
set(BENCHMARK_ENABLE_INSTALL Off)

# If benchmark library included as git submodule
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/benchmark/include")
    # Adding git benchmark as submodule
    add_subdirectory(benchmark)

    # Include benchmark headers
    include_directories(benchmark/include)
endif()

# Search for benchmarks
file(GLOB BENCHMARK_SRCS *.cpp)

# Add benchmarks to executable
add_executable(ConstructorBenchmark
        ${BENCHMARK_SRCS}
        bench_extend/NamespaceRegistrator.hpp AVPData.cpp AVP.cpp Packet.cpp)

# Link everything
target_link_libraries(ConstructorBenchmark
        DiameterPacketConstructor
        gtest
        benchmark
)