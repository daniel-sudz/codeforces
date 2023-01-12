let std_header = [
    String.raw`using namespace std;`,
]

let macro_defines = [
    String.raw`#include "bits/stdc++.h"`,
    String.raw`#define pb push_back`,
    String.raw`#define endl '\n'`,
    String.raw`#define mp make_pair`,
    String.raw`#define pb push_back`,
]

let typedefs = {
    "ui":       "unsigned int",
    "ull":      "unsigned long long",
    "ll":       "long long",
    "vi":       "vector<int>",
    "vb":       "vector<bool>",
    "vll":      "vector<long long>",
    "vvi":      "vector<vector<int>>",
    "vvll":     "vector<vector<long long>>",
    "pii":      "pair<int, int>",
    "pll":      "pair<long long, long long>",
    "vpii":     "vector<pair<int, int>>",
    "vvpii":    "vector<vector<pair<int, int>>>",
    "vpll":     "vector<pair<long long, long long>>",
    "vvpll":    "vector<vector<pair<long long, long long>>>",
}

let debug = [
    String.raw`void __print(const int& x) {cerr << x;}`,
    String.raw`void __print(const long& x) {cerr << x;}`,
    String.raw`void __print(const long long& x) {cerr << x;}`,
    String.raw`void __print(const unsigned& x) {cerr << x;}`,
    String.raw`void __print(const unsigned long& x) {cerr << x;}`,
    String.raw`void __print(const unsigned long long& x) {cerr << x;}`,
    String.raw`void __print(const float& x) {cerr << x;}`,
    String.raw`void __print(const double& x) {cerr << x;}`,
    String.raw`void __print(const long double& x) {cerr << x;}`,
    String.raw`void __print(const char& x) {cerr << '\'' << x << '\'';}`,
    String.raw`void __print(const char *x) {cerr << '\"' << x << '\"';}`,
    String.raw`void __print(const string &x) {cerr << '\"' << x << '\"';}`,
    String.raw`void __print(const bool& x) {cerr << (x ? "true" : "false");}`,
    // heuristics for an stl container type 
    String.raw`template<typename T> concept Container = requires(T t) { begin(t); end(t); size(t); }`,
    // forward declarations for recursive calls 
    String.raw`void __print(const stack<auto>& s)`,
    String.raw`void __print(const deque<auto>& x)`,
    String.raw`void __print(const queue<auto>& q)`,
    String.raw`void __print(const pair<auto, auto>& p)`,
    String.raw`template <Container C> void __print(const C& c)`,
    String.raw`
        void __print(const stack<auto>& s) {
            auto c = s; 
            cerr<<"{STACK_TOP  ";
            while(c.size()) {
                auto v=c.top();
                c.pop(); 
                __print(v);
                cerr<<(c.size()?",":"");
            }
            cerr<<"}";
        }
    `.split("\n").join(";"),
    String.raw`
        void __print(const queue<auto>& q) {
            auto c = q;
            cerr<<"{QUEUE_FONT ";
            while(c.size()) {
                auto v=c.front();
                c.pop();
                __print(v);
                cerr<<(c.size()?",":"");
            }
            cerr<<"}";
        }
    `.split("\n").join(";"),
    String.raw`
        void __print(const deque<auto>& x) {
            cerr<<"{"; 
            for(auto& v: x) {
                __print(v);;
                if(&v != &x.back()) cerr<<","; 
            }
            cerr<<"}";
        }
    `.split("\n").join(";"),
    String.raw`void __print(const pair<auto, auto> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}`,
    String.raw`template <Container C> void __print(const C &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}`,
    String.raw`void _print() {cerr << "]\n";}`,
    String.raw`template <typename T, typename... V> void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}`,
]

let min_max = [
    String.raw`auto min_many(auto a) {return a;}`,
    String.raw`auto min_many(auto a, auto b, auto... c) {return min_many(std::min(a,b),c...);}`,
    String.raw`auto max_many(auto a) {return a;}`,
    String.raw`auto max_many(auto a, auto b, auto... c) {return max_many(std::max(a,b),c...);}`,
]

let online_judge = [
    String.raw`#ifdef ONLINE_JUDGE`,
    String.raw`    # define debug(x...)`,
    String.raw`    # define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);`,
    String.raw`#else`,
    String.raw`    # define debug(x...) cerr << "[" << #x << "] = ["; _print(x)`,
    String.raw`    # define fastio`,
    String.raw`#endif`,
]


let prog_header = ""
prog_header += macro_defines.join("\n") + "\n"
prog_header += std_header.join(";") + ";"
prog_header += debug.join(";") + ";"
prog_header += min_max.join(";") + ";"
for(const [k,v] of Object.entries(typedefs))
    prog_header += `typedef ${v} ${k};`
prog_header += "\n" + online_judge.join("\n")

prog_header += `\n\n
int main() {
    fastio;
}`

console.log(prog_header); 
