
#include <benchmark/benchmark.h>
#include <Diameter/AVP.hpp>
#include <iostream>
#include <cstdint>
#include <thread>
#include "bench_extend/NamespaceRegistrator.hpp"

namespace AVP { namespace Data
{
    static void DefaultConstruction(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::AVP::Data());
        }
    }

    static void CopyEmpty(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            auto copy = data;

            benchmark::DoNotOptimize(copy);
        }
    }

    static void MoveEmpty(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            auto copy = std::move(data);

            benchmark::DoNotOptimize(copy);

            data = std::move(copy);
        }
    }

    static void CopyWithData(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        ByteArray byteArray;

        byteArray.appendMultiple<uint8_t>(
            0xAA,
            static_cast<ByteArray::size_type>(state.range(0))
        );

        data.setOctetString(byteArray);

        for (auto _ : state)
        {
            auto copy = data;

            benchmark::DoNotOptimize(copy);
        }
    }

    static void MoveWithData(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        ByteArray byteArray;

        byteArray.appendMultiple<uint8_t>(
            0xAA,
            static_cast<ByteArray::size_type>(state.range(0))
        );

        data.setOctetString(byteArray);

        for (auto _ : state)
        {
            auto copy = std::move(data);

            benchmark::DoNotOptimize(copy);

            data = std::move(copy);
        }

        state.SetComplexityN(state.range(0));
    }

    static void SetOctetString(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto byteArray = ByteArray::fromHex("00112233445566778899AABBCCDDEEFF");

        for (auto _ : state)
        {
            data.setOctetString(byteArray);
        }
    }

    static void ToOctetStringEmpty(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.toOctetString());
        }
    }

    static void ToOctetStringWithData(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        data.setOctetString(ByteArray::fromHex("00112233445566778899AABBCCDDEEFF"));

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.toOctetString());
        }
    }

    static void SetInteger32(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto val = state.range(0);

        for (auto _ : state)
        {
            data.setInteger32(val);
        }
    }

    static void ToInteger32Success(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        data.setInteger32(123456);

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.toInteger32());
        }
    }

    static void ToInteger32Failed(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            try
            {
                data.toInteger32();
            }
            catch (std::invalid_argument& exception)
            {

            }
        }
    }

    static void SetInteger64(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto val = state.range(0);

        for (auto _ : state)
        {
            data.setInteger64(val);
        }
    }

    static void ToInteger64Success(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        data.setInteger64(123456);

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.toInteger64());
        }
    }

    static void ToInteger64Failed(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            try
            {
                data.toInteger64();
            }
            catch (std::invalid_argument& exception)
            {

            }
        }
    }

    static void SetUnsigned32(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto val = static_cast<uint32_t>(state.range(0));

        for (auto _ : state)
        {
            data.setUnsigned32(val);
        }
    }

    static void ToUnsigned32Success(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        data.setUnsigned32(123456);

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.toUnsigned32());
        }
    }

    static void ToUnsigned32Failed(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            try
            {
                data.toUnsigned32();
            }
            catch (std::invalid_argument& exception)
            {

            }
        }
    }

    static void SetUnsigned64(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto val = static_cast<uint64_t>(state.range(0));

        for (auto _ : state)
        {
            data.setUnsigned64(val);
        }
    }

    static void ToUnsigned64Success(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        data.setUnsigned64(123456);

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.toUnsigned64());
        }
    }

    static void ToUnsigned64Failed(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        for (auto _ : state)
        {
            try
            {
                data.toUnsigned64();
            }
            catch (std::invalid_argument& exception)
            {

            }
        }
    }

    static void ToAVPsSuccess(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto avp = Diameter::AVP()
            .setData(
                Diameter::AVP::Data(
                    ByteArray::fromHex("00112233445566778899AABBCCDDEEFF")
                )
            );

        avp.updateLength();

        for (auto i = 0; i < state.range(0); ++i)
        {
            data.addAVP(
                avp
            );
        }

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.toAVPs());
        }

        state.SetComplexityN(state.range(0));
    }

    static void ToAVPsFail(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        data.setOctetString(
            ByteArray::fromHex("AABBCC")
        );

        for (auto _ : state)
        {
            try
            {
                auto container = data.toAVPs();
            }
            catch (std::invalid_argument& exception)
            {

            }
        }

    }

    static void Size(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto avp = Diameter::AVP()
            .setData(
                Diameter::AVP::Data(
                    ByteArray::fromHex("00112233445566778899AABBCCDDEEFF")
                )
            );

        avp.updateLength();

        for (auto i = 0; i < state.range(0); ++i)
        {
            data.addAVP(
                avp
            );
        }

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.size());
        }

        state.SetComplexityN(state.range(0));
    }

    static void IsValid(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto avp = Diameter::AVP()
            .setData(
                Diameter::AVP::Data(
                    ByteArray::fromHex("00112233445566778899AABBCCDDEEFF")
                )
            );

        avp.updateLength();

        for (auto i = 0; i < state.range(0); ++i)
        {
            data.addAVP(
                avp
            );
        }

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.isValid());
        }

        state.SetComplexityN(state.range(0));
    }

    static void DeployAlreadyAllocated(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto avp = Diameter::AVP()
            .setData(
                Diameter::AVP::Data(
                    ByteArray::fromHex("00112233445566778899AABBCCDDEEFF")
                )
            );

        avp.updateLength();

        for (auto i = 0; i < state.range(0); ++i)
        {
            data.addAVP(
                avp
            );
        }

        ByteArray array(data.size());

        for (auto _ : state)
        {
            array.clear();
            data.deploy(array);
        }

        state.SetComplexityN(state.range(0));
    }

    static void DeployNewByteArray(benchmark::State& state)
    {
        Diameter::AVP::Data data;

        auto avp = Diameter::AVP()
            .setData(
                Diameter::AVP::Data(
                    ByteArray::fromHex("00112233445566778899AABBCCDDEEFF")
                )
            );

        avp.updateLength();

        for (auto i = 0; i < state.range(0); ++i)
        {
            data.addAVP(
                avp
            );
        }

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(data.deploy());
        }

        state.SetComplexityN(state.range(0));
    }
}}

