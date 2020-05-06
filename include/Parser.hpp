/**
 * @file Parser.hpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include "include/Ast.hpp"
#include "include/Token.hpp"
class Parser {
   public:
    Parser(TokenList &_tl, std::string _s) : tokens(_tl), stop(_s) {}
    NodeList parse();
    Node *next_expr(Node *prev);
    NodeList mult_expr(std::string, std::string);
    NodeList param_list();

   private:
    void fail(std::string);

   private:
    TokenList &tokens;
    std::string stop;
};