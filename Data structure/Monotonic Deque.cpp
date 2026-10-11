template<class T>
class SlidingDeque{
    stack<T> f[2], b[2];
    
    T merge(T a, T b){
        return __gcd(a, b);
    }
    void add(T val, stack<T> s[]){
        s[0].push(val);
        s[1].push((s[1].empty() ? val : merge(s[1].top(), val)));
    }
    void rem(stack<T> s[]){
        s[0].pop(), s[1].pop();
    }
    void rebalance(stack<T> low[], stack<T> high[]){
        stack<T> temp;
        int cnt = high[0].size() / 2;
        while(cnt--) temp.push(high[0].top()), rem(high);
        while(high[0].size()) add(high[0].top(), low), rem(high);
        while(temp.size()) add(temp.top(), high), temp.pop();
    }
public:
    void push_back(T val){ add(val, b); }
    void push_front(T val){ add(val, f); }
    void pop_back(){
        if(b[0].empty()) rebalance(b, f);
        rem(b);
    }
    void pop_front(){
        if(f[0].empty()) rebalance(f, b);
        rem(f);
    }
    T query(){
        return (f[1].size() && b[1].size() ? merge(f[1].top(), b[1].top()) :
               (f[1].size()? f[1].top() : b[1].top()));
    }
};