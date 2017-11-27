//
// Created by megaxela on 11/27/17.
//

#pragma once

#include <cstdint>
#include <ByteArray.hpp>
#include <vector>
#include "AVP.hpp"

namespace Diameter
{
    /**
     * @brief Constructor class for building Diameter packet.
     */
    class Packet
    {
    public:

        /**
         * @brief Constructor class for building Diameter packet header.
         */
        class Header
        {
        public:
            const static int Size = 20; //< Header size in bytes

            using VersionType = uint8_t;
            using MessageLengthType = uint32_t;
            using CommandCodeType = uint32_t;
            using ApplicationIdType = uint32_t;
            using HBHType = uint32_t;
            using ETEType = uint32_t;

            /**
             * @brief Constructor class for building Diameter packet header flags.
             */
            class Flags
            {
            public:

                using Type = uint8_t;

                enum class Bits
                {
                      Request       = 0b10000000 //< Request - if this bit is set - this packet is a request. Otherwise it's answer.
                    , Proxiable     = 0b01000000 //< Proxiable - if this bit set - this message can be proxied. Otherwise it has to be proxied locally.
                    , Error         = 0b00100000 //< Error - if this bit is set - this message contains protocol error.
                    , ReTransmitted = 0b00010000 //< Potentially re-transmitted message - eg. RFC-3588
                };

                /**
                 * @brief Default constructor.
                 */
                Flags();

                /**
                 * @brief Parsing constructor.
                 * @param flags Flags.
                 */
                explicit Flags(Type flags);

                /**
                 * @brief Method for setting bit value.
                 * @param bit Bit.
                 * @param value Value.
                 * @return Reference to constructor.
                 */
                Flags& setFlag(Bits bit, bool value);

                /**
                 * @brief Method for getting bit value.
                 * @param bit Bit.
                 * @return Value.
                 */
                bool isSet(Bits bit) const;

                /**
                 * @brief Method for validating flags. eg. RFC-3588.
                 * @return Is valid.
                 */
                bool isValid() const;

                /**
                 * @brief Method for getting flags serialized.
                 * @return Serialized.
                 */
                Type deploy() const;

            private:
                Type m_bits;
            };

            /**
             * @brief Default constructor.
             */
            Header();

            /**
             * @brief Parsing constructor.
             * @param data Byte array.
             */
            explicit Header(const ByteArray& array);

            /**
             * @brief Method for setting diameter packet version.
             * RFC-3588 defines type 8 bits long, but it must
             * have value 1.
             * @param version Version.
             * @return Reference to constructor.
             */
            Header& setVersion(VersionType version);

            /**
             * @brief Method for getting diameter packet version.
             * @return Version.
             */
            VersionType version() const;

            /**
             * @brief Method for getting diameter packet version.
             * @return Version.
             */
            VersionType& version();

            /**
             * @brief Method for setting message length in bytes (with header).
             * RFC-3588 defines, that message length type is 24 bits (3 bytes) long.
             * Possible values are [0, 16777215].
             * @param length Message length. Possible values [0, 16777215].
             * @return Reference to constructor.
             */
            Header& setMessageLength(MessageLengthType length);

            /**
             * @brief Method for getting message length.
             * @return Message length in bytes.
             */
            MessageLengthType messageLength() const;

            /**
             * @brief Method for getting message length.
             * @return Message length in bytes.
             */
            MessageLengthType& messageLength();

            /**
             * @brief Method for setting command flags.
             * @param flags Flags value.
             * @return Flags constructor.
             */
            Header& setCommandFlags(const Flags& flags);

            /**
             * @brief Method for getting command flags.
             * @return Reference to flags constructor.
             */
            Flags commandFlags() const;

            /**
             * @brief Method for getting command flags.
             * @return Reference to flags constructor.
             */
            Flags& commandFlags();

            /**
             * @brief Method for setting command code.
             * RFC-3588 defines this field as 24 bits (3 bytes),
             * Available values are [0, 16777215].
             * But RFC-3588 also defines [16777214, 16777215]
             * values for experimental usage.
             * @param commandCode Command code. [0, 16777215].
             * @return Reference to constructor.
             */
            Header& setCommandCode(CommandCodeType commandCode);

            /**
             * @brief Method for getting command code.
             * @return Command code.
             */
            CommandCodeType commandCode() const;

            /**
             * @brief Method for getting command code.
             * @return Command code.
             */
            CommandCodeType& commandCode();

            /**
             * @brief Method for setting ApplicationId value.
             * RFC-3588 defines this fields as 32 bits (4 bytes).
             * @param id ApplicationId.
             * @return Reference to constructor.
             */
            Header& setApplicationId(ApplicationIdType id);

            /**
             * @brief Method for getting ApplicationId.
             * @return ApplicationId.
             */
            ApplicationIdType applicationId() const;

            /**
             * @brief Method for getting ApplicationId.
             * @return ApplicationId.
             */
            ApplicationIdType& applicationId();

            /**
             * @brief Method for setting Hop-By-Hop identifier.
             * @param value Hop-By-Hop value.
             * @return Reference to constructor.
             */
            Header& setHBHIdentifier(HBHType value);

            /**
             * @brief Method for getting Hop-By-Hop identifier.
             * @return Hop-By-Hop value.
             */
            HBHType hbhIdentifier() const;

            /**
             * @brief Method for getting Hop-By-Hop identifier.
             * @return Hop-By-Hop value.
             */
            HBHType& hbhIdentifier();

            /**
             * @brief Method for setting End-To-End identifier.
             * @param value End-To-End value.
             * @return Reference to constructor.
             */
            Header& setETEIdentifier(ETEType value);

            /**
             * @brief Method for getting End-To-End identifier.
             * @return End-To-End value.
             */
            ETEType& eteIdentifier() const;

            /**
             * @brief Method for checking packet validness.
             * @return Packet validness.
             */
            bool isValid() const;

        private:
            VersionType m_version;
            MessageLengthType m_messageLength;
            Flags m_commandFlags;
            CommandCodeType m_commandCode;
            ApplicationIdType m_applicationId;
            HBHType m_hopByHop;
            ETEType m_endToEnd;

            std::vector<AVP> m_avps;
        };
    };
}



