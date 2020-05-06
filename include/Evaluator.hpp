/**
 * @file Evaluator.hpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include "include/Environment.hpp"
#include "include/Ast.hpp"
#include "include/Primitives.hpp"

class Evaluator {
   public:
    Primitive *visit(Node *node, Environment *env);

    Primitive *eval_operation(Operation *op, Environment *env);
    Primitive *eval_assignment(Assignment *ass, Environment *env);
    Primitive *eval_funcall(FunCall *call, Environment *env);
    Primitive *eval_fundef(FunDef *def, Environment *env);
    Primitive *eval_list(NodeList *nodes, Environment *env);
};