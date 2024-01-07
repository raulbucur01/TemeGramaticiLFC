#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <set>
#include <algorithm>
struct Transition {
    int state;
    std::string symbol;
    char stackSymbol;
    std::vector<std::pair<int, std::string>> result;
};
class PushDownAutomaton {
public:
    PushDownAutomaton(
        std::vector<int> states,
        std::vector<char> alphabet,
        std::vector<char> stack_alphabet,  // Γ - stack alphabet
        std::vector<Transition> transitions,  // δ - transition function with stack operations
        int initial_state,
        char initial_stack_symbol,  // Z0 - initial stack symbol
        std::vector<int> final_states
    );

    PushDownAutomaton();

    void ReadAutomaton(std::string filename);
    void DisplayAutomaton() const;
    bool Simulation(char inputSymbol, int& currentState, std::string& stack) const;
    bool ProcessWord(const std::string& word);
    bool isDeterministic();
private:
    std::vector<int> states;                                  // Q - states
    std::vector<char> alphabet;                               // Σ - input alphabet
    std::vector<char> stack_alphabet;                         // Γ - stack alphabet
    std::vector<Transition> transitions; // δ - transition function
    int initial_state;                                        // q0 - initial state
    char initial_stack_symbol;                                // Z0 - initial stack symbol
    std::vector<int> final_states;                            // F - final states
    
};

