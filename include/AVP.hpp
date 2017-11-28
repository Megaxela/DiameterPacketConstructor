//
// Created by megaxela on 11/28/17.
//

#pragma once

#include <cstdint>
#include <ByteArray.hpp>

namespace Diameter
{
    /**
     * @brief Constructor class for building Diameter AVP.
     */
    class AVP
    {
    public:

        using LengthType = uint32_t;

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
                    VendorSpecific = 0b10000000, Mandatory = 0b01000000, P = 0b00100000
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
                 * @brief Метод для проверки корректности
                 * AVP.
                 * @return Корректность AVP.
                 */
                bool isValid() const;

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
            Header& setAVPLength(uint32_t length);

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
             * @return Value.
             */
            uint64_t toUnsigned64() const;

            /**
             * @brief Method for adding AVP's as data.
             * @param avp AVP constructor.
             * @return Reference to constructor.
             */
            Data& addAVP(AVP avp);

            /**
             * @brief Method for counting number of
             * possible AVP's
             * @return Number of AVPs. If it's impossible
             * to count AVPs, std::invalid_argument exception
             * will be thrown.
             */
            uint32_t numberOfAVPs() const;

            /**
             * @brief Method for getting AVP by index. If
             * there is no such index, std::invalid_argument exception
             * will be thrown.
             * @param index Индекс AVP.
             * @return AVP.
             */
            AVP avp(uint32_t index) const;

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

    private:
        Header m_header;
        Data m_data;
    };
}




