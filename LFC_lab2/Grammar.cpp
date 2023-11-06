#include "Grammar.h"

void Grammar::ReadGrammar(std::ifstream& input)
{
	int VnSize;
	input >> VnSize;
	
	for (int i = 0; i < VnSize; i++)
	{
		char elem; 
		input >> elem;
		Vn.push_back(elem); 
	}

	int VtSize;
	input >> VtSize;

	for (int i = 0; i < VtSize; i++)
	{
		char elem; 
		input >> elem;  
		Vt.push_back(elem); 
	}

	input >> S;
	int noProd;
	input >> noProd;
	for (int i = 0; i < noProd; i++) {
		std::pair<std::string, std::string> elem;
		input >> elem.first;
		input >> elem.second;
		P.push_back(elem);
	}

	if (!VerifyGrammar()) {
		throw std::exception("Datele sunt eronate!");
	}
}

bool Grammar::VerifyGrammar()
{	
	// (1) VN intersectat cu VT = 0
	for (int i = 0; i < Vn.size(); i++)
	{
		if (std::find(Vt.begin(), Vt.end(), Vn[i]) != Vt.end())
			return false;
	}

	// (2) S apartine VN 
	for (int i = 0; i < Vn.size(); i++)
	{
		if (std::find(Vn.begin(), Vn.end(), S) == Vn.end())
			return false;
	}

	// (3) pentru fiecare regulă, membrul stâng conține cel puțin un neterminal 
	bool contine = false;
	for (int i = 0; i < P.size(); i++)
	{
		contine = false;
		for (int j = 0; j < Vn.size(); j++)
		{
			if (P[i].first.find(Vn[j]) < P[i].first.length()) {
				contine = true;
				break;
			}
		}
		if (!contine)
			return false;
	}
	
	// (4) există cel puțin o producție care are în stânga doar S
	bool exista = false;
	for (int i = 0; i < P.size(); i++)
	{
		if (P[i].first.length() == 1 && P[i].first[0] == 'S')
		{
			exista = true;
			break;
		}
	}
	if (!exista)
		return false;

	// (5) fiecare producție conține doar elemente din VN și VT
	for (int i = 0; i < P.size(); i++)
	{
		std::string stanga = P[i].first;
		for (int j = 0; j < stanga.length(); j++)
			if (std::find(Vn.begin(), Vn.end(), stanga[j]) == Vn.end() && std::find(Vt.begin(), Vt.end(), stanga[j]) == Vt.end())
				return false;

		std::string dreapta = P[i].second;
		for (int j = 0; j < dreapta.length(); j++)
			if (std::find(Vn.begin(), Vn.end(), dreapta[j]) == Vn.end() && std::find(Vt.begin(), Vt.end(), dreapta[j]) == Vt.end())
				return false;
	}

	return true;
}

void Grammar::PrintGrammar()
{
	std::cout << "Vn = { ";
	for (int i = 0; i < Vn.size(); i++)
	{
		std::cout << Vn[i] << " ";
	}
	std::cout << "}\n";

	std::cout << "Vt = { ";
	for (int i = 0; i < Vt.size(); i++)
	{
		std::cout << Vt[i] << " ";
	}
	std::cout << "}\n";

	std::cout << "S = " << S << "\n";

	std::cout << "P: \n";
	for (size_t i = 0; i < P.size(); i++)
	{
		std::cout << "(" << i + 1 << ") " << P[i].first << " -> " << P[i].second << "\n";
	}
}
