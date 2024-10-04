#pragma once

#include <cstdint>
#include <vector>

#include "token.hpp"

namespace newd::compiler::text::lexer {
    class Lexer {
        public:
          const std::string content;
          uint64_t index;
          char current;

        public:
          Lexer(const std::string& content): content(content), index(0), current(content[index]) {}

        public:
          std::vector<Token> tokenize();

        private:
          Token tokenize_next(), tokenize_identifier(), tokenize_string(), advance_with_token(const Token& token);

          char skip_whitespace(), advance();
    };
}