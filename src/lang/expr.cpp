#include "expr.hpp"
#include "lexer.hpp"
#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>
#include <util/error.hpp>

ExprParser::ExprParser(std::vector<Token> tokens): tokens(tokens), pos(0) {}
ExprParser::~ExprParser() {}

std::unordered_map<std::string, int> op_precedence = {
	{"!",  70},
    {"~",  70},
    {"*",  60},
    {"/",  60},
    {"%",  60},
    {"+",  50},
    {"-",  50},
    {"&",  40},
    {"^",  35},
    {"|",  30},
    {"<",  25},
    {">",  25}
};

std::optional<Token> ExprParser::peek() {
	if (pos >= tokens.size()) {
		return {};
	} else {
		return tokens[pos];
	}
}

std::optional<Token> ExprParser::advance() {
	std::optional<Token> token = peek();
	pos++;
	return token;
}

int ExprParser::bp(Token token) {
	int prec;

	try {
		prec = op_precedence.at(token.literal);
	} catch (std::out_of_range) {
		return -1;
	}

	return prec;
}

std::unique_ptr<Node> ExprParser::parse(int min_prec) {
    std::optional<Token> tok_opt = advance();
    if (!tok_opt) return nullptr;
    Token token = tok_opt.value();

    std::unique_ptr<Node> left;

    if (token.type == TokenType::TOKEN_NUMBER) {
        left = std::make_unique<Number>(token.num);
    } else if (token.type == TokenType::TOKEN_OPERATOR && token.literal == "-") {
        auto rhs = parse(100);
        left = std::make_unique<UnaryExpr>(token.literal, std::move(rhs));
    } else {
        error("unexpected token");
    }

    while (true) {
        auto look_opt = peek();
        if (!look_opt) break;
        Token look = look_opt.value();

        if (look.type != TokenType::TOKEN_OPERATOR) break;

        std::string op = look.literal;
        int prec = bp(look);
        if (prec < min_prec) break;

        advance();

        auto right = parse(prec + 1);

        left = std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
    }

    return left;
}
