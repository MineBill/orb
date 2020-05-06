/**
 * @file Lexer.hpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once

#include "Token.hpp"

class Lexer {
   public:
    Lexer(const char *input);
    /**
     * @brief Returns a list of all the tokens it found.
     *
     * @return TokenList
     */
    TokenList lex();

   private:
    /**
     * @brief Checks if the current character is in the haystack.
     *
     * @param haystack
     * @return true
     * @return false
     */
    bool match(std::string haystack);
    /**
     * @brief Moves forward until it finds @delim
     * and return the whole string.
     *
     * @param delim
     * @return std::string
     */
    std::string scan_str(char delim);
    /**
     * @brief Moves forward until it can't any more numbers
     * and returns the collected number.
     *
     * @return std::string
     */
    std::string scan_num();

    /**
     * @brief Moves forward until it can't find any more
     * alnum characters and returns the alnum string.
     *
     * @return std::string
     */
    std::string scan_alnum();

    void skip_comment();

   private:
    /**
     * @brief Points to current character in the input string.
     *
     */
    char *ptr;
};