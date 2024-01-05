#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>

class DeterministicFiniteAutomaton {
public:
    DeterministicFiniteAutomaton(
        std::vector<int> states,
        std::vector<char> alphabet,
        std::vector<std::tuple<int, char, std::vector<int>>> transitions,
        int initial_state,
        std::vector<int> final_states
    );

    bool VerifyAutomaton();
    void PrintAutomaton();
    bool CheckWord(const std::string& word);
    bool IsDeterministic();


private:
    std::vector<int> states;                                  // Q - starile automatei
    std::vector<char> alphabet;                               // E - alfabetul automatei
    std::vector<std::tuple<int, char, std::vector<int>>> transitions; // & - functia de tranzitie
    int initial_state;                                        // q0 - starea initiala
    std::vector<int> final_states;                            // F - starile finale
    bool Simulation(const std::string& word, int currentState);
};