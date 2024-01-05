#include "PushDownAutomaton.h"

PushDownAutomaton::PushDownAutomaton(
    std::vector<int> states,
    std::vector<char> alphabet,
    std::vector<std::tuple<int, char, std::vector<int>>> transitions,
    int initial_state,
    std::vector<int> final_states
) :
    states(std::move(states)),
    alphabet(std::move(alphabet)),
    transitions(std::move(transitions)),
    initial_state(initial_state),
    final_states(std::move(final_states))
{
}

bool PushDownAutomaton::VerifyAutomaton() {
    // Verificare stari si alfabet
    if (states.empty() || alphabet.empty()) {
        std::cerr << "Eroare: Stari si alfabetul nu pot fi goale.\n";
        return false;
    }

    // Verificare starea initiala 
    if (std::find(states.begin(), states.end(), initial_state) == states.end()) {
        std::cerr << "Eroare: Starea initiala nu este inclusa in multimea starilor.\n";
        return false;
    }

    // Verificare stari finale valide
    for (int final_state : final_states) {
        if (std::find(states.begin(), states.end(), final_state) == states.end()) {
            std::cerr << "Eroare: O stare finala nu este inclusa in multimea starilor.\n";
            return false;
        }
    }

    // Verificare functie de tranzitie
    for (const auto& transition : transitions) {
        int from_state = std::get<0>(transition);
        char symbol = std::get<1>(transition);
        const std::vector<int>& to_states = std::get<2>(transition);

        // Verificare stari valide in functia de tranzitie
        if (std::find(states.begin(), states.end(), from_state) == states.end()) {
            std::cerr << "Eroare: Starea " << from_state << " din functia de tranzitie nu este inclusa in multimea starilor.\n";
            return false;
        }

        // Verificare simboluri valide in functia de tranzitie
        if (std::find(alphabet.begin(), alphabet.end(), symbol) == alphabet.end()) {
            std::cerr << "Eroare: Simbolul '" << symbol << "' din functia de tranzitie nu este inclus in alfabet.\n";
            return false;
        }

        // Verificare stari valide la care se poate ajunge
        for (int to_state : to_states) {
            if (std::find(states.begin(), states.end(), to_state) == states.end()) {
                std::cerr << "Eroare: Starea " << to_state << " din functia de tranzitie nu este inclusa in multimea starilor.\n";
                return false;
            }
        }
    }

    // Nu a dat erori pe parcurs, automatul este valid
    std::cout << "Automatul este valid.\n" << "\n";
    return true;
}

void PushDownAutomaton::PrintAutomaton() {
    std::cout << "Stari: { ";
    for (const auto& state : states) {
        std::cout << state << " ";
    }
    std::cout << "}\n";

    std::cout << "Alfabet: { ";
    for (const auto& symbol : alphabet) {
        std::cout << "'" << symbol << "' ";
    }
    std::cout << "}\n";

    std::cout << "Tranzitii:\n";
    for (const auto& transition : transitions) {
        int from_state = std::get<0>(transition);
        char symbol = std::get<1>(transition);
        const auto& to_states = std::get<2>(transition);

        std::cout << "(" << from_state << ", '" << symbol << "') -> { ";
        for (const auto& to_state : to_states) {
            std::cout << to_state << " ";
        }
        std::cout << "}\n";
    }

    std::cout << "Stare initiala: " << initial_state << "\n";

    std::cout << "Stari finale: { ";
    for (const auto& final_state : final_states) {
        std::cout << final_state << " ";
    }
    std::cout << "}\n";
}

bool PushDownAutomaton::CheckWord(const std::string& word)
{
    if (!VerifyAutomaton()) {
        std::cerr << "Automatul nu este valid. Verificati definirea acestuia.\n";
        return false;
    }

    return Simulation(word, initial_state);
}

bool PushDownAutomaton::IsDeterministic()
{

    for (const auto& transition : transitions) {
        const auto& toStates = std::get<2>(transition);

        if (toStates.size() > 1) {
            return false;
        }
    }

    // Toate tranzitiile au fost unice, deci automatul este determinist
    return true;
}

bool PushDownAutomaton::Simulation(const std::string& word, int currentState)
{
    // Verificare daca starea curenta este stare finala
    if (word.empty()) {
        return std::find(final_states.begin(), final_states.end(), currentState) != final_states.end();
    }

    char symbol = word[0];
    std::string remainingWord = word.substr(1);

    // Gasirea tranzitiilor pentru starea curenta si simbolul dat
    for (const auto& transition : transitions) {
        int fromState = std::get<0>(transition);
        char transitionSymbol = std::get<1>(transition);
        const auto& toStates = std::get<2>(transition);

        if (fromState == currentState && transitionSymbol == symbol) {
            // Incercam sa simulam tranzitiile pentru restul cuvantului
            for (int toState : toStates) {
                if (Simulation(remainingWord, toState)) {
                    return true;
                }
            }
        }
    }

    // Nu am gasit nicio tranzitie valida pentru simbolul curent
    return false;
}
