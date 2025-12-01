#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <ostream>

enum class TokenType {
	TOKEN_NUMBER,
	TOKEN_LITERAL,
	TOKEN_OPERATOR,
	TOKEN_SEMICOLON
};

struct Token {
	TokenType type;

	int num;
	std::string literal;

	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

enum class LexerState {
	LEXER_DEFAULT,
	LEXER_NUMBER,
	LEXER_OPERATOR
};

class Lexer {
public:
	Lexer(std::string code);
	~Lexer();

	void tokenize();

	std::vector<Token> tokens;

	friend std::ostream& operator<<(std::ostream& os, const Lexer& lexer);

private:
	LexerState state;
	LexerState lastState;
	std::string buffer;

	std::string code;
};

#endif //LEXER_HPP