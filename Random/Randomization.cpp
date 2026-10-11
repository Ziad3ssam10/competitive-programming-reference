mt19937 mt(time(0)); //: For int
mt19937_64 mt(time(0)); //: For long long
 
OR 
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //: For int
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); //: For long long
 
int get(int x)
{
    return mt()%x;
}
 
int x=uniform_int_distribution<int>(0, n-1)(rng);
 
shuffle(v2.begin() , v2.end() , rng) ;
