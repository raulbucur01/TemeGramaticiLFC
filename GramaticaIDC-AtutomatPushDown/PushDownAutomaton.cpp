#include "PushDownAutomaton.h"

PushDownAutomaton::PushDownAutomaton(
    std::vector<int> states,
    std::vector<char> alphabet,
    std::vector<char> stack_alphabet,
    std::vector<Transition> transitions,
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

        int no;
        fin >> q >> c1 >> c2;
        fin.get();
        fin >> no;
        Transition transition;
        transition.state = q;
        transition.symbol = c1;
        transition.stackSymbol = c2;
        for (int i = 0; i < no; i++)
        {
            std::pair<int, std::string> right;
            fin >> q1 >> pd;
            right = std::make_pair(q1, pd);
            transition.result.push_back(right);
        }
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

        std::cout << "(" << transition.state << ", " << transition.symbol << ", " << transition.stackSymbol << ") -> ";
        for (int i = 0; i < transition.result.size(); i++)
        {
            std::cout << "(" << transition.result[i].first << ", " << transition.result[i].second << ") ";
            
        }
        std::cout << '\n';
            
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
    
    for (const auto& transition : transitions) {
        
        for (int i = 0; i < transition.result.size(); i++)
        {


            if (transition.state == currentState && (transition.symbol[0] == inputSymbol || transition.symbol == "lambda")) {

                currentState = transition.result[i].first;

                if (transition.result[i].second == "lambda" || transition.symbol == "lambda")
                {
                    if (!stack.empty())stack.pop_back();
                }
                else
                {
                    if (!stack.empty())stack.pop_back();
                    for (char c : transition.result[i].second) {
                        stack.push_back(c);
                    }
                }
                return true;
            }
        }
    }

    std::cout << "Nu exista o tranzitie valida pentru starea " << currentState
        << " si simbolul de intrare " << inputSymbol << " cu stiva " << stack << "'" << std::endl;

    return false;
}

bool PushDownAutomaton::ProcessWord(const std::string& word) {
    
    int currentState = initial_state;
    std::string stack = std::string(1, initial_stack_symbol);

    
    for (char inputSymbol : word) {
        
        if (!Simulation(inputSymbol, currentState, stack)) {
            std::cout << "Cuvantul \"" << word << "\" nu este acceptat." << std::endl;
            return false;
        }
    }
    
    if (currentState == transitions.back().state)
    {
        currentState = transitions.back().result.back().first;
        if (!stack.empty())
            stack.pop_back();
        else return false;
    }

    if (!stack.empty())
        return false;
    
    if (std::find(final_states.begin(), final_states.end(), currentState) != final_states.end()) {
        std::cout << "Cuvantul \"" << word << "\" este acceptat." << std::endl;
        return true;
    }
    else {
        std::cout << "Cuvantul \"" << word << "\" nu este acceptat." << std::endl;
        return false;
    }
}
bool PushDownAutomaton::isDeterministic()
{
    for (auto& transition : transitions)
    {
        if (transition.result.size() != 1)
            return false;
    }
    return true;
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
