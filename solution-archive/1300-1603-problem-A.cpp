#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i ++) {
        int N;
        cin >> N;
        bool skipChecks = false;
        int a;
        for (a = 0; a < N; a ++ ) {
            int val;
            cin >> val;
            bool possible = false;
            if (skipChecks == false) {
                for (int b = 0; b <= a; b++) {
                    if (val % (b + 2) != 0) {
                        possible = true;
                        break;
                    }
                }
                if (possible == false) {
                    cout << "NO\n";
                    skipChecks = true;
                }
            }
        }
        if (!skipChecks && a == N) {
            cout << "YES\n";
        }
    }
}
