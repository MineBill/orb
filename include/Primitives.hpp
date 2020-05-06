/**
 * @file Primitives.hpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include <string>
#include "Ast.hpp"

struct Primitive {
    std::string type;

    Primitive(std::string _t) : type(_t) {}

    virtual ~Primitive() = default;
};

struct Number : Primitive {
    float value;

    Number(std::string _t, float _v) : Primitive(_t), value(_v) {}
};

struct String : Primitive {
    std::string value;

    String(std::string _t, std::string _v) : Primitive(_t), value(_v) {}
};

struct Func : Primitive {
    NodeList body, args;

    Func(std::string _t, NodeList _b, NodeList _a)
        : Primitive(_t), body(_b), args(_a) {}
};

class Evaluator;
class Environment;

struct Native : Primitive {
    Primitive(*(*fn)(Evaluator&, Environment*, std::vector<Node*>));

    Native(std::string _t,
           Primitive(*(*_fn)(Evaluator&, Environment*, std::vector<Node*>)))
        : Primitive(_t), fn(_fn) {}
};

using PrimitiveList = std::vector<Primitive*>;