#include "bits/stdc++.h"
# define ll long long
using namespace std;

ll M;

int main() {
    multiset<int> M_set;
    vector<int> readings;
    cin >> M;

    while (true) {
        int a; cin >> a;
        if (a == -1) break;
        readings.push_back(a);
    }

    int last_read_index = 0;
    int first_read_index = M;

    for (int i = 0; i < M; i ++) M_set.insert(readings[i]);
    cout << *M_set.rbegin() << endl;

    while (first_read_index < readings.size()) {
        M_set.erase(M_set.find(readings[last_read_index]));
        M_set.insert(readings[first_read_index]);
        cout << *M_set.rbegin() << endl;
        last_read_index ++; first_read_index++;
    }
}
