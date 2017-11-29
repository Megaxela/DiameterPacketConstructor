#include <Diameter/Packet.hpp>


Diameter::Packet::Header::Flags::Flags() :
    m_bits(0)
{

}

Diameter::Packet::Header::Flags::Flags(Diameter::Packet::Header::Flags::Type flags) :
    m_bits(flags)
{

}

Diameter::Packet::Header::Flags::Flags(Diameter::Packet::Header::Flags&& moved) noexcept :
    m_bits(moved.m_bits)
{

}

Diameter::Packet::Header::Flags::Flags(const Diameter::Packet::Header::Flags& flags) :
    m_bits(flags.m_bits)
{

}

Diameter::Packet::Header::Flags&
Diameter::Packet::Header::Flags::operator=(const Diameter::Packet::Header::Flags& copied)
{
    m_bits = copied.m_bits;

    return (*this);
}

Diameter::Packet::Header::Flags&
Diameter::Packet::Header::Flags::setFlag(Diameter::Packet::Header::Flags::Bits bit, bool value)
{
    // Set to true
    if (value)
    {
        m_bits |= static_cast<uint8_t>(bit);
    }
    else
    {
        m_bits &= ~static_cast<uint8_t>(bit);
    }

    return (*this);
}

bool Diameter::Packet::Header::Flags::isSet(Diameter::Packet::Header::Flags::Bits bit) const
{
    return (m_bits & static_cast<uint8_t>(bit)) == static_cast<uint8_t>(bit);
}

bool Diameter::Packet::Header::Flags::isValid() const
{
    if ((m_bits & (1 << 3)) != 0) // 0b00001000
    {
        return false;
    }

    if ((m_bits & (1 << 2)) != 0) // 0b00000100
    {
        return false;
    }

    if ((m_bits & (1 << 1)) != 0) // 0b00000010
    {
        return false;
    }

    if ((m_bits & 1) != 0) // 0b00000001
    {
        return false;
    }

    return true;
}

Diameter::Packet::Header::Flags::Type Diameter::Packet::Header::Flags::deploy() const
{
    return m_bits;
}

Diameter::Packet::Header::Flags&
Diameter::Packet::Header::Flags::operator=(Diameter::Packet::Header::Flags&& moved) noexcept
{
    m_bits = moved.m_bits;

    return *this;
}
