#include <Packet.hpp>

Diameter::Packet::Packet() :
    m_header(),
    m_avps()
{

}

Diameter::Packet::Packet(const ByteArray& byteArray)
{

}

Diameter::Packet::Packet(Diameter::Packet&& moved) noexcept :
    m_header(std::move(moved.m_header)),
    m_avps(std::move(moved.m_avps))
{

}

Diameter::Packet& Diameter::Packet::setHeader(Header header)
{
    m_header = std::move(header);

    return *this;
}

Diameter::Packet::Header Diameter::Packet::header() const
{
    return m_header;
}

Diameter::Packet::Header& Diameter::Packet::header()
{
    return m_header;
}

Diameter::Packet& Diameter::Packet::addAVP(Diameter::AVP avp)
{
    m_avps.emplace_back(std::move(avp));

    return *this;
}

Diameter::AVP Diameter::Packet::avp(uint32_t index) const
{
    if (index >= m_avps.size())
    {
        throw std::invalid_argument("Wrong AVP index.");
    }

    return m_avps[index];
}

Diameter::AVP& Diameter::Packet::avp(uint32_t index)
{
    if (index >= m_avps.size())
    {
        throw std::invalid_argument("Wrong AVP index.");
    }

    return m_avps[index];
}

Diameter::Packet& Diameter::Packet::replaceAVP(Diameter::AVP avp, uint32_t index)
{
    if (index >= m_avps.size())
    {
        throw std::invalid_argument("Wrong AVP index.");
    }

    m_avps[index] = std::move(avp);

    return *this;
}

uint32_t Diameter::Packet::numberOfAVPs() const
{
    return static_cast<uint32_t>(m_avps.size());
}

bool Diameter::Packet::isValid() const
{
    if (!m_header.isValid())
    {
        return false;
    }

    for (auto&& avp : m_avps)
    {
        if (!avp.isValid())
        {
            return false;
        }
    }

    return true;
}

Diameter::Packet& Diameter::Packet::operator=(Diameter::Packet&& moved) noexcept
{
    m_header = std::move(moved.m_header);
    m_avps = std::move(moved.m_avps);

    return *this;
}

Diameter::Packet::Header::MessageLengthType Diameter::Packet::calculateLength() const
{
    Header::MessageLengthType length = Header::Size;

    for (auto&& avp : m_avps)
    {
        length += avp.calculateLength();
    }

    return length;
}

ByteArray Diameter::Packet::deploy() const
{
    ByteArray result(calculateLength());

    deploy(result);

    return result;
}

void Diameter::Packet::deploy(ByteArray& byteArray) const
{
    m_header.deploy(byteArray);

    for (auto&& avp : m_avps)
    {
        avp.deploy(byteArray);
    }
}

Diameter::Packet& Diameter::Packet::updateLength()
{
    m_header.setMessageLength(calculateLength());
}
