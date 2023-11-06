#include <iostream>
#include <fstream>
#include "Gramatica.h"

int main() {
	try {
		std::ifstream input("input.in");
		Grammar g;
		g.ReadGrammar(input);
		g.PrintGrammar();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}