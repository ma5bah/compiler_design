#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

map<char, map<char, string>> createParsingTable()
{
    map<char, map<char, string>> table;
    table['E']['i'] = "Te";
    table['E']['('] = "Te";
    table['e']['+'] = "+Te";
    table['e'][')'] = "0";
    table['e']['$'] = "0";
    table['T']['i'] = "Ft";
    table['T']['('] = "Ft";
    table['t']['+'] = "0";
    table['t']['*'] = "*Ft";
    table['t'][')'] = "0";
    table['t']['$'] = "0";
    table['F']['i'] = "i";
    table['F']['('] = "(E)";
    return table;
}

string getStackAsString(stack<char> s)
{
    string result;
    while (!s.empty())
    {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}

void parseString(const map<char, map<char, string>> &table, const string &input)
{
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push('E');

    stack<char> inputStack;
    for (int i = input.size() - 1; i >= 0; --i)
    {
        inputStack.push(input[i]);
    }

    cout << "\nMatched\t\tStack\t\tInput\n";
    string matched;

    while (!parseStack.empty() && !inputStack.empty())
    {
        char topStack = parseStack.top();
        char topInput = inputStack.top();

        string stackContents = getStackAsString(parseStack);
        string inputContents = getStackAsString(inputStack);

        cout << matched << "\t\t" << stackContents << "\t\t" << inputContents << "\n";

        if (topStack == topInput)
        {
            matched.push_back(topStack);
            parseStack.pop();
            inputStack.pop();
        }
        else
        {
            if (!table.count(topStack) || !table.at(topStack).count(topInput))
            {
                cout << "Rejected!\n";
                return;
            }
            
            parseStack.pop();
            string production = table.at(topStack).at(topInput);
            if (production != "0")
            {
                for (int i = production.size() - 1; i >= 0; --i)
                {
                    parseStack.push(production[i]);
                }
            }
        }
    }

    
    if (!parseStack.empty() && parseStack.top() == '$' &&
        !inputStack.empty() && inputStack.top() == '$')
    {
        parseStack.pop(), inputStack.pop();
    }
   
   

    if (parseStack.empty() && inputStack.empty())
    {
        cout << "Accepted!\n";
    }
    else
    {
        cout << "Rejected!\n";
    }
}

int main()
{
    // i+i*i$
    map<char, map<char, string>> table = createParsingTable();
    string input;
    cin >> input;
    parseString(table, input);
    return 0;
}