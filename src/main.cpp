#include "lang/expr.hpp"
#include <iostream>
#include <lang/lexer.hpp>
#include <sstream>
#include <fstream>
#include <util/error.hpp>

std::string readFile(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        error("failed to open " + filename);
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    if (file.fail() && !file.eof()) {
        error("failed to read " + filename);
    }

    return ss.str();
}

int main(int argc, char** argv) {
	if (argc < 2) {
		error("input file name required");
	}

	std::string code = readFile(argv[1]);

	Lexer lexer(code);

	lexer.tokenize();

	ExprParser parser(lexer.tokens);

    

    std::cout << (parser.parse()) << std::endl;

	return 0;
}