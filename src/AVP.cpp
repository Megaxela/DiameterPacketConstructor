#include <AVP.hpp>

Diameter::AVP::AVP() :
    m_header(),
    m_data()
{

}

Diameter::AVP::AVP(const ByteArray& array) :
    m_header(),
    m_data()
{
    auto guessedSize = Header::MaxSize;

    if (array.length() < guessedSize)
    {
        guessedSize = Header::MinSize;

        if (array.length() < guessedSize)
        {
            throw std::invalid_argument("Can't parse AVP: Data is too small.");
        }
    }

    m_header = Header(array.cut(0, guessedSize));

    if (!m_header.flags().isSet(Header::Flags::Bits::VendorSpecific))
    {
        guessedSize = Header::MinSize;

        m_header = Header(array.cut(0, guessedSize));
    }

    m_data = Data(array.cut(guessedSize, m_header.length()));
}

Diameter::AVP::AVP(Diameter::AVP&& moved) noexcept :
    m_header(std::move(moved.m_header)),
    m_data(std::move(moved.m_data))
{

}

Diameter::AVP& Diameter::AVP::setHeader(const Diameter::AVP::Header& value)
{
    m_header = value;
    return (*this);
}

Diameter::AVP::Header Diameter::AVP::header() const
{
    return m_header;
}

Diameter::AVP::Header& Diameter::AVP::header()
{
    return m_header;
}

Diameter::AVP& Diameter::AVP::setData(const Diameter::AVP::Data& value)
{
    m_data = value;

    return (*this);
}

Diameter::AVP::Data Diameter::AVP::data() const
{
    return m_data;
}

Diameter::AVP::Data& Diameter::AVP::data()
{
    return m_data;
}

bool Diameter::AVP::isValid() const
{
    return m_header.isValid() && m_data.isValid();
}

Diameter::AVP& Diameter::AVP::operator=(Diameter::AVP&& moved) noexcept
{
    m_header = std::move(moved.m_header);
    m_data   = std::move(moved.m_data);

    return *this;
}

Diameter::AVP::Header::LengthType Diameter::AVP::calculateLength() const
{
    auto headerSize = m_header.calculateSize();
    auto dataSize = m_data.size();

    dataSize = (dataSize + 3) & 0xFFFFFFFC;

    return headerSize + dataSize;
}

Diameter::AVP& Diameter::AVP::updateLength()
{
    m_header.setAVPLength(calculateLength());

    return *this;
}

void Diameter::AVP::deploy(ByteArray& byteArray) const
{
    byteArray.append(m_header.deploy());
    byteArray.append(m_data.deploy());

    if (m_data.size() % 4)
    {
        auto requiredPadding = 4 - (m_data.size() % 4);

        byteArray.appendMultiple<uint8_t>(0, requiredPadding);
    }
}

ByteArray Diameter::AVP::deploy() const
{
    ByteArray byteArray(calculateLength());

    deploy(byteArray);

    return byteArray;
}
