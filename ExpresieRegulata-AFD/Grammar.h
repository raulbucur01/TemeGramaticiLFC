#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include "DeterministicFiniteAutomaton.h"
class Grammar
{
private:
	std::vector<char> Vn;
	std::vector<char> Vt;
	char S{};
	std::vector<std::pair<std::string, std::string>> P;
public:
	Grammar() = default;
	bool VerifyGrammar();
	bool IsRegular();
	void GenerateWord();
	void PrintGrammar();
	void ReadGrammar(std::ifstream& input);
	DeterministicFiniteAutomaton ConvertToAutomaton();
};

