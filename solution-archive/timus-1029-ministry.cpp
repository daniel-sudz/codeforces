#include "bits/stdc++.h"
# define ll long long
using namespace std;

// 1029 Ministry
// https://acm.timus.ru/problem.aspx?space=1&num=1029

ll M;
ll N;

enum direction {
    move_up, move_left, move_right, nullable_na
};

struct Office {
    ll value;
    enum direction d;
};

Office scan_direction(vector<vector<Office>> &dp, vector<vector<ll>> &building, ll loc_x, ll loc_y,
                      ll directional_operator) {
    ll running_x = building[loc_y][loc_x];
    ll best_sol = running_x + dp[loc_y + 1][loc_x].value;
    ll initial_sol = best_sol;
    loc_x += directional_operator;
    while (loc_x >= 0 && loc_x < N) {
        ll next_running_x = running_x + building[loc_y][loc_x];
        ll next_sol = next_running_x + dp[loc_y + 1][loc_x].value;
        best_sol = min(best_sol, next_sol);
        running_x = next_running_x;
        loc_x += directional_operator;
    }
    if (initial_sol == best_sol) {
        return {best_sol, move_up};
    }
    return {best_sol, directional_operator == 1 ? move_right : move_left};
}

void read_sol(vector<vector<Office>> &dp, ll x, ll y) {
    Office cur_office = dp[y][x];
    cout << x + 1 << " ";
    if (y == M - 1) {
        return;
    }
    if (cur_office.d == move_right) x ++;
    if (cur_office.d == move_left) x --;
    if (cur_office.d == move_up) y++;
    read_sol(dp, x, y); // this should be tail end unrolled
}

int main() {
    cin >> M >> N;

    vector<vector<Office>> dp(M);
    vector<vector<ll>> building(M);
    for (ll i = 0; i < M; i++) {
        building[i].resize(N);
        dp[i].resize(N);
        for (ll j = 0; j < N; j++) {
            cin >> building[i][j];
        }
    }

    // copy last row
    for (ll i = 0; i < N; i++) {
        dp[M - 1][i] = {building[M - 1][i], nullable_na};
    }

    // build dp table
    for (ll i = M - 2; i >= 0; i--) {
        vector<Office> next_dp_row(N);
        for (ll j = 0; j < N; j++) {
            Office left_scan = scan_direction(dp, building, j, i, -1);
            Office right_scan = scan_direction(dp, building, j, i, +1);
            if (left_scan.value < right_scan.value) {
                next_dp_row[j] = left_scan;
            } else {
                next_dp_row[j] = right_scan;
            }
        }
        dp[i] = next_dp_row;
    }

    // scan initial row for min
    ll entry_point_min = dp[0][0].value;
    ll entry_x = 0;
    for (ll i = 0; i < N; i++) {
        if (dp[0][i].value < entry_point_min) {
            entry_point_min = dp[0][i].value;
            entry_x = i;
        }
    }

    // read solution from dp table
    read_sol(dp, entry_x, 0);
}
