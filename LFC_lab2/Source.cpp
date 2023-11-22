#include <iostream>
#include <fstream>
#include "Grammar.h"
#include <string>

int main() {
	try {
		/*std::ifstream input("input.in");
		Grammar g;
		g.ReadGrammar(input);
		g.PrintGrammar();
		if (g.IsRegular())
			std::cout << "\nE regulata!";
		else
			std::cout << "\nNu e regulata!";

		input.close();*/

		std::cout << "\n~~~~~~~~~~~~~\n";

		std::ifstream input2("input2.in");
		Grammar g2;
		g2.ReadGrammar(input2);
		g2.PrintGrammar();
		if (g2.IsRegular())
			std::cout << "\nE regulata!";
		else
			std::cout << "\nNu e regulata!";

		//g2.GenerateWord();
		input2.close();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}