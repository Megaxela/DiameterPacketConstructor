//
// Created by megaxela on 11/30/17.
//

#include <ByteArray.hpp>
#include <gtest/gtest.h>
#include <Diameter/Packet.hpp>
#include <cstdint>

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

TEST(CER, ToBinary)
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
                        .setOctetString(
                            ByteArray::fromASCII("dre2017")
                        )
                )
                .updateLength()
        );

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
                    .setOctetString(
                        ByteArray::fromASCII("mnc002.mcc250.3gppnetwork.org")
                    )
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
                    .setOctetString(
                        ByteArray::fromASCII("ITS-Diameter")
                    )
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
                        ByteArray::fromHex("0001c0a80661")
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
                        ByteArray::fromHex("0001c0a80661")
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

    auto packet = builder.deploy();

    ASSERT_EQ(binaryCER.size(), packet.size());

    for (uint32_t i = 0; i < binaryCER.size(); ++i)
    {
        if (binaryCER[i] != packet[i])
        {
            std::cout << "Raw: " << binaryCER << std::endl;
            std::cout << "Built: " << packet << std::endl;
            std::cout << "Error at: 0x" << std::hex << i << std::endl;
        }

        ASSERT_EQ(binaryCER[i], packet[i]);
    }
}