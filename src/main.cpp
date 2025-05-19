#include "compiler/lexer/lex.h"
#include "compiler/parser/parser.h"
#include "compiler/parser/token_source.h"
#include "compiler/semantic/semantic_analysis.h"


#include <iostream>

int main() {
    auto lexer = Lexer::for_string("int main(){int a = 5; int b = a + 2; return b;}");
    TokenSource source(lexer);
    Parser parser(source);
    auto program = parser.parse_program();
    SemanticAnalysis analysis(std::move(program));
    program = analysis.analyze();
    return 0;
}