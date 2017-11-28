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
            throw std::invalid_argument("Data is too small.");
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
