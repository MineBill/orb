#pragma once
#include "include/Ast.hpp"
#include "include/Environment.hpp"
#include "include/Evaluator.hpp"
#include "include/Primitives.hpp"

namespace library {
void import(Environment &env);

Primitive *_if_(Evaluator &eval, Environment *env, std::vector<Node *> args);
Primitive *_while_(Evaluator &eval, Environment *env, std::vector<Node *> args);
Primitive *_for_(Evaluator &eval, Environment *env, std::vector<Node *> args);
Primitive *_print_(Evaluator &eval, Environment *env, std::vector<Node *> args);
Primitive *_get_(Evaluator &eval, Environment *env, std::vector<Node *> args);
Primitive *_println_(Evaluator &eval, Environment *env, std::vector<Node *> args);
}  // namespace library