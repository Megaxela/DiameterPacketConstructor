
#include <benchmark/benchmark.h>
#include <Diameter/AVP.hpp>
#include <iostream>
#include <cstdint>
#include <thread>
#include "bench_extend/NamespaceRegistrator.hpp"

namespace AVP { namespace Header
{
    static void DefaultConstruction(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::AVP::Header());
        }
    }

    static void Copy(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            auto copy = header;

            benchmark::DoNotOptimize(copy);
        }
    }

    static void Move(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            auto copy = std::move(header);

            benchmark::DoNotOptimize(copy);

            header = std::move(copy);
        }
    }

    static void SetAVPCode(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        auto val = static_cast<Diameter::AVP::Header::AVPCodeType>(state.range(0));

        for (auto _ : state)
        {
            header.setAVPCode(val);
        }
    }

    static void SetAVPCodeReference(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        auto val = static_cast<Diameter::AVP::Header::AVPCodeType>(state.range(0));

        for (auto _ : state)
        {
            header.avpCode() = val;
        }
    }

    static void AVPCode(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.avpCode());
        }
    }

    static void SetFlags(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        Diameter::AVP::Header::Flags flags(static_cast<Diameter::AVP::Header::Flags::Type>(state.range(0)));

        for (auto _ : state)
        {
            header.setFlags(flags);
        }
    }

    static void SetFlagsReference(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        Diameter::AVP::Header::Flags flags(static_cast<Diameter::AVP::Header::Flags::Type>(state.range(0)));

        for (auto _ : state)
        {
            header.flags() = flags;
        }
    }

    static void Flags(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.flags());
        }
    }

    static void SetAVPLength(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        auto val = static_cast<Diameter::AVP::Header::LengthType>(state.range(0));

        for (auto _ : state)
        {
            header.setAVPLength(val);
        }
    }

    static void SetAVPLengthReference(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        auto val = static_cast<Diameter::AVP::Header::LengthType>(state.range(0));

        for (auto _ : state)
        {
            header.length() = val;
        }
    }

    static void Length(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.length());
        }
    }

    static void SetVendorIDSuccess(benchmark::State& state)
    {
        Diameter::AVP::Header header;
        header.flags().setFlag(Diameter::AVP::Header::Flags::Bits::VendorSpecific, true);

        auto val = static_cast<Diameter::AVP::Header::VendorIdType>(state.range(0));

        for (auto _ : state)
        {
            header.setVendorID(val);
        }
    }

    static void SetVendorIDFail(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        auto val = static_cast<Diameter::AVP::Header::VendorIdType>(state.range(0));

        for (auto _ : state)
        {
            try
            {
                header.setVendorID(val);
            }
            catch (std::invalid_argument& exception)
            {

            }
        }
    }

    static void VendorIDSuccess(benchmark::State& state)
    {
        Diameter::AVP::Header header;
        header.flags().setFlag(Diameter::AVP::Header::Flags::Bits::VendorSpecific, true);

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.vendorId());
        }
    }

    static void VendorIDFail(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            try
            {
                benchmark::DoNotOptimize(header.vendorId());
            }
            catch (std::invalid_argument& exception)
            {

            }
        }
    }

    static void IsValid(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.isValid());
        }
    }

    static void CalculateSize(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.calculateSize());
        }
    }

    static void DeployAlreadyAllocated(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        ByteArray array(header.calculateSize());

        for (auto _ : state)
        {
            array.clear();
            header.deploy(array);
        }
    }

    static void DeployNewByteArray(benchmark::State& state)
    {
        Diameter::AVP::Header header;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(header.deploy());
        }
    }
}}

BENCHMARK_NS(AVP::Header::DefaultConstruction)->Arg(12);
BENCHMARK_NS(AVP::Header::Copy);
BENCHMARK_NS(AVP::Header::Move);

BENCHMARK_NS(AVP::Header::SetAVPCode)         ->Arg(222);
BENCHMARK_NS(AVP::Header::SetAVPCodeReference)->Arg(222);
BENCHMARK_NS(AVP::Header::AVPCode);

BENCHMARK_NS(AVP::Header::SetFlags)         ->Arg(0b0001);
BENCHMARK_NS(AVP::Header::SetFlagsReference)->Arg(0b0001);
BENCHMARK_NS(AVP::Header::Flags);

BENCHMARK_NS(AVP::Header::SetAVPLength)         ->Arg(128);
BENCHMARK_NS(AVP::Header::SetAVPLengthReference)->Arg(128);
BENCHMARK_NS(AVP::Header::Length);

BENCHMARK_NS(AVP::Header::SetVendorIDSuccess)->Arg(16000);
BENCHMARK_NS(AVP::Header::SetVendorIDFail)   ->Arg(16000);
BENCHMARK_NS(AVP::Header::VendorIDSuccess);
BENCHMARK_NS(AVP::Header::VendorIDFail);

BENCHMARK_NS(AVP::Header::IsValid);

BENCHMARK_NS(AVP::Header::CalculateSize);
BENCHMARK_NS(AVP::Header::DeployAlreadyAllocated);
BENCHMARK_NS(AVP::Header::DeployNewByteArray);