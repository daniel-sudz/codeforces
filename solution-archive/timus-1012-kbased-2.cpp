#include "bits/stdc++.h"
# define ll long long
using namespace std;

int N; int K;

struct simple_long_math {
    vector<unsigned int> state;
    simple_long_math(vector<unsigned int> state_int) { state = state_int; }
    void add_to_state(vector<unsigned int>& to_add) {
        int it_length = max(to_add.size(), state.size());
        ll s; ll c = 0;
        for (int i = 0; i < it_length; i ++) {
            s = c; c = 0;
            if (i < state.size()) s += state[i];
            if (i < to_add.size()) s += to_add[i];
            if (s >= 100000000) { s -= 100000000; c = 1; }
            if (i < state.size()) state[i] = s;
            else { state.push_back(s); }
        }
        if (c == 1) state.push_back(1);
    }
    vector<int> serialize_to_output() {
        vector<int> ret;
        for (int i = 0; i < state.size(); i ++) {
            for (int j = 0; j < 8; j ++) {
                ret.push_back(state[i] % 10);
                state[i] = state[i] / 10;
            }
        }
        return ret;
    }
};

int main () {
    cin >> N >> K;
    simple_long_math prev = simple_long_math({1});
    simple_long_math cur = simple_long_math({(unsigned int) K - 1});
    for (int i = 0; i < N - 1; i ++) {
        simple_long_math next = simple_long_math({0});
        for (int j = 0; j < K - 1; j++) {
            next.add_to_state(prev.state);
            next.add_to_state(cur.state);
        }
        prev.state = cur.state;
        cur.state = next.state;
    }
    auto ret = cur.serialize_to_output();
    bool trailing = false;
    for (int i = ret.size() - 1; i >= 0; i --) {
        if (!trailing && ret[i] == 0) continue;
        else {
            trailing = true;
            cout << ret[i];
        }
    }
    cout << endl;
}
