#include <iostream>
#include <fstream>
#include "Grammar.h"
#include <string>
#include "PushDownAutomaton.h"



int main() {
	try {
		std::ifstream input("input2.in");
		Grammar g;
		g.ReadGrammar(input);
		g.PrintGrammar();
		if (g.IsIDC())
			std::cout << "\nE IDC!";
		else
			std::cout << "\nNu e IDC!";

		input.close();
		std::string word = g.GenerateWord();
		//g.PrintGrammar();
		//g.RemoveSimbolNotGenerating();
		//g.PrintGrammar();*/
		std::cout << "\n\nCuvantul generat este: " << word << "\n\n";
		PushDownAutomaton pda;
		pda.ReadAutomaton("input.in");
		pda.PrintAutomaton();
		pda.CheckWord("aaabbb");
		if (pda.IsDeterministic())
			std::cout << "E determinist\n";
		else
			std::cout << "Nu e determinist\n";
		
		std::cout << "\n Alege un cuvant de verificat: ";
		std::cin >> word;
		pda.CheckWord(word);
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;


}