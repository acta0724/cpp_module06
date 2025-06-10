#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
    Data data;
    data.value = 42;
    uintptr_t raw = Serializer::serialize(&data);
    Data* ptr = Serializer::deserialize(raw);
    std::cout << "data: " << &data << std::endl;
    std::cout << "ptr: " << ptr << std::endl;
    std::cout << "raw: " << raw << std::endl;
    if (ptr == &data)
        std::cout << "ptr == &data" << std::endl;
    else
		std::cout << "ptr != &data" << std::endl;
    return 0;
}
