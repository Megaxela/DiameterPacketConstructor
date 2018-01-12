//
// Created by megaxela on 11/28/17.
//

#pragma once

#include <cstdint>
#include <ByteArray.hpp>
#include <vector>

namespace Diameter
{
    /**
     * @brief Constructor class for building Diameter AVP.
     */
    class AVP
    {
    public:

        /**
         * @brief Constructor class for building Diameter AVPs header.
         */
        class Header
        {
        public:

            const static uint32_t MinSize = 8;
            const static uint32_t MaxSize = 12;

            using AVPCodeType = uint32_t;
            using VendorIdType = uint32_t;
            using LengthType = uint32_t;

            /**
             * @brief Constructor class for building AVPs header flags.
             */
            class Flags
            {
            public:

                using Type = uint8_t;

                /**
                 * @brief Enum type .
                 */
                enum class Bits
                {
                      VendorSpecific = (1 << 7) // 0b10000000
                    , Mandatory      = (1 << 6) // 0b01000000
                    , Protected      = (1 << 5) // 0b00100000
                };

                /**
                 * @brief Constructor.
                 */
                Flags();

                /**
                 * @brief Parsing constructor.
                 * @param array Flags value.
                 */
                explicit Flags(Type array);

                /**
                 * @brief Move constructor.
                 */
                Flags(Flags&& rhs) noexcept;

                /**
                 * @brief Copy constructor.
                 * @param rhs
                 */
                Flags(const Flags& rhs);

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
                 * @brief Method for getting flags serialized.
                 * @return Serialized.
                 */
                Type deploy() const;

                /**
                 * @brief Method for checking are flags valid.
                 * @return Flags validness.
                 */
                bool isValid() const;

                /**
                 * @brief Move operator.
                 * @param rhs Moved object.
                 * @return Reference to constructor.
                 */
                Flags& operator=(Flags&& rhs) noexcept;

                /**
                 * @brief Copy operator.
                 * @param rhs Copied obejct.
                 * @return
                 */
                Flags& operator=(const Flags& rhs);

            private:
                Type m_bits;
            };

            /**
             * @brief Default constructor.
             */
            Header();

            /**
             * @brief Parsing constructor.
             * @param array Byte array.
             * @param size Byte array size.
             */
            explicit Header(const ByteArray& byteArray);

            /**
             * @brief Move constructor.
             */
            Header(Header&& moved) noexcept;

            /**
             * @brief Copy constructor.
             * @param copied Copy.
             */
            Header(const Header& copied);

            /**
             * @brief Method for setting AVP code.
             * RFC-3588 defines field size as 32 bit (4 bytes).
             * @param code AVP code.
             * @return Reference to constructor.
             */
            Header& setAVPCode(AVPCodeType code);

            /**
             * @brief Method for getting AVP code.
             * @return AVP code.
             */
            AVPCodeType avpCode() const;

            /**
             * @brief Method for getting AVP code.
             * @return AVP code.
             */
            AVPCodeType &avpCode();

            /**
             * @brief Method for setting AVP flags.
             * @param flags AVP flags constructor.
             * @return Reference to constructor.
             */
            Header& setFlags(const Flags& flags);

            /**
             * @brief Method for getting AVP flags.
             * @return AVP flags.
             */
            Flags flags() const;

            /**
             * @brief Method for getting AVP flags.
             * @return AVP flags.
             */
            Flags& flags();

            /**
             * @brief Method for setting AVP length. (With header)
             * RFC3588 defines this field as 24 bits (3 байта).
             * Available values are [0, 16777215].
             * @param length AVP length. Available values [0, 16777215]
             * @return Reference to constructor.
             */
            Header& setAVPLength(LengthType length);

            /**
             * @brief Method for getting AVP length.
             * @return AVP length.
             */
            LengthType length() const;

            /**
             * @brief Method for getting AVP length.
             * @return AVP length.
             */
            LengthType& length();