BENCHMARK_NS(AVP::Data::DefaultConstruction);
BENCHMARK_NS(AVP::Data::CopyEmpty);
BENCHMARK_NS(AVP::Data::CopyWithData)
    ->Range(1, 1 << 20)
    ->Complexity();
BENCHMARK_NS(AVP::Data::MoveEmpty);
BENCHMARK_NS(AVP::Data::MoveWithData)
    ->Range(1, 1 << 20)
    ->Complexity();

BENCHMARK_NS(AVP::Data::SetOctetString);
BENCHMARK_NS(AVP::Data::ToOctetStringEmpty);
BENCHMARK_NS(AVP::Data::ToOctetStringWithData);

BENCHMARK_NS(AVP::Data::SetInteger32)->Arg(123123);
BENCHMARK_NS(AVP::Data::ToInteger32Success);
BENCHMARK_NS(AVP::Data::ToInteger32Failed);

BENCHMARK_NS(AVP::Data::SetInteger64)->Arg(123123);
BENCHMARK_NS(AVP::Data::ToInteger64Success);
BENCHMARK_NS(AVP::Data::ToInteger64Failed);

BENCHMARK_NS(AVP::Data::SetUnsigned32)->Arg(123123);
BENCHMARK_NS(AVP::Data::ToUnsigned32Success);
BENCHMARK_NS(AVP::Data::ToUnsigned32Failed);

BENCHMARK_NS(AVP::Data::SetUnsigned64)->Arg(123123);
BENCHMARK_NS(AVP::Data::ToUnsigned64Success);
BENCHMARK_NS(AVP::Data::ToUnsigned64Failed);

BENCHMARK_NS(AVP::Data::ToAVPsSuccess)
    ->Range(1, 1 << 10)
    ->Complexity();
BENCHMARK_NS(AVP::Data::ToAVPsFail);
BENCHMARK_NS(AVP::Data::Size)
    ->Range(1, 1 << 10)
    ->Complexity();
BENCHMARK_NS(AVP::Data::IsValid)
    ->Range(1, 1 << 10)
    ->Complexity();
BENCHMARK_NS(AVP::Data::DeployAlreadyAllocated)
    ->Range(1, 1 << 10)
    ->Complexity();
BENCHMARK_NS(AVP::Data::DeployNewByteArray)
    ->Range(1, 1 << 10)
    ->Complexity();