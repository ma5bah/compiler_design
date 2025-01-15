#include <bits/stdc++.h>
using namespace std;
string parsed_code;
void print_vector(vector<string> list_of_word)
{
    set<string>st;
    
    for (int i = 0; i < list_of_word.size(); i++)
    {
        cout << list_of_word[i];
        if ((i + 1) < list_of_word.size())
        {
            cout << ", ";
        }
    }
    cout << endl;
}

vector<string> functions;
vector<string> operators;
vector<string> data_types;
vector<string> keywords;
vector<string> others;

bool is_keyword(string word, int idx = -1)
{
    vector<string> list_of_keyword = {
        "main",
        "return",
        "include"};
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
    stack<char>st;
    // cout<<word<<" == "<<idx<<" == "<<parsed_code[idx-1]<<endl;
    bool flag=false;
    int i;
    for(i=idx;i<parsed_code.size();i++){
        if(parsed_code[i]!='(' && parsed_code[i]!=' '){
            break;
        }
        if(parsed_code[i]=='('){
            flag=true;
            break;
        }
    }
    if(flag==false){return false;}
    flag=false;
    for(;i<parsed_code.size();i++){
        if(parsed_code[i]==')'){
            flag=true;
            break;
        }
    }
    if(flag==false){return false;};
    return true;
}
bool is_operator(string word, int idx)
{
    vector<string> list_of_keyword = {"+", "-", "*", "/", "="};
    for (int i = 0; i < list_of_keyword.size(); i++)
    {
        if (list_of_keyword[i].compare(word) == 0)
        {
            return true;
        }
    }
    return false;
}

void find_category(string word, int idx)
{
    if (is_function_type(word, idx))
    {
        functions.push_back(word);
    }
    else if (is_keyword(word, idx))
    {
        keywords.push_back(word);
    }
    else if (is_operator(word, idx))
    {
        operators.push_back(word);
    }
    else if (is_datatype(word, idx))
    {
        data_types.push_back(word);
    }

    else
    {
        others.push_back(word);
    }
}

void parse()
{
    int flag = true;
    string word;
    for (int i = 0; i < parsed_code.length(); i++)
    {
        char c = parsed_code[i];
        if (isspace(c) && flag)
        {
            // cout << word << endl;
            find_category(word, i);
            word = "";
            flag = false;
            continue;
        }

        if (!isspace(c))
        {
            flag = true;
            word += c;
        }
    }
}

int main()
{
    string input;
    while (cin >> input)
    {
        parsed_code += (input + " ");
    }
    parse();
    // cout<<parsed_code<<endl;
    cout << "function : ";
    print_vector(functions);
    cout << "operator : ";
    print_vector(operators);
    cout << "data type : ";
    print_vector(data_types);
    cout << "keywords : ";
    print_vector(keywords);
    cout << "others : ";
    print_vector(others);
    return 0;
}