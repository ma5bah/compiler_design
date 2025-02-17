#include <bits/stdc++.h>
using namespace std;

template <typename T>
void print_vector(const vector<T>& vec) {
    for (const T& element : vec) {
        cout << element << " ";
    }
    cout << endl;
}

vector<string> split_string(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

map<string, vector<string>> context_free_grammar;

bool is_terminal(const string& symbol) {
    for (char c : symbol) {
        if (!islower(c))
            return false;
    }
    return true;
}

bool validate_string(const string& current, const string& target) {
    if (is_terminal(current)) {
        return current == target;
    }

    if (current.size() > target.size()) {
        return false;
    }

    bool is_valid = false;

    for (size_t i = 0; i < current.size(); i++) {
        string nonterminal = current.substr(i, 1);

        if (context_free_grammar.count(nonterminal)) {
            for (const string& replacement : context_free_grammar[nonterminal]) {
                string updated_string = current;
                if (replacement == "ε") {
                    updated_string.erase(i, 1);
                } else {
                    updated_string.replace(i, 1, replacement);
                }

                is_valid |= validate_string(updated_string, target);

                if (is_valid)
                    return true;
            }
        }
    }

    return is_valid;
}

void apply_epsilon_rules() {
    map<string, vector<string>> updated_grammar = context_free_grammar;

    for (auto& [nonterminal, productions] : context_free_grammar) {
        for (const string& production : productions) {
            if (production == "ε") {
                for (auto& [lhs, rhs_list] : context_free_grammar) {
                    vector<string> modified_rules;
                    for (const string& rhs : rhs_list) {
                        size_t pos = rhs.find(nonterminal);
                        if (pos != string::npos) {
                            string modified_production = rhs;
                            modified_production.erase(pos, nonterminal.length());
                            modified_rules.push_back(modified_production);
                        }
                    }

                    if (lhs == "S") {
                        for (const string& new_rule : modified_rules) {
                            if (!new_rule.empty()) {
                                updated_grammar["S"].push_back(new_rule);
                            }
                        }
                    }
                }
            }
        }
    }

    context_free_grammar = updated_grammar;
}

int main() {
    int num_productions;
    cin >> num_productions;
    cin.ignore();

    string production_rule;
    for (int i = 0; i < num_productions; i++) {
        getline(cin, production_rule);
        vector<string> tokens = split_string(production_rule);

        if (tokens.empty())
            continue;

        string nonterminal = tokens[0];

        for (size_t j = 1; j < tokens.size(); j++) {
            context_free_grammar[nonterminal].push_back(tokens[j]);
            // if (tokens[j] == "ε") {
            //     swap(context_free_grammar[nonterminal].back(), context_free_grammar[nonterminal][0]);
            // }
        }
    }

    apply_epsilon_rules();

    for (auto& [lhs, rhs_list] : context_free_grammar) {
        cout << lhs << " -> ";
        print_vector(rhs_list);
    }

    int num_test_cases;
    cin >> num_test_cases;
    cin.ignore();

    while (num_test_cases--) {
        string test_string;
        cin >> test_string;
        if (validate_string("S", test_string)) {
            cout << test_string << " -> Accepted" << endl;
        } else {
            cout << test_string << " -> Rejected" << endl;
        }
    }

    return 0;
}