            /**
             * @brief Method for setting Vendor Id.
             * If flag `V` is not defined, then if try
             * to set vendor id, std::invalid_argument exception
             * will be thrown.
             * @param id Vendor Id.
             * @return Reference to constructor.
             */
            Header& setVendorID(VendorIdType id);

            /**
             * @brief Method for getting Vendor Id.
             * If there is no vendor id, std::invalid_argument
             * exception will be thrown.
             * Check existence with flag `V`.
             * @return Vendor Id value.
             */
            VendorIdType vendorId() const;

            /**
             * @brief Method for checking AVP header validness.
             * @return AVP validness.
             */
            bool isValid() const;

            /**
             * @brief Method for calculating header size
             * based on internal state.
             * @return Header length.
             */
            LengthType calculateSize() const;

            /**
             * @brief Method for deploying AVP header.
             * @return Byte array.
             */
            ByteArray deploy() const;

            /**
             * @brief Method for deploying AVP header to
             * existing byte array. Byte array will be appended.
             * @param byteArray Byte array.
             */
            void deploy(ByteArray& byteArray) const;

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

        private:
            AVPCodeType m_avpCode;
            Flags m_flags;
            LengthType m_length;
            VendorIdType m_vendorId;
        };

        /**
         * @brief Constructor class for building AVP data.
         * There is no Float32 and Float64 types, because
         * C++ standard does not defines `float` and `double`
         * implementation.
         */
        class Data
        {
        public:

            using AVPContainer = std::vector<AVP>;

            /**
             * @brief Default constructor.
             */
            Data();

            /**
             * @brief Parsing constructor.
             * @param array Byte array.
             * @param size Byte array size.
             */
            explicit Data(const ByteArray& byteArray);

            /**
             * @brief Move constructor.
             */
            Data(Data&& moved) noexcept;

            /**
             * @brief Copy constructor.
             * @param copied Copied.
             */
            Data(const Data& copied);

            /**
             * @brief Method for setting byte array as data.
             * @param value Data.
             * @return Reference to constructor.
             */
            Data& setOctetString(const ByteArray &value);

            /**
             * @brief Method for translating data to octet string.
             * @return Массив байт.
             */
            ByteArray toOctetString() const;

            /**
             * @brief Method for setting signed 32 bit
             * integer.
             * @param value Value.
             * @return Constructor reference.
             */
            Data& setInteger32(int32_t value);

            /**
             * @brief Method for getting signed 32 bit integer.
             * If it's not 32 bit integer, std::invalid_argument
             * exception will be thrown.
             * @return Value.
             */
            int32_t toInteger32() const;

            /**
             * @brief Method for setting signed 64 bit
             * integer.
             * @param value Value.
             * @return Reference to constructor.
             */
            Data& setInteger64(int64_t value);

            /**
             * @brief Method for getting signed 64 bit
             * integer.
             * If it's not 64 bit integer, std::invalid_argument
             * exception will be thrown.
             * @return Value.
             */
            int64_t toInteger64() const;

            /**
             * @brief Method for setting unsigned 32 bit
             * integer.
             * @param value Value.
             * @return Reference to constructor.
             */
            Data& setUnsigned32(uint32_t value);

            /**
             * @brief Method for getting unsigned 32 bit
             * integer.
             * If it's not 32 bit integer, std::invalid_argument
             * exception will be thrown.
             * @return Value.
             */
            uint32_t toUnsigned32() const;

            /**
             * @brief Method for setting unsigned 64 bit
             * integer.
             * @param value Value.
             * @return Reference to constructor.
             */
            Data& setUnsigned64(uint64_t value);

            /**
             * @brief Method for getting unsigned 64 bit
             * integer.
             * If it's not 64 bit integer, std::invalid_argument
             * exception will be thrown.
             * @return Value.
             */
            uint64_t toUnsigned64() const;

