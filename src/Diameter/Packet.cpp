#include <Diameter/Packet.hpp>

Diameter::Packet::Packet() :
    m_header(),
    m_avps()
{

}

Diameter::Packet::Packet(const ByteArray& byteArray) :
    m_header(),
    m_avps()
{
    m_header = Header(byteArray.mid(0, Header::Size));

    // Trying to calculate things
    uint32_t pointer = Header::Size;

    while (pointer < byteArray.size())
    {
        // Trying to read AVP length
        if (pointer + AVP::Header::MinSize >= byteArray.size())
        {
            throw std::invalid_argument("Data has no any AVPs");
        }

        AVP::Header header(
            byteArray.mid(
                pointer,
                AVP::Header::MinSize
            )
        );

        auto realLength = header.length();

        // Performing /4 padding
        realLength = (realLength + 3) & 0xFFFFFFFC;

        // Can this be size?
        if (pointer + realLength > byteArray.size())
        {
            throw std::invalid_argument("Data has no any AVPs");
        }

        m_avps.emplace_back(byteArray.mid(pointer, realLength));

        pointer += realLength;
    }

}

Diameter::Packet::Packet(Diameter::Packet&& moved) noexcept :
    m_header(std::move(moved.m_header)),
    m_avps(std::move(moved.m_avps))
{

}

Diameter::Packet::Packet(const Diameter::Packet& packet) :
    m_header(packet.m_header),
    m_avps(packet.m_avps)
{

}

Diameter::Packet& Diameter::Packet::operator=(const Diameter::Packet& copied)
{
    m_header = copied.m_header;
    m_avps = copied.m_avps;

    return *this;
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

    return m_header.messageLength() == calculateLength();

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
        length += avp.calculateLength(true);
    }

    return length;
}

ByteArray Diameter::Packet::deploy(bool checkValid) const
{
    ByteArray result(calculateLength());

    deploy(result, checkValid);

    return result;
}

void Diameter::Packet::deploy(ByteArray& byteArray, bool checkValid) const
{
    if (checkValid)
    {
        if (!isValid())
        {
            throw std::logic_error("Packet is not valid");
        }
    }

    m_header.deploy(byteArray);

    for (auto&& avp : m_avps)
    {
        avp.deploy(byteArray);
    }
}

Diameter::Packet& Diameter::Packet::updateLength()
{
    m_header.setMessageLength(calculateLength());

    return (*this);
}

Diameter::Packet& Diameter::Packet::eraseAVP(uint32_t index)
{
    m_avps.erase(
        m_avps.begin() + index
    );

    return (*this);
}
