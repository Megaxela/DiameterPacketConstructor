#include <benchmark/benchmark.h>
#include <Diameter/AVP.hpp>
#include <iostream>
#include <cstdint>
#include <thread>
#include "bench_extend/NamespaceRegistrator.hpp"

namespace AVP
{
    static void DefaultConstruction(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::AVP());
        }
    }

    static void CopyEmpty(benchmark::State& state)
    {
        Diameter::AVP avp;

        for (auto _ : state)
        {
            Diameter::AVP copy(avp);

            benchmark::DoNotOptimize(copy);
        }
    }

    static void CopyWithData(benchmark::State& state)
    {
        Diameter::AVP avp;

        ByteArray byteArray;

        byteArray.appendMultiple<uint8_t>(
            0xAA,
            static_cast<ByteArray::size_type>(state.range(0))
        );

        avp.setData(Diameter::AVP::Data(byteArray));

        for (auto _ : state)
        {
            Diameter::AVP copy(avp);

            benchmark::DoNotOptimize(copy);
        }
    }

    static void MoveEmpty(benchmark::State& state)
    {
        Diameter::AVP avp;

        for (auto _ : state)
        {
            auto copy = std::move(avp);

            benchmark::DoNotOptimize(copy);

            avp = std::move(copy);
        }
    }

    static void MoveWithData(benchmark::State& state)
    {
        Diameter::AVP avp;

        ByteArray byteArray;

        byteArray.appendMultiple<uint8_t>(
            0xAA,
            static_cast<ByteArray::size_type>(state.range(0))
        );

        avp.setData(Diameter::AVP::Data(byteArray));

        for (auto _ : state)
        {
            auto copy = std::move(avp);

            benchmark::DoNotOptimize(copy);

            avp = std::move(copy);
        }

        state.SetComplexityN(state.range(0));
    }

    static void SetHeader(benchmark::State& state)
    {
        Diameter::AVP avp;

        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            avp.setHeader(header);
        }
    }

    static void SetHeaderReference(benchmark::State& state)
    {
        Diameter::AVP avp;

        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            avp.header() = header;
        }
    }

    static void Header(benchmark::State& state)
    {
        Diameter::AVP avp;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.header());
        }
    }

    static void SetDataEmpty(benchmark::State& state)
    {
        Diameter::AVP avp;

        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            avp.setData(data);
        }
    }

    static void SetDataWithData(benchmark::State& state)
    {
        Diameter::AVP avp;

        Diameter::AVP::Data data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        for (auto _ : state)
        {
            avp.setData(data);
        }
    }

    static void SetDataReferenceEmpty(benchmark::State& state)
    {
        Diameter::AVP avp;

        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            avp.data() = data;
        }
    }

    static void SetDataReferenceWithData(benchmark::State& state)
    {
        Diameter::AVP avp;

        Diameter::AVP::Data data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        for (auto _ : state)
        {
            avp.data() = data;
        }
    }

    static void DataEmpty(benchmark::State& state)
    {
        Diameter::AVP avp;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.data());
        }
    }

    static void DataWithData(benchmark::State& state)
    {
        Diameter::AVP avp;

        avp.data() = Diameter::AVP::Data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.data());
        }
    }

    static void IsValidTrue(benchmark::State& state)
    {
        // Making it's valid
        Diameter::AVP avp;

        avp.data() = Diameter::AVP::Data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        avp.updateLength();

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.isValid());
        }
    }

    static void IsValidFalse(benchmark::State& state)
    {
        // Making it's valid
        Diameter::AVP avp;

        // This AVP is not valid, because
        // avp header flags must set all bits, except active to 0
        avp.header().flags().setFlag(
            static_cast<Diameter::AVP::Header::Flags::Bits>(0b00010000),
            true
        );

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.isValid());
        }
    }

    static void CalculateLength(benchmark::State& state)
    {
        // Making it's valid
        Diameter::AVP avp;

        avp.data() = Diameter::AVP::Data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        avp.updateLength();

        auto includePadding = static_cast<bool>(state.range(0));

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.calculateLength(includePadding));
        }
    }

    static void UpdateLength(benchmark::State& state)
    {
        Diameter::AVP avp;

        avp.data() = Diameter::AVP::Data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.updateLength());
        }
    }

    static void DeployAlreadyAllocated(benchmark::State& state)
    {
        Diameter::AVP avp;

        avp.data() = Diameter::AVP::Data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        ByteArray array(avp.calculateLength(true));

        for (auto _ : state)
        {
            array.clear();
            avp.deploy(array);
        }
    }

    static void DeployNewByteArray(benchmark::State& state)
    {
        Diameter::AVP avp;

        avp.data() = Diameter::AVP::Data(
            ByteArray::fromHex("AABBCCDDEEFF")
        );

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(avp.deploy());
        }
    }
}

BENCHMARK_NS(AVP::DefaultConstruction);
BENCHMARK_NS(AVP::CopyEmpty);
BENCHMARK_NS(AVP::CopyWithData)
    ->Range(1, 1 << 20)
    ->Complexity();
BENCHMARK_NS(AVP::MoveEmpty);
BENCHMARK_NS(AVP::MoveWithData)
    ->Range(1, 1 << 20)
    ->Complexity();

BENCHMARK_NS(AVP::SetHeader);
BENCHMARK_NS(AVP::SetHeaderReference);
BENCHMARK_NS(AVP::Header);

BENCHMARK_NS(AVP::SetDataEmpty);
BENCHMARK_NS(AVP::SetDataWithData);
BENCHMARK_NS(AVP::SetDataReferenceEmpty);
BENCHMARK_NS(AVP::SetDataReferenceWithData);

BENCHMARK_NS(AVP::DataEmpty);
BENCHMARK_NS(AVP::DataWithData);

BENCHMARK_NS(AVP::IsValidTrue);
BENCHMARK_NS(AVP::IsValidFalse);

BENCHMARK_NS(AVP::CalculateLength)->Arg(0);
BENCHMARK_NS(AVP::CalculateLength)->Arg(1);
BENCHMARK_NS(AVP::UpdateLength);

BENCHMARK_NS(AVP::DeployAlreadyAllocated);
BENCHMARK_NS(AVP::DeployNewByteArray);