#include "bits/stdc++.h"
# define ll long long
using namespace std;

ll N; ll F;
vector<ll> days_to_mature;

bool check(ll min_days) {
    ll booster_used = 0;
    for (ll day_to_mature: days_to_mature) {
        booster_used += max(0ll, day_to_mature - min_days);
    }
    if (booster_used <= F) return true;
    return false;
}

int main() {
    cin >> N;
    for (ll i = 0; i < N; i ++) {
        ll a; string b;
        cin >> b >> a;
        days_to_mature.push_back(a);
    }
    cin >> F;

    ll low = 0; ll high = 1000000ll; ll mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }
    cout << low << endl;
}
