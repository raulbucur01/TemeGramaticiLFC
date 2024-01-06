#include "PushDownAutomaton.h"

PushDownAutomaton::PushDownAutomaton(
    std::vector<int> states,
    std::vector<char> alphabet,
    std::vector<char> stack_alphabet,
    std::vector<std::tuple<int, std::string, char, std::pair<int, std::string>>> transitions,
    int initial_state,
    char initial_stack_symbol,
    std::vector<int> final_states
) : 
    states(std::move(states)),
    alphabet(std::move(alphabet)),
    stack_alphabet(std::move(stack_alphabet)),  // Added stack alphabet initialization
    transitions(std::move(transitions)),        // Added transitions with stack operations
    initial_state(initial_state),
    initial_stack_symbol(initial_stack_symbol),  // Added initial stack symbol initialization
    final_states(std::move(final_states))
{
    // Additional initialization if needed
}

PushDownAutomaton::PushDownAutomaton()
{
}

void PushDownAutomaton::ReadAutomaton(std::string filename)
{
    std::ifstream fin(filename);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int state;
        fin >> state;
        states.push_back(state);
    }

    fin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        fin >> c;
        alphabet.push_back(c);
    }


    fin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        fin >> c;
        stack_alphabet.push_back(c);
    }

    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int q;
        char c2;
        std::string c1;
        int q1;
        std::string pd;

        fin >> q >> c1 >> c2 >> q1 >> pd;
        std::pair<int, std::string> right;
        right = std::make_pair(q1, pd);
        std::tuple<int, std::string, char, std::pair<int, std::string>> transition;
        transition = std::make_tuple(q, c1, c2, right);
        transitions.push_back(transition);
    }
    fin >> initial_state >> initial_stack_symbol;

    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int s;
        fin >> s;
        final_states.push_back(s);
    }

}

void PushDownAutomaton::DisplayAutomaton() const {
    std::cout << "States : ";
    for (int state : states) {
        std::cout << state << " ";
    }
    std::cout << std::endl;

    std::cout << "Alphabet : ";
    for (char symbol : alphabet) {
        std::cout << symbol << " ";
    }
    std::cout << std::endl;

    std::cout << "Stack Alphabet : ";
    for (char stackSymbol : stack_alphabet) {
        std::cout << stackSymbol << " ";
    }
    std::cout << std::endl;

    std::cout << "Transitions :" << std::endl;
    for (const auto& transition : transitions) {
        int fromState;
        std::string inputSymbol;
        char stackSymbol;
        std::pair<int, std::string> toStateAndStack;

        std::tie(fromState, inputSymbol, stackSymbol, toStateAndStack) = transition;

        std::cout << "(" << fromState << ", " << inputSymbol << ", " << stackSymbol << ") -> ("
            << toStateAndStack.first << ", " << toStateAndStack.second << ")" << std::endl;
    }

    std::cout << "Initial State : " << initial_state << std::endl;
    std::cout << "Initial Stack Symbol : " << initial_stack_symbol << std::endl;

    std::cout << "Final States : ";
    for (int finalState : final_states) {
        std::cout << finalState << " ";
    }
    std::cout << std::endl;
}

bool PushDownAutomaton::Simulation(char inputSymbol, int& currentState, std::string& stack) const {
    // Căutați tranzacția curentă
    for (const auto& transition : transitions) {
        int fromState, toState;
        std::string readSymbol, stackTop;
        char stackSymbol;

        fromState = std::get<0>(transition);
        readSymbol = std::get<1>(transition);
        stackSymbol = std::get<2>(transition);
        toState = std::get<3>(transition).first;
        stackTop = std::get<3>(transition).second;

        // Verificați dacă tranzacția este validă pentru starea curentă și simbolul de intrare
        if (fromState == currentState && (readSymbol[0] == inputSymbol || readSymbol == "lambda") ) {
            // Efectuați tranziția
            currentState = toState;
            // Manipulați stiva
            if (stackTop == "lambda" || readSymbol == "lambda")
                stack.pop_back();
            else

            {
                stack.pop_back();  // Scoateți simbolul din vârful stivei
                for (char c : stackTop) {
                    stack.push_back(c);  // Adăugați simbolurile în stiva curentă
                }
            }
            return true;
        }
    }

    std::cout << "Nu există o tranziție validă pentru starea " << currentState
        << " și simbolul de intrare '" << inputSymbol << "' cu stiva '" << stack << "'" << std::endl;

    return false;
}

