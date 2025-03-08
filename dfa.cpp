#include <bits/stdc++.h>
using namespace std;

int main()
{
    int number_of_dfa;
    int dp[26][2];
    memset(dp, -1, sizeof(dp));
    cin >> number_of_dfa;
    for (int i = 0; i < number_of_dfa; i++) {
        char a, b, c;
        cin >> a >> b >> c;
        // cout << a << " " << b << " " << c << endl;
        dp[a - 'a'][b - '0'] = c - 'a';
    }
    char final_state;
    cin >> final_state;
    int number_of_strings;
    cin >> number_of_strings;
    for (int i = 0; i < number_of_strings; i++) {
        string str;
        cin >> str;
        char state = 'a';
        for (int i = 0; i < str.size(); i++) {
            state = dp[state - 'a'][str[i] - '0'] + 'a';
        }
        cout << str << " -> ";
        if (state == final_state) {
            cout << "Accepted" << endl;
        } else {
            cout << "Rejected" << endl;
        }
    }
    return 0;
}
