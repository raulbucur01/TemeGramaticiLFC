#include <iostream>
#include <fstream>
#include "Grammar.h"
#include <string>
#include "DeterministicFiniteAutomaton.h"

bool ERisValid(std::string ER) {
	// verificare sa nu fie spatii in string
	if (ER.find(' ') != std::string::npos)
		return false;

	// sa nu fie primul caracter *
	if (ER[0] == '*')
		return false;

	// sa nu fie | primul caracter
	if (ER[0] == '|')
	return false;

	// sa nu fie paranteze goale
	for (int i = 0; i < ER.length(); i++)
	{
		if (ER[i] == '(' && ER[i + 1] == ')')
			return false;
	}

	// verificare paranteze
	int count = 0;
	for (int i = 0; i < ER.length(); i++)
	{
		if (ER[i] == '(')
			count++;
		else
			if (ER[i] == ')')
				count--;
	}
	
	if (count != 0)
		return false;

	return true;
}

int main() {
	std::ifstream input("ER.in");
	std::string ER;
	std::getline(input, ER);
	if (ERisValid(ER))
		std::cout << "ER e valida \n";
	else
		std::cout << "ER NU e valida \n";

	input.close();

	try {
		/*std::ifstream input("input.in");
		Grammar g;
		g.ReadGrammar(input);
		g.PrintGrammar();
		if (g.IsRegular())
			std::cout << "\nE regulata!";
		else
			std::cout << "\nNu e regulata!";

		input.close();

		g.GenerateWord();
		std::cout << "\n~~~~~~~~~~~~~\n";*/

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

		DeterministicFiniteAutomaton automaton(
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
			// Nu a dat erori pe parcurs, automatul este valid
			std::cout << "Automatul este valid.\n" << "\n";
		}
		else {
			std::cout << "Automatul nu este valid.\n" << "\n";
			return 1;
		}

		if (automaton.CheckWord("abaa")) {
			std::cout << "Cuvantul este acceptat.\n"<<"\n";
		}
		else {
			std::cout << "Cuvantul nu este acceptat.\n"<<"\n";
		}

		if (automaton.CheckWord("aaa")) {
			std::cout << "Cuvantul este acceptat.\n" << "\n";
		}
		else {
			std::cout << "Cuvantul nu este acceptat.\n" << "\n";
		}

		std::cout << '\n';
		std::ifstream input3("input3.in");
		Grammar g3;
		g3.ReadGrammar(input3);
		DeterministicFiniteAutomaton generatedAutomaton = g3.ConvertToAutomaton();
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