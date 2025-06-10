#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>

class ScalarConverter {
 private:
    ScalarConverter(const ScalarConverter &src);
    ScalarConverter &operator=(const ScalarConverter &src);
    static bool isPseudoLiteral(const std::string &str);
    static bool isCharLiteral(const std::string &str);
    static bool isIntLiteral(const std::string &str);
    static bool isFloatLiteral(const std::string &str);
    static bool isDoubleLiteral(const std::string &str);
    static void printChar(const double &value);
    static void printInt(const double &value);
    static void printFloat(const double &value);
    static void printDouble(const double &value);
 public:
    ScalarConverter();
    ~ScalarConverter();
    static void convert(const std::string &str);
};

#endif
