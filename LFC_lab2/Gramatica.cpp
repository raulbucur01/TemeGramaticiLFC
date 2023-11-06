#include "Gramatica.h"

void Gramatica::CitireElementeGramatica(std::ifstream& input)
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

	if (!Verificare()) {
		throw std::exception("Datele sunt eronate!");
	}
}

bool Gramatica::Verificare()
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
		

	return true;
}
