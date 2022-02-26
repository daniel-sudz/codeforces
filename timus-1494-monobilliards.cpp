#include "bits/stdc++.h"
# define ll long long
using namespace std;

int N;
stack<int> s;

int main () {
    cin >> N;
    s.push(1);
    int max_seen = 1;
    for (int i = 1; i < N; i ++) {
        int next; cin >> next;
        if (next > max_seen) {
            for (int j = max_seen + 1; j < next; j ++) {
                s.push(j);
            }
            max_seen = next;
        }
        else {
            if (s.top() != next) {
                cout << "Cheater" << endl;
                exit(0);
            }
            s.pop();
        }
    }
    cout << "Not a proof" << endl;
}
