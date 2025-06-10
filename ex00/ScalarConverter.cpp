#include "ScalarConverter.hpp"

#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdexcept>

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

bool ScalarConverter::isPseudoLiteral(const std::string &str) {
    return str == "nan" || str == "nanf" || str == "+inf" || str == "+inff" || str == "-inf" || str == "-inff";
}

bool ScalarConverter::isCharLiteral(const std::string &str) {
    return (str.size() == 3 && str[0] == '\'' && str[2] == '\'' && std::isprint(str[1]));
}

bool ScalarConverter::isIntLiteral(const std::string &str) {
    size_t i = 0;
    if (str[i] == '-' || str[i] == '+')
        ++i;
    while (i < str.size()) {
        if (!std::isdigit(str[i]))
            return false;
        ++i;
    }
    return true;
}

bool ScalarConverter::isFloatLiteral(const std::string &str) {
    if (str.back() != 'f')
        return false;
    std::string tmp = str.substr(0, str.size() - 1);
    return (tmp.find('.') != std::string::npos || isPseudoLiteral(str));
}

bool ScalarConverter::isDoubleLiteral(const std::string &str) {
    return (str.find('.') != std::string::npos && str.back() != 'f');
}

void ScalarConverter::printChar(const double &value) {
    std::cout << "char: ";
    if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max()) {
        std::cout << "impossible" << std::endl;
    } else {
        char c = static_cast<char>(value);
        if (std::isprint(c))
            std::cout << "'" << c << "'" << std::endl;
        else
            std::cout << "non displayable" << std::endl;
    }
}

void ScalarConverter::printInt(const double &value) {
    std::cout << "int: ";
    if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << static_cast<int>(value) << std::endl;
    }
}

void ScalarConverter::printFloat(const double &value) {
    std::cout << "float: ";
    if (std::isnan(value)) {
        std::cout << "nanf" << std::endl;
    } else if (std::isinf(value)) {
        if (value > 0)
            std::cout << "+inff" << std::endl;
        else
            std::cout << "-inff" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision((fmod(value, 1) == 0 ? 1 : 1)) << static_cast<float>(value) << "f" << std::endl;
    }
}

void ScalarConverter::printDouble(const double &value) {
    std::cout << "double: ";
    if (std::isnan(value)) {
        std::cout << "nan" << std::endl;
    } else if (std::isinf(value)) {
        if (value > 0)
            std::cout << "+inf" << std::endl;
        else
            std::cout << "-inf" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision((fmod(value, 1) == 0 ? 1 : 1)) << value << std::endl;
    }
}

void ScalarConverter::convert(const std::string &str) {
    double value;
    try {
        if (isPseudoLiteral(str)) {
            if (str.back() == 'f')
                value = std::stof(str);
            else
                value = std::stod(str);
        } else if (isCharLiteral(str)) {
            value = static_cast<double>(str[1]);
        } else if (isIntLiteral(str)) {
            value = std::stoi(str);
        } else if (isFloatLiteral(str)) {
            value = std::stof(str);
        } else if (isDoubleLiteral(str)) {
            value = std::stod(str);
        } else {
            throw std::invalid_argument("Invalid literal");
        }
    }
    catch (...) {
        std::cout << "Invalid literal" << std::endl;
        return;
    }
    printChar(value);
    printInt(value);
    printFloat(value);
    printDouble(value);
}
