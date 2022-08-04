#include "bits/stdc++.h"
# define ll long long
# define read cin
using namespace std;

int N;
struct potential_solution{
    ll start_index; ll end_index; ll cost;
    bool operator<(const potential_solution& b) const {
        return start_index < b.start_index;
    }
};
map<ll, vector<ll>> moisture_to_index;

vector<potential_solution> rolling_calc (ll moisture_to_calc) {
    vector<ll>& indexes = moisture_to_index[moisture_to_calc];
    vector<potential_solution> ret;
    ll rolling_front = indexes[indexes.size() - 1] - indexes[0];
    ll rolling_back = 0;
    for (ll i = 0; i < indexes.size(); i ++) {
        ll sol_1 = rolling_front + rolling_front + rolling_back;
        ll sol_2 = rolling_back + rolling_back + rolling_front;
        if (i + 1 < indexes.size()) {
            ll dist = indexes[i + 1] - indexes[i];
            rolling_front -= dist;
            rolling_back += dist;
        }
        // if we are on the highest moisture, it does not matter where we end
        // addresses bug when we cast current_rolling_calc to last_cross_join for the first iteration
        // as last_cross_join is a map of start_index -> cost only while current_rolling_calc is (start_index, end_index) -> cost
        if (moisture_to_calc == moisture_to_index.rbegin()->first) ret.push_back( {indexes[i], -1, min(sol_1, sol_2)} );
        else {
            ret.push_back( {indexes[i], indexes[0], sol_1 } );
            ret.push_back( {indexes[i], indexes[indexes.size() - 1], sol_2 } );
        }
    }
    return ret;
}

// it is evident that during a cross-join of sol_a & sol_b we want to match the end_index of sol_a to the closest start_index of sol_b
// it can be shown through simple contradiction that no other optimal solution can exist
// there are two of these potentially optimal solutions (to the left and to the right) which we can find through a binary search
vector<potential_solution> find_closest_solutions (potential_solution a, set<potential_solution>& solution_b) {
    potential_solution tmp = { a.end_index, -1, -1 };
    auto sol_1 = solution_b.lower_bound(tmp);
    auto sol_2 = sol_1; sol_2 --;
    if (sol_1 != solution_b.begin()) return {*sol_1, *sol_2};
    return {*sol_1};
}

set<potential_solution> cross_join_rolling_calc (vector<potential_solution> solutions_a, set<potential_solution> solution_b) {
    unordered_map<ll, ll> solution_set;
    set<potential_solution> ret;
    for (auto sol_a : solutions_a) {
        for (auto sol_b: find_closest_solutions(sol_a, solution_b)) {
            potential_solution join_sol = { sol_a.start_index, -1, sol_a.cost + sol_b.cost + abs(sol_b.start_index - sol_a.end_index) };
            if (solution_set.count(join_sol.start_index)) solution_set[join_sol.start_index] = min(solution_set[join_sol.start_index], join_sol.cost);
            else solution_set[join_sol.start_index] = join_sol.cost;
        }
    }
    for (auto it: solution_set) ret.insert( {it.first, -1, it.second} );
    return ret;
}

int main () {
    read >> N;
    for (ll i = 1; i <= N; i ++) {
        ll a; read >> a;
        moisture_to_index[a].push_back(i);
    }
    for (auto it: moisture_to_index) {
        auto arr = it.second;
        sort(arr.begin(), arr.end());
    }

    vector<potential_solution> current_rolling_calc;
    set<potential_solution> last_cross_join;

    for (auto it = moisture_to_index.rbegin(); it != moisture_to_index.rend(); it ++) {
        current_rolling_calc = rolling_calc(it->first);
        if (it == moisture_to_index.rbegin()) {
            last_cross_join = set<potential_solution>(current_rolling_calc.begin(), current_rolling_calc.end());
        }
        else {
            last_cross_join = cross_join_rolling_calc(current_rolling_calc, last_cross_join);
        }
    }

    ll min_cost = LONG_LONG_MAX;
    for (auto it: last_cross_join) {
        min_cost = min(min_cost, it.cost + it.start_index - 1);
    }

    cout << min_cost + N << endl;
}
