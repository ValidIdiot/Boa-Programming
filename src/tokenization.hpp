#pragma once

#include <string>
#include <vector>
#include <iostream>


enum class TokenTypes {
    _ret,
    int_lit,
    semi
};



struct Token {
    TokenTypes type;
    std::optional<std::string> value {};
};

class Tokenizer {
    public:
        inline explicit Tokenizer(const std::string& src) : m_src(std::move(src)){

        };

        inline std::vector<Token> tokenize() {
            std::vector<Token> tokens;

            std::string buf;

            while (peek().has_value()) {
                if (std::isalpha(peek().value())) {
                    buf.push_back(consume());
                    while (peek().has_value() && std::isalnum(peek().value())) {
                        buf.push_back(consume());
                    }
                    if (buf == "exit") {
                        tokens.push_back({.type = TokenTypes::_ret});
                        buf.clear();
                        continue;
                    } else {
                        std::cerr << "You messed up!" << '\n';
                        exit(1);
                    }
                } else if (std::isdigit(peek().value())){
                    buf.push_back(consume());
                    while (peek().has_value() && std::isdigit(peek().value())) {
                        buf.push_back(consume());
                    }
                    tokens.push_back({.type = TokenTypes::int_lit});
                    buf.clear();
                } else if (peek().value() == ';') {
                    consume();
                    tokens.push_back({.type = TokenTypes::semi});
                    continue;
                } else if (std::isspace(peek().value())) {
                    consume();
                    continue;
                } else {
                    std::cerr << "You messed up!" << '\n';
                    exit(1);
                }
                m_index = 0;
                return tokens;
                
            }
        }
    private:

        [[nodiscard]] inline std::optional<char> peek(int offset = 0) const {
            if (m_index+offset > m_src.length()) {
                return {};
            } else {
                return m_src.at(m_index + offset);
            }
        }

        char inline consume() {
            return m_src.at(m_index++);
        }

        const std::string m_src;
        int m_index = 0;
};