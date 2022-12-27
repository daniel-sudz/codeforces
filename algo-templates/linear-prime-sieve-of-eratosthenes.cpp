#include "bits/stdc++.h"
#define pb push_back
#define endl '\n'
#define mp make_pair
#define pb push_back
using namespace std;;void __print(const int& x) {cerr << x;};void __print(const long& x) {cerr << x;};void __print(const long long& x) {cerr << x;};void __print(const unsigned& x) {cerr << x;};void __print(const unsigned long& x) {cerr << x;};void __print(const unsigned long long& x) {cerr << x;};void __print(const float& x) {cerr << x;};void __print(const double& x) {cerr << x;};void __print(const long double& x) {cerr << x;};void __print(const char& x) {cerr << '\'' << x << '\'';};void __print(const char *x) {cerr << '\"' << x << '\"';};void __print(const string &x) {cerr << '\"' << x << '\"';};void __print(const bool& x) {cerr << (x ? "true" : "false");};template<typename T> concept Container = requires(T t) { begin(t); end(t); size(t); };void __print(const stack<auto>& s);void __print(const deque<auto>& x);void __print(const queue<auto>& q);void __print(const pair<auto, auto>& p);template <Container C> void __print(const C& c);;        void __print(const stack<auto>& s) {;            auto c = s; ;            cerr<<"{STACK_TOP  ";;            while(c.size()) {;                auto v=c.top();;                c.pop(); ;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const queue<auto>& q) {;            auto c = q;;            cerr<<"{QUEUE_FONT ";;            while(c.size()) {;                auto v=c.front();;                c.pop();;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const deque<auto>& x) {;            cerr<<"{"; ;            for(auto& v: x) {;                __print(v);;;                if(&v != &x.back()) cerr<<","; ;            };            cerr<<"}";;        };    ;void __print(const pair<auto, auto> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';};template <Container C> void __print(const C &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";};void _print() {cerr << "]\n";};template <typename T, typename... V> void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);};auto min_many(auto a) {return a;};auto min_many(auto a, auto b, auto... c) {return min_many(std::min(a,b),c...);};auto max_many(auto a) {return a;};auto max_many(auto a, auto b, auto... c) {return max_many(std::max(a,b),c...);};typedef long long ll;typedef vector<int> vi;typedef vector<bool> vb;typedef vector<long long> vll;typedef vector<vector<int>> vvi;typedef vector<vector<long long>> vvll;typedef pair<int, int> pii;typedef pair<long long, long long> pll;typedef vector<pair<int, int>> vpii;typedef vector<vector<pair<int, int>>> vvpii;typedef vector<pair<long long, long long>> vpll;typedef vector<vector<pair<long long, long long>>> vvpll;
#ifdef ONLINE_JUDGE
    # define debug(x...)
    # define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#else
    # define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
    # define fastio
#endif

// https://cp-algorithms.com/algebra/prime-sieve-linear.html
vi linear_sieve(int N) {
    vi primes; 
    vi lprimes(N+1,0);
    for(int i=2;i<=N;i++) {
        if(lprimes[i] == 0) {
            primes.pb(i);
            lprimes[i] = i;
        }
        for(int p: primes) {
            if(p > lprimes[i] || p*i > N) break;
            lprimes[p*i] = p;
        }
    }
    return lprimes;
}

// after sieve has calculated lowest prime factor of each number
// can factor any number within sieve range in additional O(log(n))
vi factor(int n, vi& lprimes) {
    vi factors; 
    while(n != 1) {
        factors.pb(lprimes[n]);
        n /= lprimes[n];
    }
    return factors;
}

// verify with problem from https://codeforces.com/contest/1766/problem/D
int main() {
    fastio;
    vi lprimes = linear_sieve(1e7); 
    int T; cin>>T;
    for(int tc=0;tc<T;tc++) {
        int x; int y; cin>>y>>x; 
        int lchain = INT_MAX; 
        for(int f: factor(x-y, lprimes)) {
            lchain = min(lchain, (f-(x%f))%f); 
        }
        if(lchain == INT_MAX) cout<<-1<<endl;
        else cout<<lchain<<endl;
    }
}
