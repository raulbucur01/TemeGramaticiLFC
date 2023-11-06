#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <set>

class Gramatica
{
private:
	std::vector<char> Vn;
	std::vector<char> Vt;
	char S;
	std::vector<std::pair<std::string, std::string>> P;
public:
	void CitireElementeGramatica(std::ifstream& input);
	bool Verificare();
};

