//https://codeforces.com/contest/271/problem/D

#include "bits/stdc++.h"
#define pb push_back
#define endl '\n'
#define mp make_pair
#define pb push_back
using namespace std;;void __print(const int& x) {cerr << x;};void __print(const long& x) {cerr << x;};void __print(const long long& x) {cerr << x;};void __print(const unsigned& x) {cerr << x;};void __print(const unsigned long& x) {cerr << x;};void __print(const unsigned long long& x) {cerr << x;};void __print(const float& x) {cerr << x;};void __print(const double& x) {cerr << x;};void __print(const long double& x) {cerr << x;};void __print(const char& x) {cerr << '\'' << x << '\'';};void __print(const char *x) {cerr << '\"' << x << '\"';};void __print(const string &x) {cerr << '\"' << x << '\"';};void __print(const bool& x) {cerr << (x ? "true" : "false");};template<typename T> concept Container = requires(T t) { begin(t); end(t); size(t); };void __print(const stack<auto>& s);void __print(const deque<auto>& x);void __print(const queue<auto>& q);void __print(const pair<auto, auto>& p);template <Container C> void __print(const C& c);;        void __print(const stack<auto>& s) {;            auto c = s; ;            cerr<<"{STACK_TOP  ";;            while(c.size()) {;                auto v=c.top();;                c.pop(); ;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const queue<auto>& q) {;            auto c = q;;            cerr<<"{QUEUE_FONT ";;            while(c.size()) {;                auto v=c.front();;                c.pop();;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const deque<auto>& x) {;            cerr<<"{"; ;            for(auto& v: x) {;                __print(v);;;                if(&v != &x.back()) cerr<<","; ;            };            cerr<<"}";;        };    ;void __print(const pair<auto, auto> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';};template <Container C> void __print(const C &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";};void _print() {cerr << "]\n";};template <typename T, typename... V> void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);};auto min_many(auto a) {return a;};auto min_many(auto a, auto b, auto... c) {return min_many(std::min(a,b),c...);};auto max_many(auto a) {return a;};auto max_many(auto a, auto b, auto... c) {return max_many(std::max(a,b),c...);};typedef complex<double> cd;typedef complex<long double> cld;typedef unsigned int ui;typedef unsigned long long ull;typedef long long ll;typedef vector<int> vi;typedef vector<bool> vb;typedef vector<long long> vll;typedef vector<vector<int>> vvi;typedef vector<vector<long long>> vvll;typedef pair<int, int> pii;typedef pair<long long, long long> pll;typedef vector<pair<int, int>> vpii;typedef vector<vector<pair<int, int>>> vvpii;typedef vector<pair<long long, long long>> vpll;typedef vector<vector<pair<long long, long long>>> vvpll;
#ifdef ONLINE_JUDGE
    # define debug(x...)
    # define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#else
    # define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
    # define fastio
#endif


// calculate hash of a binary string where each index can be toggled in O(1)
struct binary_hash {
    mt19937_64 rng = mt19937_64(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> get_rng = uniform_int_distribution<ll>(LLONG_MIN, LLONG_MAX);

    ll cur_hash = 0;
    vector<ll> seeds;
      
    binary_hash(ll size) {
        seeds.resize(size);
        for(ll i=0;i<size;i++) {
            seeds[i] = get_rng(rng);
        }
    }

    void toggle(ll idx) {
        cur_hash ^= seeds[idx]; 
    }
};

int main() {
    fastio;
    ll T; cin>>T;
    for(ll tc=0;tc<T;tc++) {
        ll N; ll M; cin>>N>>M;
        vector<string> data;
        map<ll, ll> counts;
        map<ll, pll> actions;
        binary_hash bh(N);
        for(ll i=0;i<N;i++) {
            string s; cin>>s; data.pb(s);
        }    
        for(ll j=0;j<M;j++) {
            bh.cur_hash = 0;
            // initial pre-compute 
            for(ll i=0;i<N;i++) {
                if(data[i][j] == '1') {
                    bh.toggle(i);
                }
            }
            // calculate every special combination
            for(ll i=0;i<N;i++) {
                bh.toggle(i);
                counts[bh.cur_hash]++;
                actions[bh.cur_hash] = {i, j};
                bh.toggle(i);
            }
        }
        pair<ll, ll> best = {-1, -1};
        for(auto p: counts) best = max(best, {p.second, p.first});
        cout<<best.first<<endl;
        pll action = actions[best.second];
        for(ll i=0;i<N;i++) {
            if(data[i][action.second] == '1' && i != action.first) {
                cout<<"1";
            }
            else if(i == action.first && data[action.first][action.second] == '0') {
                cout<<"1";
            }
            else {
                cout<<"0";
            }
        }
        cout<<endl;
    }
    
}
