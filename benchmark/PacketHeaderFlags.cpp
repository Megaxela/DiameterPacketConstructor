
#include <benchmark/benchmark.h>
#include <Diameter/Packet.hpp>
#include "bench_extend/NamespaceRegistrator.hpp"

namespace Packet { namespace Header { namespace Flags {
    /**
     * @brief Benchmark for checking flags construction
     * speed.
     */
    static void DefaultConstruction(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::Packet::Header::Flags());
        }
    }

    /**
     * @brief Method for checking copy speed.
     * @param state Copy speed.
     */
    static void Copy(benchmark::State& state)
    {
        Diameter::Packet::Header::Flags flag;
        for (auto _ : state)
        {
            Diameter::Packet::Header::Flags copy = flag;
            benchmark::DoNotOptimize(copy);
        }
    }

    /**
     * @brief Method for checking move speed.
     * @param state Move speed.
     */
    static void Move(benchmark::State& state)
    {
        Diameter::Packet::Header::Flags flag;
        for (auto _ : state)
        {
            Diameter::Packet::Header::Flags copy = std::move(flag);

            benchmark::DoNotOptimize(copy);

            flag = std::move(copy);
        }
    }

    /**
     * @brief Benchmark for checking flags setting
     * speed.
     */
    static void SetFlag(benchmark::State& state)
    {
        Diameter::Packet::Header::Flags flag;

        for (auto _ : state)
        {
            flag.setFlag(
                Diameter::Packet::Header::Flags::Bits::Request,
                true
            );
        }
    }

    /**
     * @brief Benchmark for checking flags checking
     * speed.
     */
    static void IsSet(benchmark::State& state)
    {
        Diameter::Packet::Header::Flags flags;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(flags.isSet(
                Diameter::Packet::Header::Flags::Bits::Request
            ));
        }
    }

    /**
     * @brief Method for checking flag validness
     * speed.
     */
    static void IsValid(benchmark::State& state)
    {
        Diameter::Packet::Header::Flags flags;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(
                flags.isValid()
            );
        }
    }

    static void Deploy(benchmark::State& state)
    {
        Diameter::Packet::Header::Flags flags;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(
                flags.deploy()
            );
        }
    }
}}}

BENCHMARK_NS(Packet::Header::Flags::DefaultConstruction);
BENCHMARK_NS(Packet::Header::Flags::Copy);
BENCHMARK_NS(Packet::Header::Flags::Move);
BENCHMARK_NS(Packet::Header::Flags::SetFlag);
BENCHMARK_NS(Packet::Header::Flags::IsSet);
BENCHMARK_NS(Packet::Header::Flags::IsValid);
BENCHMARK_NS(Packet::Header::Flags::Deploy);