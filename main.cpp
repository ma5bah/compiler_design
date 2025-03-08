#include <bits/stdc++.h>

using namespace std;

using Token = pair<double, int>;

template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
void print_vector(const vector<T>& vec)
{
    for (const T& element : vec) {
        cout << element << " ";
    }
    cout << endl;
}
template <typename T>
void print_stack(stack<T> s)
{
    vector<T> v;
    while (!s.empty()) {
        v.push_back(s.top());
        s.pop();
    }
    reverse(v.begin(), v.end());
    print_vector(v);
}

vector<Token> extractTokens(const string& expression)
{
    vector<Token> tokens;
    int n = expression.size();

    for (int i = 0; i < n; i++) {
        if (expression[i] == ' ')
            continue;

        string number = "";
        if (isdigit(expression[i]) || expression[i] == '.') {
            while (i < n && (isdigit(expression[i]) || expression[i] == '.'))
                number += expression[i++];
            i--;
            tokens.emplace_back(stod(number), 0);
        } else {
            int type = (expression[i] == '(' || expression[i] == ')') ? 2 : 1;
            tokens.emplace_back((double)expression[i], type);
        }
    }

    return tokens;
}

double evaluate(double first, double second, char operation)
{
    if (operation == '+')
        return first + second;
    if (operation == '-')
        return first - second;
    if (operation == '*')
        return first * second;
    if (operation == '/')
        return first / second;
    if (operation == '%')
        return (int)first % (int)second;
    if (operation == '^')
        return pow(first, second);
    return 0;
}

void displayExpression(const vector<Token>& tokens, const vector<int>& visited)
{
    for (int i = 0; i < tokens.size(); i++) {
        if (!visited[i]) {
            if (tokens[i].second)
                cout << (char)(int)tokens[i].first;
            else {
                if (tokens[i].first < 0 && i != 0)
                    cout << '(';
                cout << tokens[i].first;
                if (tokens[i].first < 0 && i != 0)
                    cout << ')';
            }
        }
    }
    cout << endl;
}

void processOperator(stack<Token>& operands, stack<pair<char, int>>& operators, vector<Token>& tokens, vector<int>& visited)
{
    cout << "Process Operator" << endl;
    print_stack(operators);
    cout << "Operands" << endl;
    print_stack(operands);
    cout << "Visited" << endl;
    print_vector(visited);
    cout << "Tokens" << endl;
    print_vector(tokens);
    cout << endl;

    Token second = operands.top();
    operands.pop();
    Token first = operands.top();
    operands.pop();
    pair<char, int> op = operators.top();
    operators.pop();

    double result = evaluate(first.first, second.first, op.first);
    operands.push({ result, first.second });

    tokens[first.second] = { result, 0 };
    for (int j = first.second + 1; j <= second.second; j++)
        visited[j] = 1;

    displayExpression(tokens, visited);
}

void evaluateExpression(vector<Token>& tokens)
{
    map<char, int> precedence = { { '+', 1 }, { '-', 1 }, { '*', 2 }, { '/', 2 }, { '%', 2 }, { '^', 3 } };

    int tokenCount = tokens.size();
    vector<int> visited(tokenCount, 0);

    stack<pair<char, int>> operators;
    stack<Token> operands;

    displayExpression(tokens, visited);

    for (int i = 0; i < tokenCount; i++) {
        double number = tokens[i].first;
        int type = tokens[i].second;

        if (type == 0) {
            operands.push({ number, i });
        } else if (type == 1) {
            char operation = (int)number;
            while (!operators.empty() && precedence[operation] <= precedence[operators.top().first]) {
                processOperator(operands, operators, tokens, visited);
            }
            operators.push({ number, i });
        } else {
            char bracket = (int)number;
            if (bracket == '(') {
                operators.push({ bracket, i });
                continue;
            }
            processOperator(operands, operators, tokens, visited);
            operators.pop();
        }
    }

    while (!operators.empty()) {
        processOperator(operands, operators, tokens, visited);
    }
}

int main()
{
    string expression;
    getline(cin, expression);
    cout << expression << endl;
    vector<Token> tokens = extractTokens(expression);
    // for(auto token:tokens){
    //     cout<<token.first<<" "<<token.second<<endl;
    // }
    evaluateExpression(tokens);

    return 0;
}
