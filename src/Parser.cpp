/**
 * @file Parser.cpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "include/Parser.hpp"
#include <fmt/format.h>
#include "include/ErrTypes.hpp"

NodeList Parser::parse() {
    NodeList ret;
    while (!tokens.empty()) {
        Node *node = next_expr(nullptr);
        if (node != nullptr) ret.emplace_back(node);
        tokens.pop_back();
    }
    return ret;
}

Node *Parser::next_expr(Node *prev) {
    fail(";");
    Token tok = tokens.back();
    if (stop.find(tok.type) != std::string::npos) {
        return prev;
    }
    tokens.pop_back();
    if (prev == nullptr && (tok.type == "string" || tok.type == "number" ||
                            tok.type == "symbol")) {
        return next_expr(new Node(tok));
    } else if (tok.type == "operation") {
        Node *next = next_expr(nullptr);
        return next_expr(new Operation(tok, prev, next));
    } else if (tok.type == "(") {
        NodeList params = mult_expr(",", ")");

        // if (prev->token.type != "symbol") {
        // return next_expr(new FunCall(Token("symbol", "@t"), params));
        // } else {
        return next_expr(new FunCall(prev->token, params));
        // }
    } else if (tok.type == "{") {
        NodeList params = param_list();
        NodeList body = mult_expr(";", "}");
        return next_expr(new FunDef(Token("function", ""), params, body));
    } else if (tok.type == "=") {
        if (prev->token.type != "symbol") {
            fmt::print("[Error]: Assignment on a non-symbol -> {}\n",
                       prev->token.type);
            exit(NON_SYMB_ASSIGN);
        }
        Node *next = next_expr(nullptr);
        return next_expr(new Assignment(tok, prev, next));
    }
}

NodeList Parser::param_list() {
    NodeList ret;
    if (tokens.back().type != ":") {
        return ret;
    }
    tokens.pop_back();
    if (tokens.back().type != "(") {
        return ret;
    }
    tokens.pop_back();
    ret = mult_expr(",", ")");
    for (auto param : ret) {
        if (param->token.type != "symbol") {
            fmt::print(
                "[Error]: Only symbols allowed in parameter declaration.\n");
            exit(NON_SYMB_PARAM);
        }
    }
    return ret;
}

NodeList Parser::mult_expr(std::string sep, std::string end) {
    NodeList ret;
    fail(";");
    Token tok = tokens.back();
    if (tok.type == end) {
        tokens.pop_back();
    } else {
        Parser arg_parser(tokens, sep + end);
        while (tok.type != end) {
            Node *node = arg_parser.next_expr(nullptr);
            if (node != nullptr) ret.push_back(node);
            tok = tokens.back();
            tokens.pop_back();
            fail(";");
        }
    }
    return ret;
}

void Parser::fail(std::string expected) {
    if (tokens.empty()) {
        fmt::print("[ERROR]: Found end of line, expected '{}'\n", expected);
        exit(UNEXPECTED_SYMBOL);
    }
}