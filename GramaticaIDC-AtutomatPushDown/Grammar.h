#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include "PushDownAutomaton.h"
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
	bool IsIDC();
	void GenerateWord();
	void PrintGrammar();
	void ReadGrammar(std::ifstream& input);
	PushDownAutomaton ConvertToAutomaton();
};

