#include "bits/stdc++.h"
# define ll long long
using namespace std;

ll N; ll K; ll M;

int main() {
    cin >> N >> K; M = INT_MAX; // prob 1 is special case of problem 2/3 ignore modulo
    // initial state for last digit
    __int128 dp_combos_no_zero = K - 1;
    ll dp_combos_one_zero = 1;
    for (__int128 i = 2; i <= N; i ++) {
        __int128 new_dp_combos_no_zero; __int128 new_dp_combos_one_zero;
        new_dp_combos_no_zero = (dp_combos_no_zero * (K - 1) + dp_combos_one_zero * (K - 1)) % M;
        new_dp_combos_one_zero = (dp_combos_no_zero) % M;
        dp_combos_no_zero = new_dp_combos_no_zero; dp_combos_one_zero = new_dp_combos_one_zero;
    }
    cout << (ll) dp_combos_no_zero << endl;
}
