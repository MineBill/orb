#include <fmt/format.h>

#include <include/slang.h>
#include "include/Lexer.hpp"
#include "include/Token.hpp"

int main(int argc, char *argv[]) {
    Lexer lexer("______ = 2;");
    TokenList list = lexer.lex();
    for(auto token: list){
        fmt::print("Token = ({},{})\n", token.type, token.value);
    }

    return 0;
}
