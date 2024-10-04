#include "compiler/text/lexer/lexer.hpp"

namespace newd::compiler::text::lexer {
    std::vector<Token> Lexer::tokenize() {
        std::vector<Token> tokens;

        while (true) {
            auto current = tokenize_next();

            tokens.push_back(current);

            if (current.kind == Token::Kind::EndOfContent) {
                return tokens;
            }
        }
    }

    Token Lexer::tokenize_next() {
        switch (skip_whitespace()) {
            case '\"':
                return tokenize_string();

            case '\0':
                return Token(Token::Kind::EndOfContent, "<EOC>");

            default:
                if (std::isalpha(current) || current == '_' || current == '-') {
                    return tokenize_identifier();
                } else {
                    advance();
                }
        }

        return tokenize_next();
    }
    
    Token Lexer::tokenize_identifier() {
        std::string value;

        while (std::isalpha(current) || current == '_' || current == '-' || current == ':') {
            value.push_back(current);
            advance();
        }

        return Token(Token::Kind::Identifier, value);
    }

    Token Lexer::tokenize_string() {
        std::string value;

        advance();

        while (current != '\"') {
            value.push_back(current);
            advance();
        }

        return advance_with_token(Token(Token::Kind::String, value));
    }

    Token Lexer::advance_with_token(const Token& token) {
        advance();
        return token;
    }

    char Lexer::skip_whitespace() {
        while (std::isspace(current)) {
            advance();
        }

        return current;
    }

    char Lexer::advance() {
        return current = content[++index];
    }
}