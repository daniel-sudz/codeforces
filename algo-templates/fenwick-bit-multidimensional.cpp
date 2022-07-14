#include "bits/stdc++.h"
# define ll long long
using namespace std;

/** Based on original post in https://codeforces.com/blog/entry/64914
 * The ranges are declared statically but they could be done through constructors
 * as well to allow for dynamic range declaration
 * **/

/** Example: BIT<int, 1, 4> is a 2D BIT where each point stores value int and 0<=x<=1 and y<=0<=4  **/
template<class T, auto...> struct BIT {};

/** Zero dimension BIT **/
template<class T> struct BIT<T> {
    T state{};
    void updateDiff(T val) {
        state += val;
    }
    T query() {
        return state;
    }
};

/** Resolve an N-dimension BIT recursively **/
template<class T, auto N, auto... Args> struct BIT<T, N, Args...> {
    // if ranges are huge, map is better to prevent OOM
    // just swap these two lines
    //map<decltype(N), BIT<T, Args...>> bit;
    BIT<T, Args...> bit[N];

    /** updates a diff value. Example: update(valDiff, x1, y1, z1) */
    void updateDiff(T val, auto idx, auto... args) {
        for (; idx < N; idx = idx | (idx + 1)) {
            bit[idx].updateDiff(val, args...);
        }
    }

    /** returns a range query. Example: query(x1, x2, y1, y2, z1, z2) **/
    T query(auto lft, auto rht, auto... args) {
        T pr{}; T pl{};
        for (T idx = rht; idx >= 0; idx = idx & (idx + 1), idx --) pr += bit[idx].query(args...);
        for (T idx = lft - 1; idx >= 0; idx = idx & (idx + 1), idx --) pl += bit[idx].query(args...);
        return pr - pl;
    }
};

/** https://acm.timus.ru/problem.aspx?space=1&num=1470&locale=en **/
int main() {
    BIT<int, 128, 128, 128> bit;

    int N; cin >> N;
    int type;
    while (true) {
        cin >> type;
        if (type == 1) {
            int x; int y; int z; int diff;
            cin >> x >> y >> z >> diff;
            bit.updateDiff(diff, x, y, z);
        }
        else if (type == 2) {
            int x1; int y1; int z1; int x2; int y2; int z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << bit.query(x1, x2, y1, y2, z1, z2) << endl;
        }
        else {
            break;
        }
    }
}
