#pragma once

#include "tokenization.hpp"
#include "boa.hpp"
#include "generation.hpp"
#include <optional>


struct NodeExpr {
    Token int_lit;
};
struct NodeExit {
    NodeExpr exit;
};


class Parser {
    public:
        inline explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)){

        }

        std::optional<NodeExpr> parseExpr() {
            if (peek().has_value() && peek().value().type == TokenTypes::int_lit) {
                return NodeExpr{.int_lit = consume()};
            } else {
                return {};
            }
        }

        std::optional<NodeExit> parse() {
            std::optional<NodeExit> exitNode;
            while (peek().has_value()) {
                if (peek().value().type == TokenTypes::_ret) {
                    consume();
                    if (auto nodeExpr = parseExpr()) {
                        exitNode = NodeExit { .exit = nodeExpr.value()};
                    } else {
                        if (canColorCode()) {
                            std::cerr << "\033[1;31mBoa Exception:\033[0m\n";
                        } else {
                            std::cerr << "Boa Exception:\n";
                        }
                        std::cerr << "Invalid Expression. \n\n";
                        std::cout << "Current Usable Keywords:\nexit\n";
                        exit(1);
                    }
                    if (peek().has_value() && peek().value().type == TokenTypes::semi) {
                        consume();
                        // bsc::throwErr("Invalid Expression"); old code

                    }
                }
            }
            m_index = 0;
            return exitNode;
        }
    private:
        const std::vector<Token> m_tokens;
        [[nodiscard]] inline std::optional<Token> peek(int ahead = 1) const {
            if (m_index+ahead > m_tokens.size()) {
                return {};
            } else {
                return m_tokens.at(m_index);
            }
        }

        inline Token consume() {
            return m_tokens.at(m_index++);
        }

        const std::string m_src;
        size_t m_index = 0;
};