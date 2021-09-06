#include "ip_filter.h"

#include <iostream>
#include <fstream>
#include <cassert>

IpAddress::IpAddress(const std::string& str)
{
    unsigned ind = 0, startPos = 0;
    for (size_t endPos = str.find('.'); endPos != -1; endPos = str.find('.', startPos))
    {
        assert(ind < 3);
        m_data[ind++] = std::stoi(str.substr(startPos, endPos - startPos));
        startPos = static_cast<unsigned>(endPos) + 1;
    }

    assert(ind == 3);
    m_data[ind] = std::stoi(str.substr(startPos));
}

bool IpAddress::operator< (const IpAddress& other) const
{
    for (size_t i = 0; i < 4; i++)
    {
        if (m_data[i] != other.m_data[i])
            return m_data[i] > other.m_data[i];
    }

    return false;
}

void IpAddress::print(std::ostream& out) const
{
    out << m_data[0] << "." << m_data[1] << "." << m_data[2] << "." << m_data[3] << std::endl;
}

bool EqualFilterRule::accept(const IpAddress& address)
{
    return acceptByte<1>(address, eFirst) ||
           acceptByte<2>(address, eSecond) ||
           acceptByte<3>(address, eThird) ||
           acceptByte<4>(address, eFourth);
}

void IpAddressFilter::addRule(std::unique_ptr<IFilterRule> pRule)
{
    m_apRules.emplace_back(std::move(pRule));
}

void IpAddressFilter::clear()
{
    m_apRules.clear();
}

bool IpAddressFilter::accept(const IpAddress& address) const
{
    for (const auto& pRule : m_apRules)
        if (!pRule->accept(address))
            return false;

    return true;
}

void IpAddressContainer::add(const IpAddress& address)
{
    m_addresses.insert(address);
}

void IpAddressContainer::print(std::ostream& out, const IpAddressFilter* pFilter /*= nullptr*/) const
{
    for (const auto& address : m_addresses)
    {
        if (!pFilter || pFilter->accept(address))
            address.print(out);
    }
}

IpAddressContainer readFromStream(std::istream& stream)
{
    IpAddressContainer filter;
    std::string input, dummy;
    while (stream >> input >> dummy >> dummy)
        filter.add(IpAddress(input));

    return filter;
}
