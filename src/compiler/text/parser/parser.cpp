#include "compiler/text/parser/parser.hpp"

namespace newd::compiler::text::parser {
    std::vector<ui::Element> Parser::parse() {
        std::vector<ui::Element> syntax_tree;

        while (current.kind != lexer::Token::Kind::EndOfContent) {
            syntax_tree.push_back(parse_next());
        }

        return syntax_tree;
    }

    ui::Element Parser::parse_next() {
        auto name = current.value.substr(0, current.value.find(":before"));
        advance();
        auto icon = advance().value;

	if (icon[0] != '\\') icon = "\u0000";

        return ui::Element(name, icon);
    }

    lexer::Token Parser::advance() {
        return current = tokens[++index];
    }
}
