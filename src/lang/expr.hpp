#ifndef EXPR_HPP
#define EXPR_HPP

#include "ast.hpp"
#include "lexer.hpp"
#include <memory>
#include <optional>

class ExprParser {
public:
	ExprParser(std::vector<Token> tokens);
	~ExprParser();

	std::unique_ptr<Node> parse(int min_prec = 0);

private:
	int pos;

	std::vector<Token> tokens;

	std::optional<Token> peek();
	std::optional<Token> advance();

	int bp(Token token);

};

#endif