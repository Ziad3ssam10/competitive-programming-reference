#include <bits/stdc++.h>
#define S second
#define F first
#define ll long long

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
class Random {
public:
    Random() = default;

    Random(std::mt19937::result_type seed) : eng(seed) {}

    ll DrawNumber(ll min, ll max);

private:
    std::mt19937 eng{std::random_device{}()};
};

ll Random::DrawNumber(ll min, ll max) {
    if (max < min)return 0;
    return std::uniform_int_distribution<ll>{min, max}(eng);
}

Random rnd;

void gen()
{
    ofstream cout("in.txt");
    cout << rnd.DrawNumber(1, 1000) << '\n';
}
int main()
{
    system("g++ -O2 WA.cpp -o WA");
    system("g++ -O2 AC.cpp -o AC");
    int tc = 0;
    while(++tc)
    {
        gen();
        system("AC < in.txt > AC.txt");
        int temp = system("WA < in.txt > WA.txt");
        if(temp) break;
        ifstream wa("WA.txt"), ac("AC.txt");
        string AC, WA;
        getline(ac, AC, (char)EOF);
        getline(wa, WA, (char)EOF);
        cout<<tc<<endl;
        if(AC != WA) break;
    }
    return 0;
}
