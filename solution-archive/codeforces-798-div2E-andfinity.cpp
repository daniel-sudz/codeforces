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

int T; int N;
int RESERVED = 32;

void dfs(int node, vvi& G, vector<bool>& vis) {
    if (!vis[node]) {
        vis[node] = true;
        for (int n : G[node]) dfs(n, G, vis);
    }
}

int cgroups(vvi& G) {
    int groups = 0;
    vector<bool> vis(N + RESERVED);
    for (int i = 0; i < N; i ++) {
        if (!vis[i + RESERVED]) {
            groups ++;
            dfs(i + RESERVED, G, vis);
        }
    }
    return groups;
}

int testGraph(vi& input) {
    vvi G = vvi(N + RESERVED);
    // build graph based on bits
    for (int i = 0; i < N; i ++) {
        for (int ac = input[i], digit = 1; ac; ac >>= 1, digit ++) {
            if (ac % 2 == 1) {
                G[i + RESERVED].pb(digit);
                G[digit].pb(i + RESERVED);
            }
        }
    }
    return cgroups(G);
}


int main() {
    fastio
    cin >> T;
    forn(T) {
        cin >> N;
        vi input; forn(N) {int a; cin >> a; input.pb(a);}
        int totalcost = 0;

        // all zeros should be ones
        for (int i = 0; i < N; i ++) {
            if (input[i] == 0) {
                input[i] ++;
                totalcost ++;
            }
        }


        if (testGraph(input) == 1) {
           // done
        }
        else {
            totalcost ++;
            int done = false;
            for (int i = 0; i < N; i ++) {
                vi copy = input;
                copy[i] --;
                if (testGraph(copy) == 1) {
                    input = copy;
                    done = true;
                    break;
                }
            }
            if (!done) {
                for (int i = 0; i < N; i ++) {
                    vi copy = input;
                    copy[i] ++;
                    if (testGraph(copy) == 1) {
                        input = copy;
                        done = true;
                        break;
                    }
                }
            }
            if (!done) {
                totalcost ++;
                pii ntodec = {0, 0};
                for (int i = 0; i < N; i ++) ntodec = max(ntodec, {input[i] & (-input[i]), i});
                input[ntodec.second] --;
                for (int i = 0; i < N; i ++) {
                    if (input[i] & ntodec.first) {
                        input[i] ++;
                        break;
                    }
                }
            }

        }
        cout << totalcost << endl;
        for (int v: input) cout << v << " ";
        cout << endl;
    }
}
