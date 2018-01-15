
#include <benchmark/benchmark.h>
#include <Diameter/AVP.hpp>
#include "bench_extend/NamespaceRegistrator.hpp"

namespace AVP{ namespace Header{ namespace Flags {
    /**
     * @brief Benchmark for checking flags construction
     * speed.
     */
    static void DefaultConstruction(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::AVP::Header::Flags());
        }
    }

    /**
     * @brief Method for checking copy speed.
     * @param state Copy speed.
     */
    static void Copy(benchmark::State& state)
    {
        Diameter::AVP::Header::Flags flag;
        for (auto _ : state)
        {
            Diameter::AVP::Header::Flags copy = flag;
            benchmark::DoNotOptimize(copy);
        }
    }

    /**
     * @brief Method for checking move speed.
     * @param state Move speed.
     */
    static void Move(benchmark::State& state)
    {
        Diameter::AVP::Header::Flags flag;
        for (auto _ : state)
        {
            Diameter::AVP::Header::Flags copy = std::move(flag);

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
        Diameter::AVP::Header::Flags flag;

        for (auto _ : state)
        {
            flag.setFlag(
                Diameter::AVP::Header::Flags::Bits::Mandatory,
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
        Diameter::AVP::Header::Flags flags;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(flags.isSet(
                Diameter::AVP::Header::Flags::Bits::Mandatory
            ));
        }
    }

    /**
     * @brief Method for checking flag validness
     * speed.
     */
    static void IsValid(benchmark::State& state)
    {
        Diameter::AVP::Header::Flags flags;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(
                flags.isValid()
            );
        }
    }

    static void Deploy(benchmark::State& state)
    {
        Diameter::AVP::Header::Flags flags;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(
                flags.deploy()
            );
        }
    }
}}}
BENCHMARK_NS(AVP::Header::Flags::DefaultConstruction);
BENCHMARK_NS(AVP::Header::Flags::Copy);
BENCHMARK_NS(AVP::Header::Flags::Move);
BENCHMARK_NS(AVP::Header::Flags::SetFlag);
BENCHMARK_NS(AVP::Header::Flags::IsSet);
BENCHMARK_NS(AVP::Header::Flags::IsValid);
BENCHMARK_NS(AVP::Header::Flags::Deploy);