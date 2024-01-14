﻿#include "Grammar.h"

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

void Grammar::RemoveInaccessibleSymbols()
{
	std::vector<char> V, V1;
	V.push_back(S);
	V1.push_back(S);
	bool ok = false;
	while (ok == false)
	{
		for (auto elem : V)
		{
			for (auto prod : P)

				if (prod.first[0] == elem)
				{
					for (int i = 0; i < prod.second.size(); i++)
					{
						if (std::find(Vn.begin(), Vn.end(), prod.second[i]) != Vn.end())
						{
							auto it = std::find(V1.begin(), V1.end(), prod.second[i]);
							if (it == V1.end())
								V1.push_back(prod.second[i]);
						}
					}
				}

		}
		if (V.size() == V1.size())
			ok = true;
		V.clear();
		V = V1;

	}
	std::vector < std::pair<std::string, std::string>> prodNou;
	for (int i = 0; i < P.size(); i++)
	{
		auto it = std::find(V.begin(), V.end(), P[i].first[0]);
		if (it != V.end())
		{
			prodNou.push_back(P[i]);
		}
	}

	P = prodNou;
}

void Grammar::RemoveSimbolNotGenerating()
{
	std::vector<std::pair<std::string, std::string>>prodNou;
	std::vector<char> V, V1;
	for (int i = 0; i < P[0].second.size(); i++)
	{
		if (std::find(Vn.begin(), Vn.end(), P[0].second[i]) != Vn.end())
			V1.push_back(P[0].second[i]);

	}
	bool ok = false;
	V = V1;
	while (ok == false)
	{
		for (auto prod : P)
		{
			for (auto letter : prod.second)
			{
				if (std::find(Vn.begin(), Vn.end(), letter) != Vn.end())
				{
					if (std::find(V.begin(), V.end(), letter) == V.end())
					{
						V.push_back(letter);
					}
				}
			}
		}
		if (V.size() == V1.size())
		{
			ok = true;
		}
		V1.clear();
		V1 = V;
	}
	for (int i = 0; i < P.size(); i++)
	{
		if (std::find(V.begin(), V.end(), P[i].first[0]) != V.end())
		{
			bool onlyNeterminalsAccepted = true;
			for (auto letter : P[i].second)
			{
				if (std::find(Vn.begin(), Vn.end(), letter) != Vn.end())
					if (std::find(V.begin(), V.end(), letter) == V.end())
					{
						onlyNeterminalsAccepted = false;


					}
			}
			if (onlyNeterminalsAccepted == true)
			{
				prodNou.push_back(P[i]);
			}
		}
		else
		{

			bool onlyTerminal = true;
			for (auto letter : P[i].second)
			{
				if (std::find(Vn.begin(), Vn.end(), letter) != Vn.end())
					onlyTerminal = false;
			}
			if (onlyTerminal == true)
			{
				prodNou.push_back(P[i]);
			}
		}
	}
	P = prodNou;
}

//void Grammar::RemoveSymbolRename(std::vector<std::pair<std::string, std::string>> prod, std::vector<std::pair<std::string, std::string>>redenumiri)
//{
//	if (redenumiri.size() == 0)
//	{
//		return m_productii;
//	}
//
//	std::vector<std::pair<std::string, std::string>> prodNou = P;
//
//	for (auto redenumire : redenumiri)
//	{
//		std::string first = redenumire.first;
//		std::string second = redenumire.second;
//
//		for (auto& prod : m_productii)
//		{
//			if (prod.first == second)
//			{
//				prodNou.push_back({ first, prod.second });
//			}
//		}
//	}
//
//	for (int i = 0; i < prodNou.size(); i++)
//	{
//		if (prodNou[i].second.size() == 1)
//		{
//			if (std::find(Vn.begin(),Vn.end(), prodNou[i].second[0]) != Vn.end())
//			{
//				prodNou.erase(prodNou.begin() + i, prodNou.begin() + i + 1);
//			}
//		}
//	}
//	P = prodNou;
//}



