#include <iostream>
#include <fstream>
#include "Gramatica.h"

int main() {
	try {
		std::ifstream input("input.in");
		Gramatica g;
		g.CitireElementeGramatica(input);
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;
}