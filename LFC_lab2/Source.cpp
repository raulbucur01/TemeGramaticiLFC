#include <iostream>
#include <fstream>
#include "Grammar.h"
#include <string>
#include "FiniteAutomaton.h"



int main() {
	try {
		std::ifstream input("input.in");
		Grammar g;
		g.ReadGrammar(input);
		g.PrintGrammar();
		if (g.IsRegular())
			std::cout << "\nE regulata!";
		else
			std::cout << "\nNu e regulata!";

		input.close();

		g.GenerateWord();
		std::cout << "\n~~~~~~~~~~~~~\n";

		/*std::ifstream input2("input2.in");
		Grammar g2;
		g2.ReadGrammar(input2);
		g2.PrintGrammar();
		if (g2.IsRegular())
			std::cout << "\nE regulata!";
		else
			std::cout << "\nNu e regulata!";

		g2.GenerateWord();
		input2.close();*/

		FiniteAutomaton automaton(
			{ 0, 1, 2 },                
			{ 'a', 'b' },               
			{ {0, 'a', {1} },         
			  {1, 'b', {2} },
			  {2, 'a', {0} } },
			  0,                         
			  { 1, 2}                     
		);

		if (automaton.VerifyAutomaton())
		{
			automaton.PrintAutomaton();
		}

		if (automaton.CheckWord("abaa")) {
			std::cout << "Cuvantul este acceptat.\n"<<"\n";
		}
		else {
			std::cout << "Cuvantul nu este acceptat.\n"<<"\n";
		}

		if (automaton.IsDeterministic())
		{
			std::cout << "Automatul este determinist(AFD).\n";
		}
		else {
			std::cout << "Automatul este nedeterminist(AFN).\n";
		}

		std::cout << '\n';
		std::ifstream input3("input3.in");
		Grammar g3;
		g3.ReadGrammar(input3);
		FiniteAutomaton generatedAutomaton = g3.ConvertToAutomaton();
		std::cout << "Se doreste generarea unui automat finit din gramatica urmatoare:\n";
		g3.PrintGrammar();
		std::cout << "Automatul rezultat este:\n";
		generatedAutomaton.PrintAutomaton();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
	return 0;


}