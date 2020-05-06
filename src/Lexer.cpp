/**
 * @file Lexer.cpp
 * @author MineBill (you@domain.com)
 * @brief Implementation of Lexer.hpp
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "include/Lexer.hpp"
#include <fmt/format.h>
#include <string.h>
#include <algorithm>
#include "include/ErrTypes.hpp"

Lexer::Lexer(const char *input) {
    ptr = new char[strlen(input) + 1];
    strcpy(ptr, input);
}

TokenList Lexer::lex() {
    TokenList ret;
    while (*ptr != '\0') {
        if (match(" \n\r\t")) {
            ptr++;
            continue;
        } else if (match("#")) {
            ptr++;
            skip_comment();
        } else if (match("(){},;=:")) {
            if (*(ptr + 1) == '=') {
                ptr++;
                ret.emplace_back(Token("operation", "=="));
            } else {
                ret.emplace_back(Token(std::string(1, *ptr), ""));
            }
        } else if (match("+-*/%")) {
            ret.emplace_back(Token("operation", std::string(1, *ptr)));
        } else if (match("\'\"")) {
            ret.emplace_back(Token("string", scan_str(*ptr)));
        } else if (isdigit(*ptr)) {
            ret.emplace_back("number", scan_num());
        } else if (*ptr == '_' || isalnum(*ptr)) {
            ret.emplace_back("symbol", scan_alnum());
        } else if (match("!<>")) {
            std::string op;
            if (*(ptr + 1) == '=') {
                op += *(ptr++);
                op += *(ptr);
                ret.emplace_back(Token("operation", op.c_str()));
            } else if (*ptr != '!') {
                ret.emplace_back(Token("operation", std::string(1, *ptr)));
            }
        }
        ptr++;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

bool Lexer::match(std::string haystack) {
    for (auto c : haystack)
        if (*ptr == c) return true;
    return false;
}

std::string Lexer::scan_str(char delim) {
    std::string ret;
    ptr++;
    while (*ptr != delim) {
        ret += *(ptr++);
    }
    return ret;
}

std::string Lexer::scan_num() {
    std::string ret;
    while (isdigit(*ptr)) {
        ret += *(ptr++);
    }
    ptr--;
    return ret;
}

std::string Lexer::scan_alnum() {
    std::string ret;
    while (*ptr == '_' || isalnum(*ptr)) {
        ret += *(ptr++);
    }
    ptr--;

    size_t und_count = std::count(ret.begin(), ret.end(), '_');
    if (und_count == ret.length()) {
        fmt::print(
            "[Error]: Variable name cannot be only '_'. \nPlease choose a new "
            "variable name.\n");
        exit(INVALID_VAR_NAME);
    }

    return ret;
}

void Lexer::skip_comment() {
    while (!match("#")) {
        ptr++;
    }
}