bool PushDownAutomaton::ProcessWord(const std::string& word) {
    // Inițializare cu starea inițială și simbolul inițial de stivă
    int currentState = initial_state;
    std::string stack = std::string(1, initial_stack_symbol);

    // Pentru fiecare simbol din cuvânt
    for (char inputSymbol : word) {
        // Apelați funcția de simulare cu simbolul curent și stiva curentă
        if (!Simulation(inputSymbol, currentState, stack)) {
            std::cout << "Cuvântul \"" << word << "\" nu este acceptat." << std::endl;
            return false;
        }
    }

    // Verificați dacă starea curentă este o stare finală
    if (std::find(final_states.begin(), final_states.end(), currentState) != final_states.end()) {
        std::cout << "Cuvântul \"" << word << "\" este acceptat." << std::endl;
        return true;
    }
    else {
        std::cout << "Cuvântul \"" << word << "\" nu este acceptat." << std::endl;
        return false;
    }
}
//bool PushDownAutomaton::VerifyAutomaton() {
//    // Verificare stari si alfabet
//    if (states.empty() || alphabet.empty()) {
//        std::cerr << "Eroare: Stari si alfabetul nu pot fi goale.\n";
//        return false;
//    }
//
//    // Verificare starea initiala 
//    if (std::find(states.begin(), states.end(), initial_state) == states.end()) {
//        std::cerr << "Eroare: Starea initiala nu este inclusa in multimea starilor.\n";
//        return false;
//    }
//
//    // Verificare stari finale valide
//    for (int final_state : final_states) {
//        if (std::find(states.begin(), states.end(), final_state) == states.end()) {
//            std::cerr << "Eroare: O stare finala nu este inclusa in multimea starilor.\n";
//            return false;
//        }
//    }
//
//    // Verificare functie de tranzitie
//    for (const auto& transition : transitions) {
//        int from_state = std::get<0>(transition);
//        char symbol = std::get<1>(transition);
//        const std::vector<int>& to_states = std::get<2>(transition);
//
//        // Verificare stari valide in functia de tranzitie
//        if (std::find(states.begin(), states.end(), from_state) == states.end()) {
//            std::cerr << "Eroare: Starea " << from_state << " din functia de tranzitie nu este inclusa in multimea starilor.\n";
//            return false;
//        }
//
//        // Verificare simboluri valide in functia de tranzitie
//        if (std::find(alphabet.begin(), alphabet.end(), symbol) == alphabet.end()) {
//            std::cerr << "Eroare: Simbolul '" << symbol << "' din functia de tranzitie nu este inclus in alfabet.\n";
//            return false;
//        }
//
//        // Verificare stari valide la care se poate ajunge
//        for (int to_state : to_states) {
//            if (std::find(states.begin(), states.end(), to_state) == states.end()) {
//                std::cerr << "Eroare: Starea " << to_state << " din functia de tranzitie nu este inclusa in multimea starilor.\n";
//                return false;
//            }
//        }
//    }
//
//    // Nu a dat erori pe parcurs, automatul este valid
//    std::cout << "Automatul este valid.\n" << "\n";
//    return true;
//}
//
//void PushDownAutomaton::PrintAutomaton() {
//    std::cout << "Stari: { ";
//    for (const auto& state : states) {
//        std::cout << state << " ";
//    }
//    std::cout << "}\n";
//
//    std::cout << "Alfabet: { ";
//    for (const auto& symbol : alphabet) {
//        std::cout << "'" << symbol << "' ";
//    }
//    std::cout << "}\n";
//
//    std::cout << "Tranzitii:\n";
//    for (const auto& transition : transitions) {
//        int from_state = std::get<0>(transition);
//        char symbol = std::get<1>(transition);
//        const auto& to_states = std::get<2>(transition);
//
//        std::cout << "(" << from_state << ", '" << symbol << "') -> { ";
//        for (const auto& to_state : to_states) {
//            std::cout << to_state << " ";
//        }
//        std::cout << "}\n";
//    }
//
//    std::cout << "Stare initiala: " << initial_state << "\n";
//
//    std::cout << "Stari finale: { ";
//    for (const auto& final_state : final_states) {
//        std::cout << final_state << " ";
//    }
//    std::cout << "}\n";
//}
//
//bool PushDownAutomaton::CheckWord(const std::string& word)
//{
//    if (!VerifyAutomaton()) {
//        std::cerr << "Automatul nu este valid. Verificati definirea acestuia.\n";
//        return false;
//    }
//
//    return Simulation(word, initial_state);
//}
//
//bool PushDownAutomaton::IsDeterministic()
//{
//
//    for (const auto& transition : transitions) {
//        const auto& toStates = std::get<2>(transition);
//
//        if (toStates.size() > 1) {
//            return false;
//        }
//    }
//
//    // Toate tranzitiile au fost unice, deci automatul este determinist
//    return true;
//}
//
//bool PushDownAutomaton::Simulation(const std::string& word, int currentState)
//{
//    // Verificare daca starea curenta este stare finala
//    if (word.empty()) {
//        return std::find(final_states.begin(), final_states.end(), currentState) != final_states.end();
//    }
//
//    char symbol = word[0];
//    std::string remainingWord = word.substr(1);
//
//    // Gasirea tranzitiilor pentru starea curenta si simbolul dat
//    for (const auto& transition : transitions) {
//        int fromState = std::get<0>(transition);
//        char transitionSymbol = std::get<1>(transition);
//        const auto& toStates = std::get<2>(transition);
//
//        if (fromState == currentState && transitionSymbol == symbol) {
//            // Incercam sa simulam tranzitiile pentru restul cuvantului
//            for (int toState : toStates) {
//                if (Simulation(remainingWord, toState)) {
//                    return true;
//                }
//            }
//        }
//    }
//
//    // Nu am gasit nicio tranzitie valida pentru simbolul curent
//    return false;
//}
