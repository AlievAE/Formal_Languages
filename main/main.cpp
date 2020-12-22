#include "Functions.h"
#include <iostream>

int main() {
    std::string exp;
    std::string x;
    int k;
    std::cin >> exp;
    std::cin >> x;
    std::cin >>  k;
    std::cout << (solve(exp, x, k) ? "YES" : "NO") << std::endl;
}