#include "compiler/lexer/lex.h"
#include "compiler/parser/parser.h"
#include "compiler/parser/token_source.h"

#include <iostream>

int main() {
    auto lexer = Lexer::for_string("int main(){int a = 5; int b = a + 2; return b;}");
    TokenSource source(lexer);
    Parser parser(source);
    parser.parse_program();
    return 0;
}