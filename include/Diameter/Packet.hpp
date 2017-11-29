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
                      Request       = (1 << 7) //< 0b10000000 Request - if this bit is set - this packet is a request. Otherwise it's answer.
                    , Proxiable     = (1 << 6) //< 0b01000000 Proxiable - if this bit set - this message can be proxied. Otherwise it has to be proxied locally.
                    , Error         = (1 << 5) //< 0b00100000 Error - if this bit is set - this message contains protocol error.
                    , ReTransmitted = (1 << 4) //< 0b00010000 Potentially re-transmitted message - eg. RFC-3588
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
                 * @brief Move constructor.
                 * @param moved Moved object.
                 */
                Flags(Flags&& moved) noexcept;

                /**
                 * @brief Copy constructor.
                 * @param flags Copy.
                 */
                Flags(const Flags& flags);

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

                /**
                 * @brief Move operator.
                 * @param moved Object to be moved.
                 * @return Reference to constructor.
                 */
                Flags& operator=(Flags&& moved) noexcept;

                /**
                 * @brief Copy operator.
                 * @param copied Object to be copied.
                 * @return Reference to constructor.
                 */
                Flags& operator=(const Flags& copied);

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
             * @brief Move constructor.
             * @param moved Moved element.
             */
            Header(Header&& moved) noexcept;

            /**
             * @brief Copy constructor.
             * @param copied Copied.
             */
            Header(const Header& copied);

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
            Header& setCommandFlags(Flags flags);

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
            ETEType eteIdentifier() const;

            /**
             * @brief Method for getting End-To-End identifier.
             * @return End-To-End value.
             */
            ETEType& eteIdentifier();

            /**
             * @brief Method for checking packet validness.
             * @return Packet validness.
             */
            bool isValid() const;

            /**
             * @brief Move operator.
             * @param rhs Moved object.
             * @return Reference to constructor.
             */
            Header& operator=(Header&& rhs) noexcept;

            /**
             * @brief Copy operator.
             * @param rhs Copied object.
             * @return Reference to constructor.
             */
            Header& operator=(const Header& rhs);

            /**
             * @brief Method for deploying header as byte array.
             * @return Byte array.
             */
            ByteArray deploy() const;

            /**
             * @brief Method for deploying header as byte array.
             * Header will be appended to deploy.
             * @param byteArray Byte array.
             */
            void deploy(ByteArray& byteArray) const;

        private:
            VersionType m_version;
            MessageLengthType m_messageLength;
            Flags m_commandFlags;
            CommandCodeType m_commandCode;
            ApplicationIdType m_applicationId;
            HBHType m_hopByHop;
            ETEType m_endToEnd;
        };

        /**
         * @brief Default constructor.
         */
        Packet();

        /**
         * @brief Parsing constructor.
         * @param byteArray Byte array.
         */
        explicit Packet(const ByteArray& byteArray);

        /**
         * @brief Move constructor.
         * @param moved Move constructor.
         */
        Packet(Packet&& moved) noexcept;

        /**
         * @brief Copy constructor.
         * @param packet Copy constructor.
         */
        Packet(const Packet& packet);

        /**
         * @brief Method for setting diameter packet header.
         * @param header Packet header.
         * @return Reference to constructor.
         */
        Packet& setHeader(Header header);

        /**
         * @brief Method for getting diameter packet header.
         * @return Header.
         */
        Header header() const;

        /**
         * @brief Method for getting diameter packet header.
         * @return Header.
         */
        Header& header();

        /**
         * @brief Method for adding AVP to packet.
         * @param avp AVP object.
         * @return Reference to constructor.
         */
        Packet& addAVP(AVP avp);

        /**
         * @brief Method for getting AVP by index.
         * If there is no AVP with this index,
         * std::invalid_argument exception will be
         * thrown.
         * @param index Index.
         * @return AVP.
         */
        AVP avp(uint32_t index) const;

        /**
         * @brief Method for getting AVP by index.
         * If there is no AVP with this index,
         * std::invalid_argument exception will be
         * thrown.
         * @param index Index.
         * @return AVP.
         */
        AVP& avp(uint32_t index);

        /**
         * @brief Method for replacing AVPs.
         * @param avp AVP object.
         * @param index AVP placing index.
         * @return Reference to constructor.
         */
        Packet& replaceAVP(AVP avp, uint32_t index);

        /**
         * @brief Method for getting number of AVPs.
         * @return Number of AVPs.
         */
        uint32_t numberOfAVPs() const;

        /**
         * @brief Method for checking is packet valid.
         * @return Packet validness.
         */
        bool isValid() const;

        /**
         * @brief Move operator.
         * @param moved Moved.
         * @return Reference to constructor.
         */
        Packet& operator=(Packet&& moved) noexcept;

        /**
         * @brief Copy operator.
         * @param copied Copied.
         * @return Reference to constructor.
         */
        Packet& operator=(const Packet& copied);

        /**
         * @brief Method for deploying packet as byte array.
         * @return Byte array.
         */
        ByteArray deploy() const;

        /**
         * @brief Method for calculating actual packet length.
         * @return Actual packet length.
         */
        Header::MessageLengthType calculateLength() const;

        /**
         * @brief Method for updating length in header.
         * @return Reference to constructor.
         */
        Packet& updateLength();

        /**
         * @brief Method for deploying packet as byte array.
         * Packet will be appended to deploy.
         * @param byteArray Byte array.
         */
        void deploy(ByteArray& byteArray) const;

    private:

        Header m_header;

        std::vector<AVP> m_avps;
    };
}



