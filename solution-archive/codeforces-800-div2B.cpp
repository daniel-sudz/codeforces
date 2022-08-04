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

int main () {
    fastio
    ll T; cin >> T;
    forn(T) {
        ll N; cin >> N;
        string s; cin >> s;
        ll combos = N;
        for (ll i = 1; i < (ll)s.size(); i ++) {
            if (s[i] != s[i - 1]) {
                combos += i;
            }
        }
        cout << combos << endl;
    }
}
