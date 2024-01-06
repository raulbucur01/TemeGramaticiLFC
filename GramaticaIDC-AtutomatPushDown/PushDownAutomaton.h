#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>

class PushDownAutomaton {
public:
    PushDownAutomaton(
        std::vector<int> states,
        std::vector<char> alphabet,
        std::vector<char> stack_alphabet,  // Γ - stack alphabet
        std::vector<std::tuple<int, char, char, std::vector<int>>> transitions,  // δ - transition function with stack operations
        int initial_state,
        char initial_stack_symbol,  // Z0 - initial stack symbol
        std::vector<int> final_states
    );

private:
    std::vector<int> states;                                  // Q - states
    std::vector<char> alphabet;                               // Σ - input alphabet
    std::vector<char> stack_alphabet;                         // Γ - stack alphabet
    std::vector<std::tuple<int, char, char, std::vector<int>>> transitions; // δ - transition function
    int initial_state;                                        // q0 - initial state
    char initial_stack_symbol;                                // Z0 - initial stack symbol
    std::vector<int> final_states;                            // F - final states
    bool Simulation(const std::string& word, int currentState);
};