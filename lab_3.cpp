#include <bits/stdc++.h>
using namespace std;
string parsed_code;
void print_vector(set<string> list_of_word)
{

    auto begin = list_of_word.begin();
    auto end = list_of_word.end();
    while (begin != end)
    {
        cout << *begin << " , ";
        begin++;
    }
    cout << endl;
}
void print_vector(vector<string> list_of_word)
{

    auto begin = list_of_word.begin();
    auto end = list_of_word.end();
    while (begin != end)
    {
        cout << *begin << " , ";
        begin++;
    }
    cout << endl;
}

vector<string> functions;
vector<string> operators;
vector<string> data_types;
vector<string> keywords;
vector<string> variables;
vector<string> constants;
set<string> others;

bool is_keyword(string word, int idx = -1)
{
    vector<string> list_of_keyword = {
        "return",
        "include",
        "for"};
    for (int i = 0; i < list_of_keyword.size(); i++)
    {

        // if (list_of_keyword[i] == word)
        if (list_of_keyword[i].compare(word) == 0)
        {
            return true;
        }
    }
    return false;
}
bool is_datatype(string word, int idx)
{
    vector<string> list_of_keyword = {"int", "bool", "float", "double", "long"};
    for (int i = 0; i < list_of_keyword.size(); i++)
    {
        if (list_of_keyword[i].compare(word) == 0)
        {
            return true;
        }
    }
    return false;
}

bool is_function_type(string word, int idx)
{
    // Check if the word is followed by a parenthesis indicating a function
    if (word.empty())
        return false;
    vector<string> list_of_keyword = {"for", "while", "if", "else if", "(", ")"};
    for (int i = 0; i < list_of_keyword.size(); i++)
    {
        if (list_of_keyword[i].compare(word) == 0)
        {
            return false;
        }
    }
    bool flag = false;
    int i;
    for (i = idx; i < parsed_code.size(); i++)
    {
        if (parsed_code[i] != ' ' && parsed_code[i] != '(')
        {
            break;
        }
        if (parsed_code[i] == '(')
        {
            flag = true;
            break;
        }
    }

    if (!flag)
        return false;

    // Now check if there's a closing parenthesis after the opening one (typical for functions)
    flag = false;
    for (; i < parsed_code.size(); i++)
    {
        if (parsed_code[i] == ')')
        {
            flag = true;
            break;
        }
    }
    return flag;
}
bool is_operator(string word, int idx)
{
    vector<string> list_of_keyword = {"+", "-", "*", "/", "=", "++","<=",">=","--","+=","-=","*=","/="};
    for (int i = 0; i < list_of_keyword.size(); i++)
    {
        if (list_of_keyword[i].compare(word) == 0)
        {
            return true;
        }
    }
    return false;
}

bool is_char(char x)
{
    return ('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z') || x == '$' || x == '_';
}
bool is_number(char x)
{
    return ('0' <= x && x <= '9');
}

bool is_variable(string word, int idx)
{
    if (find(variables.begin(), variables.end(), word) != variables.end())
    {
        return false;
    }
    if (!is_char(word[0]))
    {
        return false;
    }
    for (int i = 1; i < word.size(); i++)
    {
        if (!is_char(word[i]) || !is_number(word[i]))
        {
            return false;
        }
    }
    return true;
}
bool is_constant(string word, int idx)
{
    for (int i = 0; i < word.size(); i++)
    {
        if (!is_number(word[i]))
        {
            return false;
        }
    }
    return true;
}

void print_category(string word, string identifier)
{
    cout << "< " << word << " , " << identifier << " >" << endl;
}

void find_category(string word, int idx)
{
    if (is_function_type(word, idx))
    {
        print_category(word, "function");
        functions.push_back(word);
    }
    else if (is_keyword(word, idx))
    {
        print_category(word, "keyword");

        keywords.push_back(word);
    }
    else if (is_operator(word, idx))
    {
        print_category(word, "operator");
        operators.push_back(word);
    }
    else if (is_datatype(word, idx))
    {
        print_category(word, "datatype");
        data_types.push_back(word);
    }
    else if (is_variable(word, idx))
    {

        variables.push_back(word);
        int x = (variables.size() - 1);
        print_category(word, to_string(x));
    }
    else if (is_constant(word, idx))
    {
        print_category(word, "constant");
        constants.push_back(word);
    }
    else
    {
        others.insert(word);
    }
}

vector<string> tokens;
void tokens_push(string token, int idx)
{
    find_category(token, idx);
    tokens.push_back(token);
}

vector<string> tokenize(const string &input)
{

    string token;

    for (size_t i = 0; i < input.size(); ++i)
    {
        char ch = input[i];

        if (isalnum(ch) || ch == '_')
        {
            token += ch;
        }
        else if (isspace(ch))
        {
            if (!token.empty())
            {
                tokens_push(token, i);
                token.clear();
            }
        }
        else
        {
            if (i + 1 < input.size())
            {
                string two_char_operator(1, ch);
                two_char_operator += input[i + 1];

                if (two_char_operator == "==" || two_char_operator == "<=" || two_char_operator == ">=" ||
                    two_char_operator == "++" || two_char_operator == "--" || two_char_operator == "+=" ||
                    two_char_operator == "-=" || two_char_operator == "*=" || two_char_operator == "/=")
                {

                    if (!token.empty())
                    {
                        tokens_push(token, i);
                        token.clear();
                    }
                    tokens_push(two_char_operator, i);
                    i++;
                    continue;
                }
            }

            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' 
            || ch == '=' || ch == '>' || ch == '<' || ch == '%' 
            || ch == '&' || ch == '|' || ch == ';' || ch == '{' 
            || ch == '}' || ch == ',' || ch == '(' || ch == ')')
            {

                if (!token.empty())
                {
                    tokens_push(token, i);
                    token.clear();
                }
                tokens_push(string(1, ch), i);
            }
        }
    }

    if (!token.empty())
    {
        tokens_push(token, parsed_code.size() - 1);
    }

    return tokens;
}
int main()
{
    string input;

    // Read input continuously until EOF (e.g., input from a file or user)
    while (cin >> input)
    {
        parsed_code += (input + " ");
    }

    // Tokenize the accumulated code
    vector<string> tokens = tokenize(parsed_code);

    // // Output tokens
    // cout << "Tokens:\n";
    // for (const auto &token : tokens)
    // {
    //     cout << token << endl;
    // }

    return 0;
}