#include "bits/stdc++.h"
# define ll long long
using namespace std;

int bit_amount = 18;
int exponent_max = (int)(pow(2, bit_amount - 1) + 1e-9);

vector<bool> bit_decomp (int n) {
    vector<bool> bits (bit_amount);
    int exponent = exponent_max;
    for (int i = bit_amount - 1; i >= 0; i --) {
        if (n / exponent == 1) {
            bits[i] = true;
            n -= exponent;
        }
        exponent /= 2;
    }
    return bits;
}

int main () {
    // build prefix-sum table
    int UPPER_BOUND = 200001;
    vector<vector<int>> prefix_table (UPPER_BOUND);
    prefix_table[0] = vector<int>(bit_amount);
    for (int i = 1; i < UPPER_BOUND; i ++) {
        vector<int> bit_set = prefix_table[i - 1];
        vector<bool> bit_set_info = bit_decomp(i);
        for (int j = 0; j < bit_amount; j ++) {
            if (bit_set_info[j] == true) {
                bit_set[j] ++;
            }
        }
        prefix_table[i] = bit_set;
    }

    // read out answers for test cases
    int N; cin >> N;
    for (int t = 0; t < N; t ++) {
        int a; cin >> a;
        int b; cin >> b;
        int best_answer = (b - a + 1);
        for (int i = 0; i < bit_amount; i ++) {
            int set_bits = prefix_table[b][i] - prefix_table[a - 1][i];
            if (set_bits > 0) {
                best_answer = min(best_answer, (b - a + 1) - set_bits);
            }
        }
        cout << best_answer << endl;
    }
}
