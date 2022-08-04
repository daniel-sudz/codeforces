#include "bits/stdc++.h"
# define ll long long
using namespace std;

int N; int K;

struct node {int val; int jumps; bool jump_accum; };
vector<node> merge_sort(vector<node> arr) {
    if (arr.size() == 1) return arr;
    vector<node> l_arr = vector<node>(arr.begin(), arr.begin() + arr.size() / 2);
    vector<node> r_arr = vector<node> (arr.begin() + arr.size() / 2, arr.end());
    l_arr = merge_sort(l_arr);
    r_arr = merge_sort(r_arr);
    // we can jump r -> l
    vector<node> ret(l_arr.size() + r_arr.size());
    int l_index = 0;
    int r_index = 0;
    int ret_index = 0;
    while (true) {
        if (l_index < l_arr.size() && r_index < r_arr.size() && l_arr[l_index].val < r_arr[r_index].val) {
            ret[ret_index] = l_arr[l_index];
            l_index ++;
        }
        else if (l_index < l_arr.size() && r_index < r_arr.size()) {
            ret[ret_index] = { r_arr[r_index].val, r_arr[r_index].jumps, 1 };
            r_index ++;
        }
        else if (l_index < l_arr.size()) {
            ret[ret_index] = l_arr[l_index];
            l_index ++;
        }
        else if (r_index < r_arr.size()) {
            ret[ret_index] = { r_arr[r_index].val, r_arr[r_index].jumps, 1 };
            r_index ++;
        }
        else { break; }
        ret_index ++;
    }
    // reduce jump count
    int accum = 0;
    for (int i = ret.size() - 1; i >= 0; i --) {
        if (ret[i].jump_accum) {
            ret[i].jumps += accum;
        }
        else if (ret[i].jump_accum == false) {
            accum ++;
        }
        ret[i].jump_accum = false;
    }
    return ret;
}

int main () {
    cin >> N >> K;
    int max_row = -1;
    int max_jumps = -1;
    for (int i = 0; i < K; i ++) {
        vector<node> cur_row;
        for (int j = 0; j < N; j ++) {
            int a; cin >> a;
            cur_row.push_back({a, 0, 0});
        }
        auto ret = merge_sort(cur_row);
        int count_jumps = 0;
        for (int k = 0; k < ret.size(); k ++) {
            count_jumps += ret[k].jumps;
        }
        if (count_jumps > max_jumps) {
            max_jumps = count_jumps;
            max_row = i + 1;
        }
    }
    cout << max_row << endl;
}
