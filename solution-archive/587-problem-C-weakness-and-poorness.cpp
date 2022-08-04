#include "bits/stdc++.h"
using namespace std;

int N;
vector<double> values;

double weakness(double N) {
    // scan to negative
    double running_sum = values[0] - N;
    double largest_negative = values[0] - N;
    for (int i = 1; i < values.size(); i ++) {
        largest_negative = min(largest_negative, running_sum);
        double val = values[i] - N;
        if (running_sum > 0 || running_sum + val > 0) {
            running_sum = val;
        }
        else {
            running_sum = running_sum + val;
        }
        largest_negative = min(largest_negative, running_sum);
    }

    // scan to positive
    running_sum = values[0] - N;
    double largest_positive = values[0] - N;
    for (int i = 1; i < values.size(); i ++) {
        largest_positive = max(largest_positive, running_sum);
        double val = values[i] - N;
        if (running_sum < 0 || running_sum + val < 0) {
            running_sum = val;
        }
        else {
            running_sum = running_sum + val;
        }
        largest_positive = max(largest_positive, running_sum);
    }

    return max(abs(largest_negative), abs(largest_positive));
}

double ternary_bin_search() {
    double low = -10000.0;
    double high = 10000.0;
    for (int i = 0; i < 100; i ++) {
        double L1 = ((high - low) / 3.0) + low;
        double L2 = ((high - low) * (2.0 / 3.0)) + low;
        double L1_sol = weakness(L1);
        double L2_sol = weakness(L2);
        if (L1_sol > L2_sol) {
            low = L1;
        }
        else {
            high = L2;
        }
    }
    return weakness(low);
}

int main () {
    cin >> N;
    cout << fixed << setprecision(20);
    for (int i = 0; i < N; i ++) {
        double a; cin >> a;
        values.push_back(a);
    }
    cout << ternary_bin_search() << endl;
}
