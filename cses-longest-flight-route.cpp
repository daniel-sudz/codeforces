#include "bits/stdc++.h"
# define ll long long
# define read cin
using namespace std;

int num_cities;
int num_flights;
vector<vector<int>> graph;

struct node_result { bool is_reachable = false; int max_edges = -1; };
vector<node_result> dp;

node_result memoize(int city) {
    // handle already solved case
    if (dp[city].max_edges != -1) return dp[city];

    // handle generic case
    node_result solution = { false, 0 };
    for (int neighbor : graph[city]) {
        node_result resolve = {memoize(neighbor).is_reachable, memoize(neighbor).max_edges + 1};
        if (resolve.is_reachable && resolve.max_edges > solution.max_edges) {
            solution = {true, resolve.max_edges};
        }
    }
    dp[city] = solution;
    return solution;
}

int main () {
    read >> num_cities >> num_flights;
    graph.resize(num_cities);
    dp.resize(num_cities);
    dp[num_cities - 1] = {true, 0};

    for (int i = 0; i < num_flights; i ++) {
        int a; int b;
        read >> a >> b;
        a --; b --;
        graph[a].push_back(b);
    }

    node_result sol = memoize(0);
    if (sol.is_reachable == false) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    cout << sol.max_edges + 1 << endl;
    cout << 1 << " ";
    // trace out the flight plan
    int cur_node = 0;
    int max_edges = sol.max_edges;
    while (max_edges != 0) {
        for (int neighbor : graph[cur_node]) {
            if (dp[neighbor].max_edges == max_edges - 1 && dp[neighbor].is_reachable) {
                cur_node = neighbor;
                cout << neighbor + 1 << " ";
                break;
            }
        }
        max_edges --;
    }
}
