#include <iostream>
#include <fstream>
#include "Grammar.h"
#include <string>

int main() {
	try {
		std::ifstream input("input.in");
		Grammar g;
		g.ReadGrammar(input);
		g.PrintGrammar();
		std::cout << g.IsRegular();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}