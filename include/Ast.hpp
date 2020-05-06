/**
 * @file Ast.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include <vector>
#include "Token.hpp"

struct Node {
    Token token;

    Node(Token &_t) : token(_t) {}

    virtual ~Node() = default;
};
using NodeList = std::vector<Node *>;

struct Operation : Node {
    Node *left, *right;

    Operation(Token _t, Node *_l, Node *_r) : Node(_t), left(_l), right(_r) {}
};

struct Assignment : Node {
    Node *left, *right;

    Assignment(Token _t, Node *_l, Node *_r) : Node(_t), left(_l), right(_r) {}
};

struct FunCall : Node {
    NodeList params;

    FunCall(Token _t, NodeList _p) : Node(_t), params(_p) {}
};

struct FunDef : Node {
    NodeList args;
    NodeList body;

    FunDef(Token _t, NodeList _a, NodeList _b)
        : Node(_t), args(_a), body(_b) {}
};
