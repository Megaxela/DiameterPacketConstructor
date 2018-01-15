#include <benchmark/benchmark.h>
#include <Diameter/Packet.hpp>
#include <iostream>
#include <cstdint>
#include "bench_extend/NamespaceRegistrator.hpp"

namespace {
    Diameter::AVP generateAVP(uint32_t size)
    {
        ByteArray byteArray;

        byteArray.appendMultiple<uint8_t>(
            0xAA,
            size
        );

        return Diameter::AVP()
            .setData(Diameter::AVP::Data(byteArray))
            .updateLength();
    }
    
    static const ByteArray binaryCER = ByteArray::fromHex(
        "010001b880000101000000007ddf9e97"
        "c15f0a0a000001084000000f64726532"
        "30313700000001024000000c00000000"
        "000001024000000c0000000400000102"
        "4000000c01000016000001024000000c"
        "01000014000001024000000c01000032"
        "000001024000000c0100002300000102"
        "4000000c01000024000001024000000c"
        "01000033000001024000000c01000001"
        "000001024000000c0100000000000102"
        "4000000c01000056000001024000000c"
        "01000057000001024000000c0000000a"
        "000001024000000c0100000600000102"
        "4000000c00000003000001024000000c"
        "01000066000001024000000c01000038"
        "000001024000000c0100003000000102"
        "4000000c01000031000001024000000c"
        "0000d90500000128400000256d6e6330"
        "30322e6d63633235302e336770706e65"
        "74776f726b2e6f72670000000000010d"
        "000000144954532d4469616d65746572"
        "0000012b4000000c000000010000012b"
        "4000000c00000000000001014000000e"
        "0001c0a806610000000001014000000e"
        "0001c0a8066100000000010a4000000c"
        "000000000000010b0000000c00000001"
        "000001094000000c000028af00000103"
        "4000000c00000003"
    );
}

