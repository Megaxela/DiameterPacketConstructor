
#include <benchmark/benchmark.h>
#include <Diameter/Packet.hpp>
#include <iostream>
#include <cstdint>
#include "bench_extend/NamespaceRegistrator.hpp"

namespace Packet { namespace Header
{
    static void DefaultConstruction(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::Packet::Header());
        }
    }

    static void Copy(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            auto copy = header;

            benchmark::DoNotOptimize(copy);
        }
    }

    static void Move(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            auto copy = std::move(header);

            benchmark::DoNotOptimize(copy);

            header = std::move(copy);
        }
    }

    static void SetVersion(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::VersionType>(state.range(0));

        for (auto _ : state)
        {
            header.setVersion(val);
        }
    }

    static void SetVersionReference(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::VersionType>(state.range(0));

        for (auto _ : state)
        {
            header.version() = val;
        }
    }

    static void Version(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.version());
        }
    }

    static void SetMessageLength(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::MessageLengthType>(state.range(0));

        for (auto _ : state)
        {
            header.setMessageLength(val);
        }
    }

    static void SetMessageLengthReference(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::MessageLengthType>(state.range(0));

        for (auto _ : state)
        {
            header.messageLength() = val;
        }
    }

    static void MessageLength(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.messageLength());
        }
    }

    static void SetCommandFlags(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<uint8_t>(state.range(0));

        auto flags = Diameter::Packet::Header::Flags(val);

        for (auto _ : state)
        {
            header.setCommandFlags(flags);
        }
    }

    static void SetCommandFlagsReference(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<uint8_t>(state.range(0));

        auto flags = Diameter::Packet::Header::Flags(val);

        for (auto _ : state)
        {
            header.commandFlags() = flags;
        }
    }

    static void CommandFlags(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.commandFlags());
        }
    }

    static void SetCommandCode(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::CommandCodeType>(state.range(0));

        for (auto _ : state)
        {
            header.setCommandCode(val);
        }
    }

    static void SetCommandCodeReference(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::CommandCodeType>(state.range(0));

        for (auto _ : state)
        {
            header.commandCode() = val;
        }
    }

    static void CommandCode(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.commandCode());
        }
    }

    static void SetApplicationId(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::ApplicationIdType>(state.range(0));

        for (auto _ : state)
        {
            header.setApplicationId(val);
        }
    }

    static void SetApplicationIdReference(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::ApplicationIdType>(state.range(0));

        for (auto _ : state)
        {
            header.applicationId() = val;
        }
    }

    static void ApplicationId(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.applicationId());
        }
    }

    static void SetHBHIdentifier(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::HBHType>(state.range(0));

        for (auto _ : state)
        {
            header.setHBHIdentifier(val);
        }
    }

    static void SetHBHIdentifierReference(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::HBHType>(state.range(0));

        for (auto _ : state)
        {
            header.hbhIdentifier() = val;
        }
    }

    static void HBHIdentifier(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.hbhIdentifier());
        }
    }

    static void SetETEIdentifier(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::ETEType>(state.range(0));

        for (auto _ : state)
        {
            header.setETEIdentifier(val);
        }
    }

    static void SetETEIdentifierReference(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        auto val = static_cast<Diameter::Packet::Header::ETEType>(state.range(0));

        for (auto _ : state)
        {
            header.eteIdentifier() = val;
        }
    }

    static void ETEIdentifier(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.eteIdentifier());
        }
    }

    static void IsValid(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.isValid());
        }
    }

    static void DeployAlreadyAllocated(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        ByteArray array(Diameter::Packet::Header::Size);

        for (auto _ : state)
        {
            array.clear();
            header.deploy(array);
        }
    }

    static void DeployNewByteArray(benchmark::State& state)
    {
        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.deploy());
        }
    }
}}

BENCHMARK_NS(Packet::Header::DefaultConstruction);
BENCHMARK_NS(Packet::Header::Copy);
BENCHMARK_NS(Packet::Header::Move);

BENCHMARK_NS(Packet::Header::SetVersion)         ->Arg(1);
BENCHMARK_NS(Packet::Header::SetVersionReference)->Arg(1);
BENCHMARK_NS(Packet::Header::Version);

BENCHMARK_NS(Packet::Header::SetMessageLength)         ->Arg(4096);
BENCHMARK_NS(Packet::Header::SetMessageLengthReference)->Arg(4096);
BENCHMARK_NS(Packet::Header::MessageLength);

BENCHMARK_NS(Packet::Header::SetCommandFlags)         ->Arg(0b0111);
BENCHMARK_NS(Packet::Header::SetCommandFlagsReference)->Arg(0b0111);
BENCHMARK_NS(Packet::Header::CommandFlags);

BENCHMARK_NS(Packet::Header::SetCommandCode)         ->Arg(211);
BENCHMARK_NS(Packet::Header::SetCommandCodeReference)->Arg(211);
BENCHMARK_NS(Packet::Header::CommandCode);

BENCHMARK_NS(Packet::Header::SetApplicationId)         ->Arg(16667331);
BENCHMARK_NS(Packet::Header::SetApplicationIdReference)->Arg(16667331);
BENCHMARK_NS(Packet::Header::ApplicationId);

BENCHMARK_NS(Packet::Header::SetHBHIdentifier)         ->Arg(0xAABBCCDD);
BENCHMARK_NS(Packet::Header::SetHBHIdentifierReference)->Arg(0xAABBCCDD);
BENCHMARK_NS(Packet::Header::HBHIdentifier);

BENCHMARK_NS(Packet::Header::SetETEIdentifier)         ->Arg(0xAABBCCDD);
BENCHMARK_NS(Packet::Header::SetETEIdentifierReference)->Arg(0xAABBCCDD);
BENCHMARK_NS(Packet::Header::ETEIdentifier);

BENCHMARK_NS(Packet::Header::IsValid);

BENCHMARK_NS(Packet::Header::DeployNewByteArray);
BENCHMARK_NS(Packet::Header::DeployAlreadyAllocated);