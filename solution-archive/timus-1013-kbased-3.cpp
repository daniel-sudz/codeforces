#include "bits/stdc++.h"
# define ll unsigned long long
# define lll __uint128_t
using namespace std;

lll N; lll K; lll M;
struct typeA { lll a; lll b; lll c; lll d; };
typeA main_accumulator;
typeA cur_accumulator;
lll cur_accum_count = 1;

typeA mmult(typeA ONE, typeA TWO) {
    return {
            ((ONE.a * TWO.a) % M + (ONE.b * TWO.c) % M) % M,
            ((ONE.a * TWO.b) % M + (ONE.b * TWO.d) % M) % M,
            ((ONE.c * TWO.a) % M + (ONE.d * TWO.c) % M) % M,
            ((ONE.c * TWO.b) % M + (ONE.d * TWO.d) % M) % M
    };
}

int main () {
    ll a; ll b; ll c; cin >> a >> b >> c;
    N = a; K = b; M = c;
    main_accumulator = { K - 1, K - 1, 1, 0};
    cur_accumulator = { K - 1, K - 1, 1, 0};
    lll remaining = N - 1;

    while (remaining != 0) {
        while (cur_accum_count + cur_accum_count <= remaining) {
            cur_accumulator = mmult(cur_accumulator, cur_accumulator);
            cur_accum_count *= 2;
        }
        main_accumulator = mmult(cur_accumulator, main_accumulator);
        remaining -= cur_accum_count;
        cur_accum_count = 1;
        cur_accumulator = { K - 1, K - 1, 1, 0};
    }
    lll ret = ((main_accumulator.c * (K - 1)) % M + main_accumulator.d % M) % M;
    cout << (ll) (ret) << endl;
}
