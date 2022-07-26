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

/**
 * absolute value expansion:
 *  abs(xa - xb) + abs(ya - yb)
 *  max(xa - xb, xb - xa) + max(ya - yb, yb - ya)
 *  max(
 *      (xa - xb) + (ya - yb),
 *      (xa - xb) + (yb - ya),
 *      (xb - xa) + (ya - yb),
 *      (xb - xa) + (yb - ya)
 *  )
 *  max(
 *      (-xb - yb) + (xa + ya),
 *      (-xb + yb) + (xa - ya),
 *      (xb - yb) + (ya - xa),
 *      (xb + yb) + (-xa - yb)
 *  )
 *
 *  given a list of (xa, ya) and (xb, yn) pairs
 *  we can find a point (xa, ya) that minimizes
 *  abs(xa - xb) + abs(ya - yb) over all (xb, yb)
 *  by precomputing min(xb + yb), max(xb + yb), min(xb - yb), max(xb - yb)
 *  and then looping over all (xa, ya) pairs
 */

int main () {
    fastio
    int T; cin >> T;
    forn(T) {
        int Y; int X;
        cin >> Y >> X;

        int XYmin = INT_MAX;
        int XYmax = INT_MIN;
        int XmYmin = INT_MAX;
        int XmYmax = INT_MIN;

        vvi M(X + 1, vi(Y + 1));
        for(int y = 1; y <= Y; y ++) {
            for (int x = 1; x <= X; x ++) {
                char a; cin >> a;
                M[x][y] = a;
                if (a == 'B') {
                    XYmin = min(XYmin, x + y);
                    XYmax = max(XYmax, x + y);
                    XmYmin = min(XmYmin, x - y);
                    XmYmax = max(XmYmax, x - y);
                }
            }
        }
        pair<int, pii> bestsol = {INT_MAX, {-1, -1}};
        for (int y = 1; y <= Y; y ++) {
            for (int x = 1; x <= X; x ++) {
                int dist1 = (XYmin * -1) + (x + y);
                int dist2 = XYmax + (-x -y);
                int dist3 = XmYmax + (y - x);
                int dist4 = (XmYmin * -1) + (x - y);
                int actualdist = max(max(max(dist1, dist2), dist3), dist4);
                bestsol = min(bestsol, {actualdist, {x, y}});
            }
        }
        cout << bestsol.second.second << " " << bestsol.second.first << endl;
    }
}
