#include <cstdlib>
#include <iostream>
#include <string>

inline void note(std::string text) {
	std::cout << "\033[1;34mnote: \033[0m" << text << std::endl;
}

inline void warn(std::string text) {
	std::cout << "\033[1;33mwarning: \033[0m" << text << std::endl;
}

inline void error(std::string text) {
	std::cout << "\033[1;31merror: \033[0m" << text << std::endl;
	exit(1);
}