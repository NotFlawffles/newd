#pragma once

#include <string>

namespace newd::compiler::text::lexer {
    class Token {
        public:
          enum class Kind { Colon, Identifier, String, EndOfContent } kind;
          std::string value;

        public:
          Token(const Kind& kind, const std::string& value): kind(kind), value(value) {}

          Token(): kind(Kind::EndOfContent) {}
    };
}