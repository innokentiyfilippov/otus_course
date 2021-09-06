#include <iostream>
#include <cassert>
#include <cstring>

#include "ip_filter.h"

#ifdef GITHUB_RUN_NUMBER
constexpr int version = GITHUB_RUN_NUMBER;
#else
constexpr int version = -1;
#endif

void test_helloworld()
{
    std::cout << "Bulid: " << version << std::endl;
    std::cout << "Hello World!\n";
}

void test_ipfilter()
{
    //std::fstream in("ip_filter.tsv");
    IpAddressContainer container;
    try
    {
        container = readFromStream(std::cin);
    }
    catch(...)
    {
        std::cout << "Invalid data format";
        return;
    }

    // print all
    container.print(std::cout);
    
    // first = 1
    IpAddressFilter filter;
    filter.addRule(std::make_unique<EqualFilterRule>(EqualFilterRule::eFirst, 1));
    container.print(std::cout, &filter);

    // first = 46, second = 70
    filter.clear();
    filter.addRule(std::make_unique<EqualFilterRule>(EqualFilterRule::eFirst, 46));
    filter.addRule(std::make_unique<EqualFilterRule>(EqualFilterRule::eSecond, 70));
    container.print(std::cout, &filter);

    // any = 46
    filter.clear();
    filter.addRule(std::make_unique<EqualFilterRule>(EqualFilterRule::eAny, 46));
    container.print(std::cout, &filter);
}

int main(int argc, char** argv)
{
    if (argc == 1)
        test_helloworld();
    else
    {
        if (strcmp(argv[1], "--hello") == 0)
            test_helloworld();
        else if (strcmp(argv[1], "--ipfilter") == 0)
            test_ipfilter();
        else
            assert(false && "incorrect argument");
    }

    system("pause");
    return 0;
}
