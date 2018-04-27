#include <Diameter/Packet.hpp>


Diameter::Packet::Header::Header() :
    m_version(1),
    m_messageLength(0),
    m_commandFlags(0),
    m_commandCode(0),
    m_applicationId(0),
    m_hopByHop(0),
    m_endToEnd(0)
{

}


Diameter::Packet::Header::Header(const ByteArray& array) :
    Header()
{
    if (array.size() < Size)
    {
        throw std::invalid_argument("Can't parse packet header: Data is too small.");
    }

    m_version = array.read<VersionType>(0);
    m_messageLength = array.readPart<MessageLengthType>(1, 3);
    m_commandFlags = Flags(array.read<Flags::Type>(4));
    m_commandCode = array.readPart<CommandCodeType>(5, 3);
    m_applicationId = array.read<ApplicationIdType>(8);
    m_hopByHop = array.read<HBHType>(12);
    m_endToEnd = array.read<ETEType>(16);
}

Diameter::Packet::Header::Header(Diameter::Packet::Header&& moved) noexcept :
    m_version(moved.m_version),
    m_messageLength(moved.m_messageLength),
    m_commandFlags(std::move(moved.m_commandFlags)),
    m_commandCode(moved.m_commandCode),
    m_applicationId(moved.m_applicationId),
    m_hopByHop(moved.m_hopByHop),
    m_endToEnd(moved.m_endToEnd)
{

}

Diameter::Packet::Header::Header(const Diameter::Packet::Header& copied) :
    m_version(copied.m_version),
    m_messageLength(copied.m_messageLength),
    m_commandFlags(copied.m_commandFlags),
    m_commandCode(copied.m_commandCode),
    m_applicationId(copied.m_applicationId),
    m_hopByHop(copied.m_hopByHop),
    m_endToEnd(copied.m_endToEnd)
{

}

Diameter::Packet::Header& Diameter::Packet::Header::operator=(const Diameter::Packet::Header& rhs)
{
    m_version = rhs.m_version;
    m_messageLength = rhs.m_messageLength;
    m_commandFlags = rhs.m_commandFlags;
    m_commandCode = rhs.m_commandCode;
    m_applicationId = rhs.m_applicationId;
    m_hopByHop = rhs.m_hopByHop;
    m_endToEnd = rhs.m_endToEnd;

    return *this;
}

Diameter::Packet::Header& Diameter::Packet::Header::setVersion(Diameter::Packet::Header::VersionType version)
{
    m_version = version;

    return *this;
}

Diameter::Packet::Header::VersionType Diameter::Packet::Header::version() const
{
    return m_version;
}

Diameter::Packet::Header::VersionType& Diameter::Packet::Header::version()
{
    return m_version;
}

Diameter::Packet::Header& Diameter::Packet::Header::setMessageLength(Diameter::Packet::Header::MessageLengthType length)
{
    if (length > 16777215)
    {
        throw std::out_of_range("Message length value " + std::to_string(length) + " is out of range [0, 16777215]");
    }

    m_messageLength = length;

    return *this;
}

Diameter::Packet::Header::MessageLengthType Diameter::Packet::Header::messageLength() const
{
    return m_messageLength;
}

Diameter::Packet::Header::MessageLengthType& Diameter::Packet::Header::messageLength()
{
    return m_messageLength;
}

Diameter::Packet::Header& Diameter::Packet::Header::setCommandFlags(Flags flags)
{
    m_commandFlags = std::move(flags);

    return *this;
}

Diameter::Packet::Header::Flags Diameter::Packet::Header::commandFlags() const
{
    return m_commandFlags;
}

Diameter::Packet::Header::Flags& Diameter::Packet::Header::commandFlags()
{
    return m_commandFlags;
}

Diameter::Packet::Header&
Diameter::Packet::Header::setCommandCode(Diameter::Packet::Header::CommandCodeType commandCode)
{
    if (commandCode > 16777215)
    {
        throw std::out_of_range("Command code value " + std::to_string(commandCode) + " is out of range [0, 16777215]");
    }

    m_commandCode = commandCode;

    return *this;
}

Diameter::Packet::Header::CommandCodeType Diameter::Packet::Header::commandCode() const
{
    return m_commandCode;
}

Diameter::Packet::Header::CommandCodeType& Diameter::Packet::Header::commandCode()
{
    return m_commandCode;
}

Diameter::Packet::Header& Diameter::Packet::Header::setApplicationId(Diameter::Packet::Header::ApplicationIdType id)
{
    m_applicationId = id;

    return *this;
}

Diameter::Packet::Header::ApplicationIdType Diameter::Packet::Header::applicationId() const
{
    return m_applicationId;
}

Diameter::Packet::Header::ApplicationIdType& Diameter::Packet::Header::applicationId()
{
    return m_applicationId;
}

Diameter::Packet::Header& Diameter::Packet::Header::setHBHIdentifier(Diameter::Packet::Header::HBHType value)
{
    m_hopByHop = value;

    return *this;
}

Diameter::Packet::Header::HBHType Diameter::Packet::Header::hbhIdentifier() const
{
    return m_hopByHop;
}

Diameter::Packet::Header::HBHType& Diameter::Packet::Header::hbhIdentifier()
{
    return m_hopByHop;
}

Diameter::Packet::Header& Diameter::Packet::Header::setETEIdentifier(Diameter::Packet::Header::ETEType value)
{
    m_endToEnd = value;

    return *this;
}

Diameter::Packet::Header::ETEType Diameter::Packet::Header::eteIdentifier() const
{
    return m_endToEnd;
}

Diameter::Packet::Header::ETEType& Diameter::Packet::Header::eteIdentifier()
{
    return m_endToEnd;
}

bool Diameter::Packet::Header::isValid() const
{
    return m_commandFlags.isValid() &&
           m_commandCode <= 16777215 &&
           m_version == 1 ;
}

Diameter::Packet::Header& Diameter::Packet::Header::operator=(Diameter::Packet::Header&& moved) noexcept
{
    m_version = moved.m_version;
    m_messageLength = moved.m_messageLength;
    m_commandFlags = std::move(moved.m_commandFlags);
    m_commandCode = moved.m_commandCode;
    m_applicationId = moved.m_applicationId;
    m_hopByHop = moved.m_hopByHop;
    m_endToEnd = moved.m_endToEnd;

    return *this;
}

ByteArray Diameter::Packet::Header::deploy() const
{
    ByteArray result(Size);

    deploy(result);

    return result;
}

void Diameter::Packet::Header::deploy(ByteArray& byteArray) const
{
    byteArray.append(m_version);
    byteArray.appendPart(m_messageLength, 3);
    byteArray.append(m_commandFlags.deploy());
    byteArray.appendPart(m_commandCode, 3);
    byteArray.append(m_applicationId);
    byteArray.append(m_hopByHop);
    byteArray.append(m_endToEnd);
}
