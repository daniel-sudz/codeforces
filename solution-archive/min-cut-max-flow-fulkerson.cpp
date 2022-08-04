#include <vector>
#include <set>
#include <ostream>
#include <iostream>
using namespace std;

// Ford–Fulkerson min-cut max-flow (1956)
// https://informatics.msk.ru/mod/statements/view.php?chapterid=111772#1

struct pipe {
    pipe(int t, int c, pipe* i, bool inv) { to = t; capacity = c; inverse = i; isInverse = inv;};
    int to; int capacity; pipe* inverse; bool isInverse;
};

pipe* pipe_with_residual(int node, int to, int capacity) {
    pipe* p = new pipe(to, capacity, nullptr, false);
    pipe* p_inverse = new pipe(node, 0, nullptr, true);
    p->inverse = p_inverse;
    p_inverse->inverse = p;
    return p;
}

int N; // systems
int S; // escape sinks
int T; // transport corridors
bool print_at_least_one = false;
vector<vector<pipe*>> G;

// find a path increasing flow by 1
// return value signifies if we have found such a path
// and if we need to unwind the stack to record it
bool dfs(int node, vector<bool>& vis, vector<pipe*>& collector) {
    if (!vis[node]) {
        vis[node] = true;
        for (pipe* neighbor : G[node]) {
            if (neighbor->capacity > 0) {
                bool terminal = dfs(neighbor->to, vis, collector);
                if (terminal || neighbor->to == N) {
                    collector.push_back(neighbor);
                    return true;
                }
            }
        }
    }
    return false; // not terminal
}

// given a path, update the residual network
void augment(vector<pipe*>& path) {
    for (pipe* p: path) {
        p->capacity --;
        p->inverse->capacity ++;
    }
}

// find nodes belonging to the cut containing the source
void cut_connection(int node, vector<bool>& vis, set<int>& collector) {
    if (!vis[node]) {
        vis[node] = true;
        for (pipe* neighbor: G[node]) {
            if (neighbor->capacity > 0) {
                collector.insert(neighbor->to);
                cut_connection(neighbor->to, vis, collector);
            }
        }
    }
}

int main() {
    cin >> N >> S;
    G.resize(N + 1);

    // collect sinks into super sink
    for (int i = 0; i < S; i ++) {
        int sink; cin >> sink; sink --;
        pipe* p = pipe_with_residual(sink, N, 10000000 /** infinity **/);
        G[sink].push_back(p);
        G[N].push_back(p->inverse);
    }

    // rest of graph
    cin >> T;
    for (int i = 0; i < T; i ++) {
        int node; int to; cin >> node >> to;
        node --; to --;
        pipe* p = pipe_with_residual(node, to, 1);
        G[node].push_back(p);
        G[to].push_back(p->inverse);
    }

    // augmentation until max flow
    int max_flow = 0;
    while (true) {
        vector<bool> vis(N + 1);
        vector<pipe*> collector;
        dfs(0, vis, collector);
        if (collector.size() == 0) break;
        augment(collector);
        max_flow ++;
    }
    cout << max_flow << endl;

    // find nodes in min cut
    set<int> nodes_in_cut = {0};
    vector<bool> vis(N + 1);
    cut_connection(0, vis, nodes_in_cut);

    // find pipes connecting across the cut
    for (int node: nodes_in_cut) {
        for (auto pipe: G[node]) {
            if (!nodes_in_cut.count(pipe->to) && !pipe->isInverse) {
                if (!print_at_least_one) cout << node + 1 << " " << pipe->to + 1;
                else  cout << " " << node + 1 << " " << pipe->to + 1;
                print_at_least_one = true;
            }
        }
    }

}
