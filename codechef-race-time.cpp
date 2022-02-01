#include "bits/stdc++.h"
# define ll long long
using namespace std;

int N; int K;
struct racer {int speed; int start; };
vector<racer> racers;

double calculate(double T) {
    double min_pos = 1e20;
    double max_pos = -1.0 * 1e20;
    for (racer cur_racer : racers) {
        double racer_pos = cur_racer.speed * T + cur_racer.start;
        min_pos = min(min_pos, racer_pos);
        max_pos = max(max_pos, racer_pos);
    }
    return (max_pos - min_pos);
}

double ternary_search() {
    double low = 0.0;
    double high = double (K);
    for(int i = 0; i < 100; i ++) {
        double L1 = ((high - low) / (3.0)) + low;
        double L2 = (2.0 * ((high - low) / (3.0))) + low;
        double L1_calc = calculate(L1);
        double L2_calc = calculate(L2);
        if (L1_calc > L2_calc) {
            low = L1;
        }
        else {
            high = L2;
        }
    }
    return calculate(low);
}

int main () {
    cin >> N >> K;
    for (int i = 0; i < N; i ++) {
        int speed; int start; cin >> speed >> start;
        racers.push_back( {speed, start} );
    }
    cout << fixed << setprecision(6) << ternary_search() << endl;
}
