/**
 * @file Token.hpp
 * @author MineBill (you@domain.com)
 * @brief Struct to represent two strings, to avoid using tuples.
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once

#include <string>
#include <vector>
struct Token {
    std::string type;
    std::string value;
    Token(std::string &_t, std::string &_v) : type(_t), value(_v) {}
    Token(std::string &_t, const char *_v) : type(_t), value(_v) {}
    Token(const char *_t, std::string &_v) : type(_t), value(_v) {}
    Token(const char *_t, const char *_v) : type(_t), value(_v) {}

    Token(std::string _t, std::string _v) : type(_t), value(_v) {}
    Token(std::string _t, const char *_v) : type(_t), value(_v) {}
    Token(const char *_t, std::string _v) : type(_t), value(_v) {}
};

using TokenList = std::vector<Token>;