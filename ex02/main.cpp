#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "identify.hpp"
#include "generate.hpp"

int main() {
    std::srand(std::time(nullptr));
    Base* base = generate();
    identify(base);
    identify(*base);
    delete base;
    return 0;
}
