#include <bits/stdc++.h>
using namespace std;
int main() {
  int test;
  cin >> test;
  while (test--) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }
    for (int i = 0; i < n; i++) {
      cout << v[i] << " ";
    }
    cout << endl;
  }
  return 0;
}