bool Grammar::VerifyGrammar()
{
	// (1) VN intersectat cu VT = 0
	for (int i = 0; i < Vn.size(); i++)
	{
		if (std::find(Vt.begin(), Vt.end(), Vn[i]) != Vt.end())
			return false;
	}

	// (2) S apartine VN 
	if (std::find(Vn.begin(), Vn.end(), S) == Vn.end())
		return false;


	// (3) pentru fiecare regulă, membrul stâng conține cel puțin un neterminal 
	bool contine = false;
	for (int i = 0; i < P.size(); i++)
	{
		contine = false;
		for (int j = 0; j < P[i].first.length(); j++)
		{
			if (std::find(Vn.begin(), Vn.end(), P[i].first[j]) != Vn.end()) {
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

bool Grammar::IsRegular()
{
	// A -> aB, A -> a
	for (int i = 0; i < P.size(); i++)
	{
		// verificare un neterminal in stanga 
		std::string left = P[i].first;
		if (left.length() > 1)
			return false;

		if (std::find(Vn.begin(), Vn.end(), left[0]) == Vn.end())
			return false;

		// verificare terminal sau terminal + neterminal in dreapta
		std::string right = P[i].second;
		if (right.length() > 2)
			return false;

		if (right.length() == 1 && std::find(Vt.begin(), Vt.end(), right[0]) == Vt.end()) // verif daca e terminal
			return false;

		if (right.length() == 2
			&& std::find(Vt.begin(), Vt.end(), right[0]) == Vt.end()
			&& std::find(Vn.begin(), Vn.end(), right[1]) == Vn.end()) // verif daca nu e terminal + neterminal
			return false;
	}

	return true;
}

bool Grammar::IsIDC()
{
	// A -> w
	for (int i = 0; i < P.size(); i++)
	{
		// verificare un neterminal in stanga 
		std::string left = P[i].first;
		if (left.length() > 1)
			return false;

		if (std::find(Vn.begin(), Vn.end(), left[0]) == Vn.end()) {
			return false;
		}

		// verificare doar terminale si neterminale dreapta
		std::string right = P[i].second;
		for (int i = 0; i < right.length(); i++)
		{
			if (std::find(Vt.begin(), Vt.end(), right[i]) == Vt.end() && std::find(Vn.begin(), Vn.end(), right[i]) == Vn.end())
				return false;
		}
	}

	return true;
}

std::string Grammar::GenerateWord()
{
	std::random_device rd;
	std::mt19937 eng(rd());

	std::vector<std::pair<int, int>> productionInfos; // vector in care avem informatii despre productie (indexul productiei aplicate si locul in care s-a aplicat)
	std::vector<std::string> productions; // vector de productii prin care se trece
	std::string word(1, S);
	productions.push_back(word); // incepem cu simbolul de start

	while (true) {
		// vedem indexii productiilor care se pot aplica
		std::vector<int> applicableProductionIndexes;
		for (int i = 0; i < P.size(); i++)
		{
			if (word.find(P[i].first) != std::string::npos) // daca in word se gaseste stanga unei productii o adaugam la vector
				applicableProductionIndexes.push_back(i);
		}

		if (applicableProductionIndexes.empty()) // in cazul in care nu se mai pot aplica productii iesim din while
			break;

		std::uniform_int_distribution<>distr(0, applicableProductionIndexes.size() - 1);
		int randomProductionIndex = distr(eng); // generam random un index din vectorul cu indexii productiilor aplicabile
		int productionToApplyIndex = applicableProductionIndexes[randomProductionIndex]; // alegem indexul corespunzator productiei care o vom aplica

		// vedem pozitiile din word la care se poate aplica productia aleasa
		std::vector<int> occurencesOfProductionInWord;
		int pos = word.find(P[productionToApplyIndex].first); // cautam in word pozitia primei aparitie a productiei
		while (pos != std::string::npos && pos < word.length()) {
			occurencesOfProductionInWord.push_back(pos); // adaugam pozitia 
			pos = word.find(P[productionToApplyIndex].first, pos + 1); // cautam alta aparitie a productiei in word
		}

		if (!occurencesOfProductionInWord.empty()) {
			std::uniform_int_distribution<>distr(0, occurencesOfProductionInWord.size() - 1);
			int randomOccurenceIndex = distr(eng); // generam random un index din vectorul cu pozitiile unde se poate aplica productia
			int occurenceToReplacePos = occurencesOfProductionInWord[randomOccurenceIndex]; // alegem pozitia din word unde vom inlocui

			// inlocuim in word productia respectiva cu ce e in dreapta
			word.replace(occurenceToReplacePos, P[productionToApplyIndex].first.length(), P[productionToApplyIndex].second);

			productions.push_back(word); // adaugam noua productie
			productionInfos.push_back(std::pair<int, int>(productionToApplyIndex, occurenceToReplacePos)); // adaugam informatiile productiei
		}
	}

	std::cout << std::endl;
	std::cout << "\n~~Afisare productii sub forma:~~ \n[productie precedenta] ==([productie aplicata] , [pozitia inlocuita])=> [productie rezultata]:\n\n";
	for (int i = 0; i < productions.size(); i++)
	{
		if (i == productions.size() - 1)
		{
			std::cout << productions[i] << " (FINAL)" << "\n";
			return productions[i];
		}
		else
			std::cout << productions[i] << " ==(" << productionInfos[i].first + 1 << "," << productionInfos[i].second << ")=> ";
	}
	return productions[productions.size() - 1];
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
