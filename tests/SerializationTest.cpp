
#include <gtest/gtest.h>
#include <Packet.hpp>

TEST(Serialization, ToBinary)
{
    ByteArray raw = ByteArray::fromHex(
        "010000648000011a000000007ddf9367"
        "c15ecb1200000108400000206e312e63"
        "7573746f6d2e7463702e736572766572"
        "2e636f6d000001114000000c00000000"
        "0000012840000021637573746f6d2e74"
        "657374696e672e7365727665722e636f"
        "6d000000"
    );

    auto packet = Diameter::Packet()
        .setHeader(
            Diameter::Packet::Header()
                .setVersion(1)
                .setCommandFlags(
                    Diameter::Packet::Header::Flags()
                        .setFlag(Diameter::Packet::Header::Flags::Bits::Request, true)
                )
                .setCommandCode(282)
                .setApplicationId(0)
                .setHBHIdentifier(0x7ddf9367)
                .setETEIdentifier(0xc15ecb12)
        )
        .addAVP(
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
                            ByteArray::fromASCII("n1.custom.tcp.server.com")
                        )
                )
                .updateLength()
        )
        .addAVP(
            Diameter::AVP()
                .setHeader(
                    Diameter::AVP::Header()
                        .setAVPCode(273)
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
        )
        .addAVP(
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
                            ByteArray::fromASCII("custom.testing.server.com")
                        )
                )
                .updateLength()
        )
        .updateLength()
        .deploy();

    ASSERT_EQ(raw.size(), packet.size());

    for (uint32_t i = 0; i < raw.size(); ++i)
    {
        ASSERT_EQ(raw[i], packet[i]);
    }
}