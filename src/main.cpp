#include <fmt/format.h>
#include <include/slang.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "include/Environment.hpp"
#include "include/Evaluator.hpp"
#include "include/Lexer.hpp"
#include "include/Library.hpp"
#include "include/Orb.hpp"
#include "include/Parser.hpp"
#include "include/Prompt.hpp"
#include "include/Token.hpp"
#include "include/linenoise.h"

Prompt prompt("~~>", ';');
Environment main_env(nullptr);

void REPL() {
    while (true) {
        Lexer l(prompt.collect().c_str());
        TokenList list = l.lex();
        Parser p(list, std::string(";"));
        Evaluator e;

        for (auto node : p.parse()) {
            Primitive *result = e.visit(node, &main_env);
            if (Number *n = dynamic_cast<Number *>(result)) {
                printf("%g\n", n->value);
            } else if (Func *f = dynamic_cast<Func *>(result)) {
                printf("<function>\n");
            } else if (String *s = dynamic_cast<String *>(result)) {
                printf("%s\n", s->value.c_str());
            }
        }
    }
}

void interpreter(const char *filename) {
    std::ifstream stream(filename);
    std::stringstream buff;
    buff << stream.rdbuf();

    Lexer l(buff.str().c_str());
    TokenList list = l.lex();
    Parser p(list, std::string(";"));
    Evaluator e;

    for (auto node : p.parse()) e.visit(node, &main_env);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        REPL();
    } else {
        if (std::string(argv[argc - 1]).find(".orb") == std::string::npos) {
            fmt::print("'{}' is not an Orb file.\n", argv[argc - 1]);
            exit(0);
        }
        
        orb::Orb new_orb;
        new_orb.import_std();
        new_orb.load(argv[argc - 1]);
        new_orb.call();
    }

    return 0;
}
