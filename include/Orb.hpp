/**
 * @file Orb.hpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-23
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <fmt/format.h>
#include <include/slang.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "include/Environment.hpp"
#include "include/Evaluator.hpp"
#include "include/Lexer.hpp"
#include "include/Library.hpp"
#include "include/Parser.hpp"
#include "include/Prompt.hpp"
#include "include/Token.hpp"
#include "include/linenoise.h"

namespace orb {

struct FootPrint {
    Evaluator &eval;
    Environment *env;
    NodeList args;
};

class Orb {
   public:
    Orb() : main_env(nullptr) {}
    bool register_fn(Primitive *(*_fn)(FootPrint));
    void import_std();

    bool load(const char *filename);
    bool call();

   private:
    Environment main_env;
    TokenList program;
};
}  // namespace orb