namespace Packet
{
    static void DefaultConstruction(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::Packet());
        }
    }

    static void CopyEmpty(benchmark::State& state)
    {
        Diameter::Packet packet;

        for (auto _ : state)
        {
            auto copy = packet;

            benchmark::DoNotOptimize(copy);
        }
    }

    static void MoveEmpty(benchmark::State& state)
    {
        Diameter::Packet packet;

        for (auto _ : state)
        {
            auto moved = std::move(packet);

            benchmark::DoNotOptimize(moved);

            packet = std::move(moved);
        }
    }

    static void CopyWithData(benchmark::State& state)
    {
        Diameter::Packet packet;

        for (int i = 0; i < state.range(0); ++i)
        {
            packet.addAVP(
                generateAVP(
                    static_cast<uint32_t>(state.range(1))
                )
            );
        }

        for (auto _ : state)
        {
            auto copy = packet;

            benchmark::DoNotOptimize(copy);
        }

        state.SetComplexityN(state.range(0));
    }

    static void MoveWithData(benchmark::State& state)
    {
        Diameter::Packet packet;

        for (int i = 0; i < state.range(0); ++i)
        {
            packet.addAVP(
                generateAVP(
                    static_cast<uint32_t>(state.range(1))
                )
            );
        }

        for (auto _ : state)
        {
            auto moved = std::move(packet);

            benchmark::DoNotOptimize(moved);

            packet = std::move(moved);
        }

        state.SetComplexityN(state.range(0));
    }

    static void SetHeader(benchmark::State& state)
    {
        Diameter::Packet packet;

        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            packet.setHeader(header);
        }
    }

    static void SetHeaderReference(benchmark::State& state)
    {
        Diameter::Packet packet;

        Diameter::Packet::Header header;

        for (auto _ : state)
        {
            packet.header() = header;
        }
    }

    static void Header(benchmark::State& state)
    {
        Diameter::Packet packet;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(packet.header());
        }
    }

    static void AddAVP(benchmark::State& state)
    {
        auto avp = generateAVP(
            static_cast<uint32_t>(state.range(0))
        );

        for (auto _ : state)
        {
            Diameter::Packet packet;
            packet.addAVP(avp);
        }
    }

    static void AvpLast(benchmark::State& state)
    {
        Diameter::Packet packet;

        auto avp = generateAVP(
            static_cast<uint32_t>(state.range(1))
        );

        int i;
        for (i = 0; i < state.range(0); ++i)
        {
            packet.addAVP(avp);
        }

        --i;

        for (auto _ : state)
        {
            benchmark::DoNotOptimize(packet.avp(static_cast<uint32_t>(i)));
        }

        state.SetComplexityN(state.range(0));
    }
    
    static void ReplacePreLastAVP(benchmark::State& state)
    {
        Diameter::Packet packet;
        
        auto avp = generateAVP(32);
        
        int i;
        for (i = 0; i < state.range(0); ++i)
        {
            packet.addAVP(avp);
        }
        
        i -= 2;
        
        // Changing base AVP
        avp.setData(
            Diameter::AVP::Data(
                ByteArray::fromHex("00112233445566778899AABBCCDDEEFF")
            )
        );
        
        for (auto _ : state)
        {
            packet.replaceAVP(avp, static_cast<uint32_t>(i));
        }
    }
    
    static void IsValidCER(benchmark::State& state)
    {
        // It's valid CER, trust me.
        Diameter::Packet packet(binaryCER);
        
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(packet.isValid());
        }
    }
    
    static void BuildingCER(benchmark::State& state)
    {
        std::vector<uint32_t> values = {
            0,
            4,
            16777238,
            16777236,
            16777266,
            16777251,
            16777252,
            16777267,
            16777217,
            16777216,
            16777302,
            16777303,
            10,
            16777222,
            3,
            16777318,
            16777272,
            16777264,
            16777265,
            55557
        };
        
        auto originRealm = ByteArray::fromASCII("mnc002.mcc250.3gppnetwork.org");
        auto productName = ByteArray::fromASCII("ITS-Diameter");
        auto hostIpAddress = ByteArray::fromHex("0001c0a80661");
        auto hostname = ByteArray::fromASCII("dre2017");

        for (auto _ : state)
        {
            auto builder = Diameter::Packet()
                .setHeader(
                    Diameter::Packet::Header()
                        .setVersion(1)
                        .setCommandFlags(
                            Diameter::Packet::Header::Flags()
                                .setFlag(Diameter::Packet::Header::Flags::Bits::Request, true)
                        )
                        .setCommandCode(257)
                        .setApplicationId(0)
                        .setHBHIdentifier(0x7ddf9e97)
                        .setETEIdentifier(0xc15f0a0a)
                )
                .addAVP( // Origin-Host
                    Diameter::AVP()
                        .setHeader(
                            Diameter::AVP::Header()
                                .setAVPCode(264)
                                .setFlags(
                                    Diameter::AVP::Header::Flags()
                                        .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                                )
                        )
                        .setData(
                            Diameter::AVP::Data()
                                .setOctetString(hostname)
                        )
                        .updateLength()
                );

            for (auto&& value : values)
            {
                builder.addAVP(
                    Diameter::AVP()
                        .setHeader(
                            Diameter::AVP::Header()
                                .setAVPCode(258)
                                .setFlags(
                                    Diameter::AVP::Header::Flags()
                                        .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                                )
                        )
                        .setData(
                            Diameter::AVP::Data()
                                .setUnsigned32(value)
                        )
                        .updateLength()
                );
            }
            
            builder.addAVP( // Origin-Realm
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(296)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setOctetString(originRealm)
                    )
                    .updateLength()
            ).addAVP( // Product-Name
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(269)
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setOctetString(productName)
                    )
                    .updateLength()
            ).addAVP( // Inband-Security-Id
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(299)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setUnsigned32(1)
                    )
                    .updateLength()
            ).addAVP( // Inband-Security-Id
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(299)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setUnsigned32(0)
                    )
                    .updateLength()
            ).addAVP( // Host IP Address
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(257)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setOctetString(
                                hostIpAddress
                            )
                    )
                    .updateLength()
            ).addAVP( // Host IP Address
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(257)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setOctetString(
                                hostIpAddress
                            )
                    )
                    .updateLength()
            ).addAVP( // Vendor-Id
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(266)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setUnsigned32(0)
                    )
                    .updateLength()
            ).addAVP( // Firmware revision
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(267)
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setUnsigned32(1)
                    )
                    .updateLength()
            ).addAVP( // Supported-Vendor-Id
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(265)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setUnsigned32(10415)
                    )
                    .updateLength()
            ).addAVP( // Acct Application Id
                Diameter::AVP()
                    .setHeader(
                        Diameter::AVP::Header()
                            .setAVPCode(259)
                            .setFlags(
                                Diameter::AVP::Header::Flags()
                                    .setFlag(Diameter::AVP::Header::Flags::Bits::Mandatory, true)
                            )
                    )
                    .setData(
                        Diameter::AVP::Data()
                            .setUnsigned32(3)
                    )
                    .updateLength()
            );

            builder.updateLength();

            benchmark::DoNotOptimize(builder);
        }
    }
    
    static void ParsingCER(benchmark::State& state)
    {
        for (auto _ : state)
        {
            benchmark::DoNotOptimize(Diameter::Packet(binaryCER));
        }
    }
}

BENCHMARK_NS(Packet::DefaultConstruction);
BENCHMARK_NS(Packet::CopyEmpty);
BENCHMARK_NS(Packet::MoveEmpty);
BENCHMARK_NS(Packet::CopyWithData)
    ->Ranges({{1, 1 << 20}, {1, 1 << 10}})
    ->Complexity();

BENCHMARK_NS(Packet::MoveWithData)
    ->Ranges({{1, 1 << 20}, {1, 1 << 10}})
    ->Complexity();

BENCHMARK_NS(Packet::SetHeader);
BENCHMARK_NS(Packet::SetHeaderReference);
BENCHMARK_NS(Packet::Header);
BENCHMARK_NS(Packet::AddAVP)
    ->Range(1, 1 << 20)
    ->Complexity();

BENCHMARK_NS(Packet::AvpLast)
    ->Ranges({{1, 1 << 20}, {1, 1 << 10}})
    ->Complexity();

BENCHMARK_NS(Packet::ReplacePreLastAVP)
    ->Range(4, 1 << 20)
    ->Complexity();

BENCHMARK_NS(Packet::IsValidCER);
BENCHMARK_NS(Packet::BuildingCER);
BENCHMARK_NS(Packet::ParsingCER);