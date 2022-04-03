#include "bits/stdc++.h"
# define ll long long
using namespace std;

ll N; ll ret = 0;
struct cow { int index; int height; };

int main() {
    cin >> N;
    stack<cow> cows;
    for (int i = 0; i < N; i ++) {
        int a; cin >> a;
        cow next_cow = {i, a};
        while (!cows.empty()) {
            // inequality preserved, cows strictly in descending order
            if (cows.top().height > next_cow.height) {
                break;
            }
            /**
             *  inequality broken, the top cow has two cows that can throw to each other
             *      1) the next_cow
             *      2) the previous_cow
             */
            cow top = cows.top();
            cows.pop();
            ret += next_cow.index - top.index + 1;
            if (!cows.empty()) ret += top.index - cows.top().index + 1;
        }
        cows.push(next_cow);
    }
    while (cows.size() >= 2) {
        cow top = cows.top();
        cows.pop();
        ret += top.index - cows.top().index + 1;
    }
    cout << ret << endl;
}
