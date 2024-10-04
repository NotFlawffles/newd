#include "request.hpp"
#include "compiler/text/lexer/lexer.hpp"
#include "compiler/text/parser/parser.hpp"
#include "ui/viewport.hpp"

int main() {
    setlocale(LC_ALL, "");
    wprintf(L"fetching icons...\n");

    newd::compiler::text::lexer::Lexer lexer(newd::compiler::request::read_content().substr(634));
    auto tokens = lexer.tokenize();
    auto parser = newd::compiler::text::parser::Parser(tokens);
    auto elements = parser.parse();

    newd::ui::Viewport viewport(elements);

    viewport.start();
}
