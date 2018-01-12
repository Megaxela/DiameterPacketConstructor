#include <Diameter/AVP.hpp>

Diameter::AVP::Header::Header() :
    m_avpCode(0),
    m_flags(0),
    m_length(0),
    m_vendorId(0)
{

}

Diameter::AVP::Header::Header(const ByteArray& byteArray) :
    m_avpCode(0),
    m_flags(0),
    m_length(0),
    m_vendorId(0)
{
    if (byteArray.size() < MinSize)
    {
        throw std::invalid_argument("Can't parse AVP Header: Data is too small.");
    }

    // Trying to parse some data
    m_avpCode = byteArray.read<AVPCodeType>(0);
    m_flags = Flags(byteArray.read<Flags::Type>(4));
    m_length = byteArray.readPart<LengthType>(5, 3);

    // Checking flags and then trying to read vendor id if
    // needed
    if (m_flags.isSet(Flags::Bits::VendorSpecific))
    {
        if (byteArray.size() < MaxSize)
        {
            return;
        }

        m_vendorId = byteArray.read<VendorIdType>(8);
    }
}

Diameter::AVP::Header::Header(Diameter::AVP::Header&& moved) noexcept :
    m_avpCode(moved.m_avpCode),
    m_flags(std::move(moved.m_flags)),
    m_length(moved.m_length),
    m_vendorId(moved.m_vendorId)
{

}

Diameter::AVP::Header::Header(const Diameter::AVP::Header& copied) :
    m_avpCode(copied.m_avpCode),
    m_flags(copied.m_flags),
    m_length(copied.m_length),
    m_vendorId(copied.m_vendorId)
{

}

Diameter::AVP::Header& Diameter::AVP::Header::operator=(const Diameter::AVP::Header& rhs)
{
    m_avpCode = rhs.m_avpCode;
    m_flags = rhs.m_flags;
    m_length = rhs.m_length;
    m_vendorId = rhs.m_vendorId;

    return *this;
}

Diameter::AVP::Header& Diameter::AVP::Header::setAVPCode(Diameter::AVP::Header::AVPCodeType code)
{
    m_avpCode = code;

    return *this;
}

Diameter::AVP::Header::AVPCodeType Diameter::AVP::Header::avpCode() const
{
    return m_avpCode;
}

Diameter::AVP::Header::AVPCodeType& Diameter::AVP::Header::avpCode()
{
    return m_avpCode;
}

Diameter::AVP::Header& Diameter::AVP::Header::setFlags(const Diameter::AVP::Header::Flags& flags)
{
    m_flags = flags;

    return *this;
}

Diameter::AVP::Header::Flags Diameter::AVP::Header::flags() const
{
    return m_flags;
}

Diameter::AVP::Header::Flags& Diameter::AVP::Header::flags()
{
    return m_flags;
}

Diameter::AVP::Header& Diameter::AVP::Header::setAVPLength(LengthType length)
{
    m_length = length;

    return *this;
}

Diameter::AVP::Header::LengthType Diameter::AVP::Header::length() const
{
    return m_length;
}

Diameter::AVP::Header::LengthType& Diameter::AVP::Header::length()
{
    return m_length;
}

Diameter::AVP::Header& Diameter::AVP::Header::setVendorID(Diameter::AVP::Header::VendorIdType id)
{
    if (!m_flags.isSet(Flags::Bits::VendorSpecific))
    {
        throw std::invalid_argument("Vendor specific bit is not set.");
    }

    m_vendorId = id;

    return *this;
}

Diameter::AVP::Header::VendorIdType Diameter::AVP::Header::vendorId() const
{
    if (!m_flags.isSet(Flags::Bits::VendorSpecific))
    {
        throw std::invalid_argument("Vendor specific bit is not set.");
    }

    return m_vendorId;
}

bool Diameter::AVP::Header::isValid() const
{
    return m_flags.isValid();
}

Diameter::AVP::Header& Diameter::AVP::Header::operator=(Diameter::AVP::Header&& moved) noexcept
{
    m_avpCode = moved.m_avpCode;
    m_flags = std::move(moved.m_flags);
    m_length = moved.m_length;
    m_vendorId = moved.m_vendorId;

    return *this;
}

Diameter::AVP::Header::LengthType Diameter::AVP::Header::calculateSize() const
{
    if (m_flags.isSet(Flags::Bits::VendorSpecific))
    {
        return MaxSize;
    }
    else
    {
        return MinSize;
    }
}

ByteArray Diameter::AVP::Header::deploy() const
{
    ByteArray byteArray(calculateSize());

    deploy(byteArray);

    return byteArray;
}

void Diameter::AVP::Header::deploy(ByteArray& byteArray) const
{
    byteArray.append(m_avpCode);
    byteArray.append(m_flags.deploy());
    byteArray.appendPart(m_length, 3);

    if (m_flags.isSet(Flags::Bits::VendorSpecific))
    {
        byteArray.append(m_vendorId);
    }
}
