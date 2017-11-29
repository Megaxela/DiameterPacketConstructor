#include <Diameter/AVP.hpp>


Diameter::AVP::Header::Flags::Flags() :
    m_bits(0)
{

}

Diameter::AVP::Header::Flags::Flags(Diameter::AVP::Header::Flags::Type array) :
    m_bits(array)
{

}

Diameter::AVP::Header::Flags::Flags(Diameter::AVP::Header::Flags&& rhs) noexcept :
    m_bits(rhs.m_bits)
{

}

Diameter::AVP::Header::Flags& Diameter::AVP::Header::Flags::setFlag(Diameter::AVP::Header::Flags::Bits bit, bool value)
{
    if (value)
    {
        m_bits |= (uint8_t) bit;
    }
    else
    {
        m_bits &= ~(uint8_t) bit;
    }

    return (*this);
}

bool Diameter::AVP::Header::Flags::isSet(Diameter::AVP::Header::Flags::Bits bit) const
{
    return (m_bits & (uint8_t) bit) == (uint8_t) bit;
}

Diameter::AVP::Header::Flags::Type Diameter::AVP::Header::Flags::deploy() const
{
    return m_bits;
}

bool Diameter::AVP::Header::Flags::isValid() const
{
    // This bits are reserved and has to be 0
    if ((m_bits & 0b00010000) != 0)
    {
        return false;
    }

    if ((m_bits & 0b00001000) != 0)
    {
        return false;
    }

    if ((m_bits & 0b00000100) != 0)
    {
        return false;
    }

    if ((m_bits & 0b00000010) != 0)
    {
        return false;
    }

    if ((m_bits & 0b00000001) != 0)
    {
        return false;
    }

    return true;
}

Diameter::AVP::Header::Flags& Diameter::AVP::Header::Flags::operator=(Diameter::AVP::Header::Flags&& rhs) noexcept
{
    m_bits = rhs.m_bits;

    return *this;
}

