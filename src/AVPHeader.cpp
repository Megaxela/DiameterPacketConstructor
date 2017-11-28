#include <AVP.hpp>

Diameter::AVP::Header::Header() :
    m_avpCode(0),
    m_flags(0),
    m_length(0),
    m_vendorId(0)
{

}

Diameter::AVP::Header::Header(const ByteArray& byteArray)
{

}

Diameter::AVP::Header::Header(Diameter::AVP::Header&& moved) noexcept
{

}

Diameter::AVP::Header& Diameter::AVP::Header::setAVPCode(Diameter::AVP::Header::AVPCodeType code)
{
    return <#initializer#>;
}

Diameter::AVP::Header::AVPCodeType Diameter::AVP::Header::avpCode() const
{
    return 0;
}

Diameter::AVP::Header::AVPCodeType& Diameter::AVP::Header::avpCode()
{
    return <#initializer#>;
}

Diameter::AVP::Header& Diameter::AVP::Header::setFlags(const Diameter::AVP::Header::Flags& flags)
{
    return <#initializer#>;
}

Diameter::AVP::Header::Flags Diameter::AVP::Header::flags() const
{
    return Diameter::AVP::Header::Flags();
}

Diameter::AVP::Header::Flags& Diameter::AVP::Header::flags()
{
    return <#initializer#>;
}

Diameter::AVP::Header& Diameter::AVP::Header::setAVPLength(uint32_t length)
{
    return <#initializer#>;
}

Diameter::AVP::LengthType Diameter::AVP::Header::length() const
{
    return 0;
}

Diameter::AVP::LengthType& Diameter::AVP::Header::length()
{
    return <#initializer#>;
}

Diameter::AVP::Header& Diameter::AVP::Header::setVendorID(Diameter::AVP::Header::VendorIdType id)
{
    return <#initializer#>;
}

Diameter::AVP::Header::VendorIdType Diameter::AVP::Header::vendorId() const
{
    return 0;
}

bool Diameter::AVP::Header::isValid() const
{
    return false;
}
