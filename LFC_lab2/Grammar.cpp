#include "Grammar.h"
#include <random>

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

void Grammar::GenerateWord()
{
	std::random_device rd;
	std::mt19937 eng(rd());

	std::vector<std::string> productions;
	std::string word(1, S);
	productions.push_back(word);

	while (true) {
		std::vector<int> applicableProductionIndexes;
		for (int i = 0; i < P.size(); i++)
		{
			if (word.find(P[i].first) != word.length())
				applicableProductionIndexes.push_back(i);
		}

		if (applicableProductionIndexes.empty())
			break;

		std::uniform_int_distribution<>distr(0, applicableProductionIndexes.size() - 1);
		int randomProductionIndex = distr(eng);
		int productionToApplyIndex = applicableProductionIndexes[randomProductionIndex];

		std::vector<int> occurencesOfProductionInWord;
		int pos = 0;
		while (pos < word.length()) {
			occurencesOfProductionInWord.push_back(pos);
			pos = word.find(P[productionToApplyIndex].first, pos + 1);
		}

		if (!occurencesOfProductionInWord.empty()) {
			std::uniform_int_distribution<>distr(0, occurencesOfProductionInWord.size() - 1);
			int randomOccurenceIndex = distr(eng);
			int occurenceToReplacePos = occurencesOfProductionInWord[randomOccurenceIndex];
			word.replace(occurenceToReplacePos, P[productionToApplyIndex].first.length(), P[productionToApplyIndex].second);

			productions.push_back(word);
		}
	}

	for (auto& prod : productions)
	{
		std::cout << prod << " => ";
	}
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