            /**
             * @brief Method for getting avps
             * from data value. If it's impossible
             * std::invalid_argument exception will
             * be thrown.
             * @return Container with AVPs.
             */
            AVPContainer toAVPs() const;

            /**
             * @brief Method for appending AVP
             * to data.
             * @param avp AVP object.
             * @return Reference to constructor.
             */
            Data& addAVP(const AVP& avp);

            /**
             * @brief Method for adding AVPs from range
             * @tparam InputIterator Input iterator type.
             * @param first First iterator.
             * @param last Last iterator.
             * @return Reference to constructor.
             */
            template<typename InputIterator>
            Data& addAVP(InputIterator first, InputIterator last)
            {
                for (; first != last; ++first)
                {
                    addAVP(*first);
                }

                return *this;
            }

            /**
             * @brief Method for getting data size in bytes.
             * @return Size in bytes.
             */
            uint32_t size() const;

            /**
             * @brief Method for AVP data validating.
             * @return Is valid.
             */
            bool isValid() const;

            /**
             * @brief Method for deploying Data.
             * @return Data.
             */
            ByteArray deploy() const;

            /**
             * @brief Method for deploying Data.
             * Data will be appended to ByteArray.
             * @param byteArray Byte Array.
             */
            void deploy(ByteArray& byteArray) const;

            /**
             * @brief Move operator.
             * @param rhs Moved object.
             * @return Reference to constructor
             */
            Data& operator=(Data&& rhs) noexcept;

            /**
             * @brief Copy operator.
             * @param rhs Copied object.
             * @return Reference to constructor.
             */
            Data& operator=(const Data& rhs);

        private:
            ByteArray m_value;
        };

        /**
         * @brief Constructor.
         */
        AVP();

        /**
         * @brief Parsing constructor.
         * If can't parse - throw std::invalid_argument
         * exception.
         * @param array Byte array.
         */
        explicit AVP(const ByteArray &array);

        /**
         * @brief Move constructor.
         */
        AVP(AVP&& moved) noexcept;

        /**
         * @brief Copy constructor.
         * @param copied Copied.
         */
        AVP(const AVP& copied);

        /**
         * @brief Method for setting AVP's header.
         * @param header Header..
         * @return Reference to constructor.
         */
        AVP& setHeader(const Header& header);

        /**
         * @brief Method for getting AVP's header.
         * @return AVP's header.
         */
        Header header() const;

        /**
         * @brief Method for getting AVP's header.
         * @return AVP's header.
         */
        Header& header();

        /**
         * @brief Method for setting AVPs data.
         * @param data Data.
         * @return Reference to constructor.
         */
        AVP& setData(const Data& data);

        /**
         * @brief Method for getting AVPs data.
         * @return Data.
         */
        Data data() const;

        /**
         * @brief Method for getting AVPs data.
         * @return Data.
         */
        Data& data();

        /**
         * @brief Method for checking AVP's valid.
         * @return Is AVP valid.
         */
        bool isValid() const;

        /**
         * @brief Move operator.
         * @param moved Moved.
         * @return Reference to constructor.
         */
        AVP& operator=(AVP&& moved) noexcept;

        /**
         * @brief Copy operator.
         * @param copied Copied.
         * @return Reference to constructor.
         */
        AVP& operator=(const AVP& copied);

        /**
         * @brief Method for calculating actual
         * avp length.
         * @return AVP length.
         */
        Diameter::AVP::Header::LengthType calculateLength(bool includePadding) const;

        /**
         * @brief Method for updating length value.
         * @return Reference to constructor.
         */
        AVP& updateLength();

        /**
         * @brief Method for serializing AVP to
         * byte array.
         * @return Byte array.
         */
        ByteArray deploy() const;

        /**
         * @brief Method for serializing AVP to
         * byte array. AVP will be appended.
         * @param byteArray Byte array.
         */
        void deploy(ByteArray& byteArray) const;

    private:
        Header m_header;
        Data m_data;
    };
}




