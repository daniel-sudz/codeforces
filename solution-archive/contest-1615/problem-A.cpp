#include "bits/stdc++.h"
# define ll long long
using namespace std;

int T;

int main () {
    cin >> T;
    for (int i = 0; i < T; i ++) {
        int N; cin >> N;
        int total = 0;
        for (int j = 0; j < N; j ++) {
            int a; cin >> a;
            total += a;
        }
        if (total % N == 0) {
            cout << 0 << endl;
        }
        else {
            cout << 1 << endl;
        }
    }
}
