#include "bits/stdc++.h"
using namespace std;

int N; int M;

int main () {
    cin >> N >> M;
    multiset<int> test_takers;
    int running_sum = 0;
    for (int i = 0; i < N; i ++) {
        int a; cin >> a;
        int sub_sum = 0;
        int sub_prob_answer = 0;
        auto it_max = test_takers.rbegin();
        while (running_sum + a - sub_sum > M) {
            sub_sum += *it_max;
            sub_prob_answer ++;
            it_max ++;
        }
        running_sum += a;
        test_takers.insert(a);
        cout << sub_prob_answer << endl;
    }
}
