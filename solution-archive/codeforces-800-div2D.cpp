#include "bits/stdc++.h"

#define ll long long
#define pb push_back
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pair<int, int>>
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define forn(n) for(int i = 0; i < n; i ++)
#ifdef ONLINE_JUDGE
# define watch(x) {}
    # define printv(n) {}
#else
#define watch(x) {cerr<<(#x)<<" is "<<(x)<<endl;}
#define printv(n) {for(auto v:n) cerr<<v<<" ";cerr<<endl;}
#endif
using namespace std;

ll solve(int node, vvi& G, vpii& bounds, int& cost) {
    ll freetotal = 0;
    for (int n : G[node]) {
        freetotal += solve(n, G, bounds, cost);
    }
    if (freetotal < bounds[node].first) {
        cost ++;
        return bounds[node].second;
    }
    else {
        return min((ll)bounds[node].second, freetotal);
    }
}

int main () {
    fastio
    int T; cin >> T;
    forn(T) {
        int N; cin >> N;
        vvi G(N + 1);
        vpii bounds(N + 1);
        for (int i = 2; i <= N; i ++) {
            int p; cin >> p;
            G[p].pb(i);
        }
        for (int i = 1; i <= N; i ++) {
            int l; int r; cin >> l >> r;
            bounds[i] = {l, r};
        }
        int res = 0;
        solve(1, G, bounds, res);
        cout << res << endl;
    }
}
