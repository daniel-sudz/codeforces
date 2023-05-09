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

/*
    SQRT DECOMP PROBLEM
    MO's Algorithm on XOR substring queries
    https://codeforces.com/contest/617/problem/E
*/

int main() {
    fastio;
    ll N; ll M; ll K; cin>>N>>M>>K;
    vll nums; for(ll i=0;i<N;i++) {ll a;cin>>a;nums.pb(a);}
    vll psums(N+1); psums[0] = 0; for(ll i=0;i<N;i++) {psums[i+1] = psums[i] ^ nums[i];}
    vector<vector<pair<pll,ll>>> queries(sqrt(N) + 1); 
    vll ans(M);
    for(ll i=0;i<M;i++) {
        ll l; ll r; cin>>l>>r; 
        queries[l / sqrt(N)].pb({{l-1,r-1},i}); 
    }
    for(auto& p: queries) sort(p.begin(),p.end(), [](auto& a, auto& b){return a.first.second < b.first.second;});

    // solve 
    ll count = (psums[1] == K); 
    ll lptr = 0; 
    ll rptr = 0;
    vll inc(2*(*max_element(nums.begin(),nums.end()))+10); inc[psums[1]] = 1;
    vll exc(2*(*max_element(nums.begin(),nums.end()))+10); exc[0] = 1;
    for(auto& b: queries) {
        for(auto& qv: b) {
            pll q = qv.first; 
            while(rptr < q.second) {
                inc[psums[rptr+2]] ++;
                exc[psums[rptr+1]] ++;
                count += exc[K ^ psums[rptr+2]];
                rptr ++;
            }
            while(lptr > q.first) {
                inc[psums[lptr]] ++;
                exc[psums[lptr-1]] ++;
                count += inc[K ^ psums[lptr-1]];
                lptr--;
            }
            while(lptr < q.first) {
                count -= inc[K ^ psums[lptr]];  
                inc[psums[lptr+1]] --;
                exc[psums[lptr]] --;
                lptr++;
            }
            while(rptr > q.second) {
                count -= exc[K ^ psums[rptr+1]];
                inc[psums[rptr+1]] --; 
                exc[psums[rptr]] --;
                rptr --;
            }
            ans[qv.second] = count;
        }
    }
    for(ll v: ans) cout<<v<<endl;
}
