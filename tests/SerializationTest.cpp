
#include <gtest/gtest.h>
#include <Diameter/Packet.hpp>

static const ByteArray raw = ByteArray::fromHex(
        "010000648000011a000000007ddf9367"
        "c15ecb1200000108400000206e312e63"
        "7573746f6d2e7463702e736572766572"
        "2e636f6d000001114000000c00000000"
        "0000012840000021637573746f6d2e74"
        "657374696e672e7365727665722e636f"
        "6d000000"
);

TEST(Serialization, ToBinary)
{
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
        if (raw[i] != packet[i])
        {
            std::cout << "Raw: " << raw << std::endl;
            std::cout << "Built: " << packet << std::endl;
            std::cout << "Error at: 0x" << std::hex << i << std::endl;
        }

        ASSERT_EQ(raw[i], packet[i]);
    }
}

TEST(Serialization, FromBinary)
{
    Diameter::Packet parsed;

    ASSERT_NO_THROW(parsed = Diameter::Packet(raw));

    ASSERT_TRUE(parsed.isValid());

    ASSERT_EQ(parsed.header().version(), 1);
    ASSERT_EQ(parsed.header().messageLength(), 100);

    ASSERT_EQ(parsed.header().commandFlags().isSet(
        Diameter::Packet::Header::Flags::Bits::Request
    ), true);
    ASSERT_EQ(parsed.header().commandFlags().isSet(
        Diameter::Packet::Header::Flags::Bits::Error
    ), false);
    ASSERT_EQ(parsed.header().commandFlags().isSet(
        Diameter::Packet::Header::Flags::Bits::ReTransmitted
    ), false);
    ASSERT_EQ(parsed.header().commandFlags().isSet(
        Diameter::Packet::Header::Flags::Bits::Proxiable
    ), false);

    ASSERT_EQ(parsed.header().commandCode(), 282);
    ASSERT_EQ(parsed.header().applicationId(), 0);
    ASSERT_EQ(parsed.header().hbhIdentifier(), 0x7ddf9367);
    ASSERT_EQ(parsed.header().eteIdentifier(), 0xc15ecb12);

    ASSERT_EQ(parsed.numberOfAVPs(), 3);

    auto originHostAVP = parsed.avp(0);

    ASSERT_EQ(originHostAVP.header().avpCode(), 264);
    ASSERT_EQ(originHostAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::VendorSpecific
    ), false);
    ASSERT_EQ(originHostAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::Mandatory
    ), true);
    ASSERT_EQ(originHostAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::Protected
    ), false);

    ASSERT_EQ(originHostAVP.header().length(), 32);

    ASSERT_ANY_THROW(originHostAVP.header().vendorId());

    ASSERT_EQ(
        originHostAVP.data().toOctetString(),
        ByteArray::fromASCII("n1.custom.tcp.server.com")
    );

    auto disconnectCauseAVP = parsed.avp(1);

    ASSERT_EQ(disconnectCauseAVP.header().avpCode(), 273);
    ASSERT_EQ(disconnectCauseAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::VendorSpecific
    ), false);
    ASSERT_EQ(disconnectCauseAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::Mandatory
    ), true);
    ASSERT_EQ(disconnectCauseAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::Protected
    ), false);

    ASSERT_EQ(disconnectCauseAVP.header().length(), 12);

    ASSERT_ANY_THROW(disconnectCauseAVP.header().vendorId());

    ASSERT_EQ(disconnectCauseAVP.data().toUnsigned32(), 0);

    auto originRealmAVP = parsed.avp(2);

    ASSERT_EQ(originRealmAVP.header().avpCode(), 296);
    ASSERT_EQ(originRealmAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::VendorSpecific
    ), false);
    ASSERT_EQ(originRealmAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::Mandatory
    ), true);
    ASSERT_EQ(originRealmAVP.header().flags().isSet(
        Diameter::AVP::Header::Flags::Bits::Protected
    ), false);

    ASSERT_EQ(originRealmAVP.header().length(), 33);

    ASSERT_ANY_THROW(originRealmAVP.header().vendorId());

    ASSERT_EQ(
        originRealmAVP.data().toOctetString(),
        ByteArray::fromASCII("custom.testing.server.com")
    );

}