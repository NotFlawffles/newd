#pragma once

#include <vector>
#include <cstdint>

#include "compiler/text/lexer/token.hpp"
#include "ui/element.hpp"

namespace newd::compiler::text::parser {
    class Parser {
        public:
          std::vector<lexer::Token> tokens;
          uint64_t index;
          lexer::Token current;

        public:
          Parser(const std::vector<lexer::Token>& tokens): tokens(tokens), index(0), current(tokens[index]) {}

        public:
          std::vector<ui::Element> parse();
	  ui::Element parse_next();
          lexer::Token advance();
    };
}
