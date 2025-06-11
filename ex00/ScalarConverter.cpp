#include "ScalarConverter.hpp"

#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdexcept>

bool isPseudoLiteral(const std::string &str) {
    return str == "nan" || str == "nanf" || str == "+inf" || \
        str == "+inff" || str == "-inf" || str == "-inff";
}

bool isCharLiteral(const std::string &str) {
    if (str.size() == 1 && std::isprint(str[0])) {
        return true;
    }
    return false;
}

bool isIntLiteral(const std::string &str) {
    if (str.empty())
        return false;
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

bool isFloatLiteral(const std::string &str) {
    if (str.empty())
        return false;
    if (str.back() != 'f')
        return false;
    std::string tmp = str.substr(0, str.size() - 1);
    bool has_digit = false;
    int dot_count = 0;
    size_t i = 0;
    if (tmp[0] == '-' || tmp[0] == '+')
        ++i;
    for (; i < tmp.size(); ++i) {
        if (std::isdigit(tmp[i])) {
            has_digit = true;
        } else if (tmp[i] == '.') {
            dot_count++;
        } else {
            return false;
        }
    }
    if (dot_count > 1)
        return false;
    return has_digit;
}

bool isDoubleLiteral(const std::string &str) {
    if (str.empty())
        return false;
    if (str.back() == 'f')
        return false;
    bool has_digit = false;
    int dot_count = 0;
    size_t i = 0;
    if (str[0] == '-' || str[0] == '+')
        ++i;
    for (; i < str.size(); ++i) {
        if (std::isdigit(str[i])) {
            has_digit = true;
        } else if (str[i] == '.') {
            dot_count++;
        } else {
            return false;
        }
    }
    if (dot_count > 1)
        return false;
    return has_digit;
}

void printChar(const double &value) {
    std::cout << "char: ";
    if (std::isnan(value) || std::isinf(value) || \
        value < std::numeric_limits<char>::min() || \
        value > std::numeric_limits<char>::max()) {
        std::cout << "impossible" << std::endl;
    } else {
        char c = static_cast<char>(value);
        if (std::isprint(c))
            std::cout << "'" << c << "'" << std::endl;
        else
            std::cout << "Non displayable" << std::endl;
    }
}

void printInt(const double &value) {
    std::cout << "int: ";
    if (std::isnan(value) || std::isinf(value) || \
        value < std::numeric_limits<int>::min() || \
        value > std::numeric_limits<int>::max()) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << static_cast<int>(value) << std::endl;
    }
}

void printFloat(const double &value) {
    std::cout << "float: ";
    if (std::isnan(value)) {
        std::cout << "nanf" << std::endl;
    } else if (std::isinf(value)) {
        if (value > 0)
            std::cout << "+inff" << std::endl;
        else
            std::cout << "-inff" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision(1) \
            << static_cast<float>(value) << "f" << std::endl;
    }
}

void printDouble(const double &value) {
    std::cout << "double: ";
    if (std::isnan(value)) {
        std::cout << "nan" << std::endl;
    } else if (std::isinf(value)) {
        if (value > 0)
            std::cout << "+inf" << std::endl;
        else
            std::cout << "-inf" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision(1) \
            << value << std::endl;
    }
}

void ScalarConverter::convert(const std::string &str) {
    double value;
    try {
        if (isPseudoLiteral(str)) {
            value = std::stod(str);
        } else if (isCharLiteral(str)) {
            value = static_cast<double>(str[0]);
        } else if (isIntLiteral(str)) {
            value = std::stod(str);
        } else if (isFloatLiteral(str)) {
            value = std::stod(str.substr(0, str.size() - 1));
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
