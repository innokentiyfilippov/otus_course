#pragma once

#include <fstream>
#include <array>
#include <set>
#include <string>
#include <vector>
#include <memory>

class IpAddress
{
public:
    IpAddress(const std::string& str);
    
    bool operator< (const IpAddress& other) const;

    void print(std::ostream& out) const;
    
    template<unsigned ind>
    short get() const
    {
        static_assert(ind >= 1 && ind <= 4);
        return m_data[ind - 1];
    }
    
private:
    std::array<short, 4> m_data;
};

class IFilterRule
{
public:
    virtual bool accept(const IpAddress& address) = 0;
};

class EqualFilterRule : public IFilterRule
{
public:
    enum EPosition
    {
        eNone = 0,
        eFirst = 0x1,
        eSecond = 0x2,
        eThird = 0x4,
        eFourth = 0x8,
        eAny = eFirst | eSecond | eThird | eFourth
    };

    EqualFilterRule(EPosition pos, short val) :
        m_position(pos), m_value(val)
    {}

    bool accept(const IpAddress& address) override;

private:
    template<unsigned ind>
    bool acceptByte(const IpAddress& address, EPosition pos) const
    {
        if ((m_position & pos) && address.get<ind>() == m_value)
            return true;

        return false;
    }

private:
    EPosition m_position = eNone;
    short m_value = 0;
};

class IpAddressFilter
{
public:
    void addRule(std::unique_ptr<IFilterRule> pRule);
    void clear();

    bool accept(const IpAddress& address) const;

private:
    std::vector<std::unique_ptr<IFilterRule>> m_apRules;
};

class IpAddressContainer
{
public:
    void add(const IpAddress& address);
    void print(std::ostream& out, const IpAddressFilter* pFilter = nullptr) const;

private:
    std::multiset<IpAddress> m_addresses;
};

IpAddressContainer readFromStream(std::istream& stream);
