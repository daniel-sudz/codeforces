#include <bits/stdc++.h>
using namespace std;

int main() {
    int T; cin >> T;
    for (int a = 0; a < T; a ++) {
        int N; cin >> N;
        int minshift = 0;
        for (int b = 0; b < N; b ++) {
            int val; cin >> val;
            int curshift = val - (b + 1);
            minshift = max(minshift, curshift);
        }
        cout << minshift << "\n";
    }
}
