#include "bits/stdc++.h"

#define ll long long
#define pb push_back
#define vi vector<int>
#define vb vector<bool>
#define vll vector<ll>
#define vvi vector<vector<int>>
#define vvll vector<vector<ll>>
#define pii pair<int, int>
# define pll pair<ll, ll>
#define vpii vector<pair<int, int>>
#define vpll vector<pair<ll,ll>>
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#ifdef ONLINE_JUDGE
# define watch(x) {}
    # define printv(n) {}
#else
#define watch(x) {cerr<<(#x)<<" is "<<(x)<<endl;}
#define printv(n) {for(auto v:n) cerr<<v<<" ";cerr<<endl;}
#endif
using namespace std;

void dfs(ll node,vvll& G,vll& cost,vb& vis,vb& finished,vll& dp,ll k) {
    if(cost[node]>k)return;
    if (vis[node] && !finished[node]) dp[node] = ((ll)2e18);
    if (!vis[node]) {
        vis[node] = true;
        ll nsum = 0;
        for (int n: G[node]) {
            if (cost[n] <= k) dfs(n, G, cost, vis, finished, dp, k);
            nsum = max(nsum, dp[n]);
        }
        dp[node] = min((ll)(2e18),nsum + 1);
        finished[node] = true;
    }
}

bool check(vvll& G, vll& cost, ll k, ll K) {
    vb vis(G.size());
    vb finished(G.size());
    vll dp(G.size());
    ll bsol=0;
    for(int i=1;i<G.size();i++) dfs(i,G,cost,vis,finished,dp,k);
    for(int i=1;i<G.size();i++)bsol=max(bsol,dp[i]);
    if(bsol>=K) return true;
    return false;
}

int main () {
    fastio
    int V; int E; ll K;
    cin >> V >> E >> K;
    vll cost(V + 1);
    vvll G(V + 1);
    for (int i = 1; i <= V; i ++) cin >> cost[i];
    for (int i = 0; i < E; i ++) {
        int f; int t;
        cin >> f >> t;
        G[f].pb(t);
    }

    ll low = 1;
    ll high = 2000000000LL;
    while (low < high) {
        ll mid = (low + high) / 2;
        if(check(G,cost,mid,K)) {
            high=mid;
        }
        else{
            low=mid+1;
        }
    }
    if(!check(G,cost,low,K)) cout<<-1<<endl;
    else cout<<low<<endl;
}
