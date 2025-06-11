#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter {
 private:
    ScalarConverter() = delete;
    ScalarConverter(const ScalarConverter &src) = delete;
    ScalarConverter &operator=(const ScalarConverter &src) = delete;
 public:
    static void convert(const std::string &str);
};

#endif
