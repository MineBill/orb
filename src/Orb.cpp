#include "include/Orb.hpp"

namespace orb {
bool Orb::load(const char *filename) {
    std::fstream file;
    file.open(filename);

    if (file.fail()) {
        std::cerr << "Failed to open file."
                  << "\n";
        return false;
    }

    std::string buffer, ret;
    while (std::getline(file, buffer)) {
        ret.append(buffer);
    }

    Lexer l(ret.c_str());
    program = l.lex();
    return true;
}

bool Orb::call() {
    Parser p(program, std::string(";"));
    Evaluator e;

    for (auto node : p.parse()) e.visit(node, &main_env);
}

void Orb::import_std() {
    library::import(main_env);
}
}  // namespace orb