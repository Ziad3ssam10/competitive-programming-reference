#include <bits/stdc++.h>
using namespace std;

#include <ext/rope>
using namespace __gnu_cxx;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    rope<int> rope;

    rope.insert(0, 5);

    cout << rope[0] << '\n';
}