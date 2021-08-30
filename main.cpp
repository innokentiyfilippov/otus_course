#include <iostream>

#ifdef GITHUB_RUN_NUMBER
constexpr int version = GITHUB_RUN_NUMBER;
#else
constexpr int version = -1;
#endif

int main()
{
    std::cout << "Bulid: " << version << std::endl;
    std::cout << "Hello World!\n";
    system("pause");
    return 0;
}
