#include "include/Library.hpp"
#include <fmt/format.h>
#include <iostream>

void library::import(Environment &env) {
    env.set("if", new Native("native", _if_));
    env.set("while", new Native("native", _while_));
    env.set("p", new Native("native", _print_));
    env.set("pln", new Native("native", _println_));
    env.set("get", new Native("native", _get_));
    env.set("for", new Native("native", _for_));
}

Primitive *library::_if_(Evaluator &eval, Environment *env,
                         std::vector<Node *> args) {
    if (args.size() < 3) {
        fmt::print("if() requires 3 parameters, {} were given.\n", args.size());
        exit(0);
    }
    Primitive *ret;
    Number *cond = dynamic_cast<Number *>(eval.visit(args[0], env));
    if (cond->value != 0.0f) {
        if (Func *fn = dynamic_cast<Func *>(eval.visit(args[1], env))) {
            for (auto p : fn->body) {
                ret = eval.visit(p, env);
            }
        }
        return ret;
    } else {
        if (Func *fn = dynamic_cast<Func *>(eval.visit(args[2], env))) {
            for (auto p : fn->body) {
                ret = eval.visit(p, env);
            }
        }
        return ret;
    }
}

Primitive *library::_while_(Evaluator &eval, Environment *env,
                            std::vector<Node *> args) {
    if (args.size() < 2) {
        fmt::print("while() requires 2 parameters, {} were given.\n",
                   args.size());
        exit(0);
    }
    Primitive *ret;
    Number *cond = dynamic_cast<Number *>(eval.visit(args[0], env));
    while (cond->value != 0.0f) {
        if (Func *fn = dynamic_cast<Func *>(eval.visit(args[1], env))) {
            for (auto p : fn->body) {
                ret = eval.visit(p, env);
            }
        }
        cond = dynamic_cast<Number *>(eval.visit(args[0], env));
    }
    return ret;
}

Primitive *library::_for_(Evaluator &eval, Environment *env, std::vector<Node *> args){
    if (args.size() < 4) {
        fmt::print("while() requires 3 parameters, {} were given.\n",
                   args.size());
        exit(0);
    }
    eval.visit(args[0], env);
    Primitive *ret;
    Number *cond = dynamic_cast<Number *>(eval.visit(args[1], env));
    while (cond->value != 0.0f) {
        if (Func *fn = dynamic_cast<Func *>(eval.visit(args[3], env))) {
            for (auto p : fn->body) {
                ret = eval.visit(p, env);
            }
        }
        eval.visit(args[2], env);
        cond = dynamic_cast<Number *>(eval.visit(args[1], env));
    }
    return new Primitive("nil");
}


Primitive *library::_print_(Evaluator &eval, Environment *env,
                            std::vector<Node *> args) {
    if (Number *n = dynamic_cast<Number *>(eval.visit(args[0], env))) {
        printf("%g", n->value);
        return new Primitive("nil");
    } else if (String *s = dynamic_cast<String *>(eval.visit(args[0], env))) {
        printf("%s", s->value.c_str());
        return new Primitive("nil");
    }
}

Primitive *library::_println_(Evaluator &eval, Environment *env,
                            std::vector<Node *> args) {
    if (Number *n = dynamic_cast<Number *>(eval.visit(args[0], env))) {
        printf("%g\n", n->value);
        return new Primitive("nil");
    } else if (String *s = dynamic_cast<String *>(eval.visit(args[0], env))) {
        printf("%s\n", s->value.c_str());
        return new Primitive("nil");
    }
}

Primitive *library::_get_(Evaluator &eval, Environment *env,
                          std::vector<Node *> args) {
    std::string got;
    std::getline(std::cin, got);
    return new String("string", got);
}