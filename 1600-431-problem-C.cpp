#include <bits/stdc++.h>
#define read cin
#define write cout
using namespace std;

/* sample cases
https://codeforces.com/problemset/problem/431/C
3 3 2
3
3 3 3
1
4 3 2
6
4 5 2
7
*/

long N; long K; long D;
long MOD_VALUE = 1000000007;
map<long, long> perms_satisfied;
map<long, long> perms_not_satisfied;

map<long, long>* get_perms(bool satisfied) {
    if (satisfied) return &perms_satisfied;
    return &perms_not_satisfied;
}

// % operator type casts to int and overflows
long modulo(long x) {
    while (x >= MOD_VALUE) {
        x -= MOD_VALUE;
    }
    return x;
}

int main() {
    read >> N >> K >> D;
    (*get_perms(false))[N] = 1;
    for (long running_total = N - 1; running_total >= 0; running_total--) {
        long satified_combinations = 0;
        long unsatisfied_combinations = 0;
        for (long i = 1; i <= K; i++) {
            long next_total = running_total + i;
            if (i >= D) {
                satified_combinations = modulo(satified_combinations + (*get_perms(true))[next_total]);
                satified_combinations = modulo(satified_combinations + (*(get_perms(false)))[next_total]);
            } else {
                satified_combinations = modulo( satified_combinations + (*get_perms(true))[next_total]);
                unsatisfied_combinations = modulo( unsatisfied_combinations + (*(get_perms(false)))[next_total]);
            }
        }
        (*get_perms(true))[running_total] = modulo(satified_combinations);
        (*get_perms(false))[running_total] = modulo(unsatisfied_combinations);
    }
    write << modulo((*get_perms(true))[0]) << endl;
}
