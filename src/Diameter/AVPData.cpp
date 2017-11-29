#include <Diameter/AVP.hpp>

Diameter::AVP::Data::Data() :
    m_value()
{

}

Diameter::AVP::Data::Data(const ByteArray& array) :
    m_value(array)
{

}

Diameter::AVP::Data::Data(Diameter::AVP::Data&& moved) noexcept :
    m_value(std::move(moved.m_value))
{

}

Diameter::AVP::Data::Data(const Diameter::AVP::Data& copied) :
    m_value(copied.m_value)
{

}

Diameter::AVP::Data& Diameter::AVP::Data::operator=(const Diameter::AVP::Data& rhs)
{
    m_value = rhs.m_value;

    return *this;
}

Diameter::AVP::Data& Diameter::AVP::Data::operator=(Diameter::AVP::Data&& rhs) noexcept
{
    m_value = std::move(rhs.m_value);

    return *this;
}

ByteArray Diameter::AVP::Data::toOctetString() const
{
    return m_value;
}

int32_t Diameter::AVP::Data::toInteger32() const
{
    if (m_value.size() != 4)
    {
        throw std::invalid_argument("Data size is not equal 4.");
    }

    return m_value.read<int32_t>(0);
}

int64_t Diameter::AVP::Data::toInteger64() const
{
    if (m_value.size() != 8)
    {
        throw std::invalid_argument("Data size is not equal 8.");
    }

    return m_value.read<int64_t>(0);
}

uint32_t Diameter::AVP::Data::toUnsigned32() const
{
    if (m_value.size() != 4)
    {
        throw std::invalid_argument("Data size is not equal 4.");
    }

    return m_value.read<uint32_t>(0);
}

uint64_t Diameter::AVP::Data::toUnsigned64() const
{
    if (m_value.size() != 8)
    {
        throw std::invalid_argument("Data size is not equal 8.");
    }

    return m_value.read<uint64_t>(0);
}

Diameter::AVP::Data& Diameter::AVP::Data::setOctetString(const ByteArray& value)
{
    m_value = value;

    return (*this);
}

Diameter::AVP::Data& Diameter::AVP::Data::setInteger32(int32_t value)
{
    m_value.clear();
    m_value.append<int32_t>(value);

    return (*this);
}

Diameter::AVP::Data& Diameter::AVP::Data::setInteger64(int64_t value)
{
    m_value.clear();
    m_value.append<int64_t>(value);

    return (*this);
}

Diameter::AVP::Data& Diameter::AVP::Data::setUnsigned32(uint32_t value)
{
    m_value.clear();
    m_value.append<uint32_t>(value);

    return (*this);
}

Diameter::AVP::Data& Diameter::AVP::Data::setUnsigned64(uint64_t value)
{
    m_value.clear();
    m_value.append<uint64_t>(value);

    return (*this);
}

Diameter::AVP::Data& Diameter::AVP::Data::addAVP(const Diameter::AVP &avp)
{
    m_value.append(avp.deploy());

    return (*this);
}

Diameter::AVP::Data::AVPContainer Diameter::AVP::Data::toAVPs() const
{
    AVPContainer container;

    if (m_value.empty())
    {
        return container;
    }

    // Trying to calculate things
    uint32_t pointer = 0;

    while (pointer < m_value.size())
    {
        // Trying to read AVP length
        if (pointer + Header::MinSize >= m_value.size())
        {
            throw std::invalid_argument("Data has no any AVPs");
        }

        AVP::Header header(m_value.cut(pointer, pointer + Header::MinSize));

        auto realLength = header.length();

        // Performing /4 padding
        realLength = (realLength + 3) & 0xFFFFFFFC;

        // Can this be size?
        if (pointer + realLength > m_value.size())
        {
            throw std::invalid_argument("Data has no any AVPs");
        }

        container.emplace_back(m_value.mid(pointer, realLength));

        pointer += realLength;
    }

    return container;
}

uint32_t Diameter::AVP::Data::size() const
{
    return m_value.size();
}

void Diameter::AVP::Data::deploy(ByteArray& byteArray) const
{
    byteArray.append(m_value);
}

ByteArray Diameter::AVP::Data::deploy() const
{
    return m_value;
}

bool Diameter::AVP::Data::isValid() const
{
    // Проверяем выравнивание
    return true;
}