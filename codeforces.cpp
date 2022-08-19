#include "bits/stdc++.h"
using namespace std;
 
// stl
#define ll long long
#define pb push_back
#define vi vector<int>
#define vb vector<bool>
#define vll vector<ll>
#define vvi vector<vector<int>>
#define vvll vector<vector<ll>>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vpii vector<pair<int, int>>
#define vpll vector<pair<ll,ll>>
#define endl '\n'
#define mp make_pair
#define pb push_back

// debug
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V> void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T> void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V> void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

// codeforces
#ifdef ONLINE_JUDGE
    # define debug(x...)
    # define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#else
    # define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
    # define fastio // buffering output does not work with debugger as nothing will print 
#endif

int main() {
    fastio;
}
