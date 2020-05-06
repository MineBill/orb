/**
 * @file Evaluator.cpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "include/Evaluator.hpp"
#include <fmt/format.h>
#include <algorithm>
#include "include/Ast.hpp"
#include "include/ErrTypes.hpp"
#include "include/Primitives.hpp"

Primitive *Evaluator::visit(Node *node, Environment *env) {
    auto type = node->token.type;
    auto value = node->token.value;
    if (type == "number") {
        return new Number("number", std::stof(value));
    } else if (type == "string") {
        return new String("string", value);
    } else if (Operation *op = dynamic_cast<Operation *>(node)) {
        return eval_operation(op, env);
    } else if (Assignment *op = dynamic_cast<Assignment *>(node)) {
        return eval_assignment(op, env);
    } else if (FunCall *op = dynamic_cast<FunCall *>(node)) {
        return eval_funcall(op, env);
    } else if (FunDef *op = dynamic_cast<FunDef *>(node)) {
        return eval_fundef(op, env);
    } else if (type == "symbol") {
        if (!env->contains(value)) {
            fmt::print("[Error]: Use of uninitialized variable '{}'.\n", value);
            exit(UNINITIALIZED_VAR);
        }
        return env->get(value);
    }
    return new Primitive("nil");
}

Primitive *Evaluator::eval_operation(Operation *op, Environment *env) {
    Number *lhs, *rhs;
    if (!(lhs = dynamic_cast<Number *>(visit(op->left, env)))) {
        fmt::print(
            "[Error]: Left hand side on operation '{}' is not a number.\n",
            op->token.type);
        exit(0);
    }
    if (!(rhs = dynamic_cast<Number *>(visit(op->right, env)))) {
        fmt::print(
            "[Error]: Right hand side on operation '{}' is not a number.\n",
            op->token.type);
        exit(INVALID_OP);
    }
    switch (op->token.value[0]) {
        case '+':
            return new Number("number", lhs->value + rhs->value);
        case '-':
            return new Number("number", lhs->value - rhs->value);
        case '*':
            return new Number("number", lhs->value * rhs->value);
        case '/':
            return new Number("number", lhs->value / rhs->value);
        case '%':
            return new Number("number",
                              float((int)lhs->value % (int)rhs->value));
        case '=':
            if (op->token.value[1] == '=') {
                return new Number("number", lhs->value == rhs->value);
            }
        case '!':
            if (op->token.value[1] == '=') {
                return new Number("number", lhs->value != rhs->value);
            }
        case '>':
            if (op->token.value[1] == '=') {
                return new Number("number", lhs->value >= rhs->value);
            } else {
                return new Number("number", lhs->value > rhs->value);
            }
        case '<':
            if (op->token.value[1] == '=') {
                return new Number("number", lhs->value <= rhs->value);
            } else {
                return new Number("number", lhs->value < rhs->value);
            }
    }
}

Primitive *Evaluator::eval_assignment(Assignment *ass, Environment *env) {
    auto var_name = ass->left->token.value;
    if (env->contains(var_name)) {
        // TODO: Warn about var re-assignment.
    }
    Primitive *p = visit(ass->right, env);
    if (Number *n = dynamic_cast<Number *>(p)) {
        env->set(var_name, n);
    } else if (String *s = dynamic_cast<String *>(p)) {
        env->set(var_name, s);
    } else if (Func *f = dynamic_cast<Func *>(p)) {
        env->set(var_name, f);
    }
    return p;
}

Primitive *Evaluator::eval_funcall(FunCall *call, Environment *env) {
    auto fn = call->token.value;
    if (!env->contains(fn)) {
        fmt::print("[Error]: Unknown function '{}'.\n", fn);
        exit(UNKNOWN_FN_CALL);
    }
    auto type = env->get(call->token.value)->type;
    if (type == "function") {
        Primitive *ret;
        PrimitiveList args;
        for (auto a : call->params) args.push_back(visit(a, env));

        Environment *new_env = new Environment(env);
        NodeList params;
        Func *f;
        if (f = dynamic_cast<Func *>(env->get(call->token.value))) {
            params = f->args;
        }
        std::transform(params.begin(), params.end(), args.begin(), args.end(),
                       [new_env](Node *n, Primitive *p) {
                           new_env->set(n->token.value, p);
                           return nullptr;
                       });
        for (auto p : f->body) {
            ret = visit(p, new_env);
        }
        return ret;
    } else if (type == "native") {
        Native *fun = dynamic_cast<Native *>(env->get(call->token.value));
        return fun->fn(*this, env, call->params);
    }
}

Primitive *Evaluator::eval_fundef(FunDef *def, Environment *env) {
    return new Func("function", def->body, def->args);
}

Primitive *Evaluator::eval_list(NodeList *nodes, Environment *env) {}
