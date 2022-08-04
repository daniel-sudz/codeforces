#include "bits/stdc++.h"
# define ll long long
using namespace std;

ll NUM_NODES;
ll NUM_ROADS;

struct edge{
    edge(ll sw, ll t, ll tw){ supported_weight = sw; time = t; to_where = tw; }
    ll supported_weight; ll time; ll to_where;
};
vector<vector<edge>> graph;

// check if we can drive to the destination in 24 hours with given weight
bool validate(ll total_weight) {
    struct node{
        node(ll ninit, ll csinit) { number = ninit; cur_sol = csinit; }
        ll number; ll cur_sol;
    };
    struct cmp{
        const bool operator()(const node* l, const node* r) const {
            if (l->cur_sol == r->cur_sol) return l->number < r->number; // allow deletion by value in queue
            return l->cur_sol < r->cur_sol;
        }
    };
    set<node*, cmp> queue;
    map<ll, node*> node_to_state;
    for (ll i = 1; i <= NUM_NODES; i ++) {
        node* n = new node(i, ((i == 1) ? 0 : INT_MAX));
        queue.insert(n);
        node_to_state[i] = n;
    }
    while (!queue.empty()) {
        node* pop_off = *queue.begin();
        queue.erase(queue.begin());
        node_to_state[pop_off->number] = nullptr;
        if (pop_off->number == NUM_NODES) {
            return pop_off->cur_sol <= (24 * 60);
        }
        for (auto e : graph[pop_off->number]) {
            if (e.supported_weight >= total_weight) {
                if (node_to_state[e.to_where] && node_to_state[e.to_where]->cur_sol > e.time + pop_off->cur_sol) {
                    if (e.time + pop_off->cur_sol <= (24 * 60) && e.to_where == NUM_NODES) {
                        return true;
                    }
                    queue.erase(node_to_state[e.to_where]);
                    node* n = new node(e.to_where, e.time + pop_off->cur_sol);
                    queue.insert(n);
                    node_to_state[e.to_where] = n;
                }
            }
        }
    }
    return false;
}

int main () {
    cin >> NUM_NODES >> NUM_ROADS;
    graph.resize(NUM_NODES + 1);
    for (ll i = 0; i < NUM_ROADS; i ++) {
        ll from; ll to; ll t; ll w;
        cin >> from >> to >> t >> w;
        graph[from].push_back({w, t, to});
        graph[to].push_back({w, t, from});
    }

    // special case where we don't need to drive the truck so it's weight isn't included
    if (NUM_NODES == 1) {
        cout << 10000000 << endl;
        return 0;
    }

    ll empty_truck = 3 * 1000 * 1000; // 3 tons = 3 * (1000 kg/ton) * (1000 g/kg)
    if (!validate(empty_truck)) {
        cout << 0 << endl;
        return 0;
    }

    // bin search on max supported weighted
    ll low = 0;
    ll high = 1000000000;
    while (low < high) {
        ll mid = (low + high + 2) / 2;
        if (validate(mid)) {
            low = mid;
        }
        else {
            high = mid - 1;
        }
    }
    cout << (low - empty_truck) / 100 << endl;
}
