#include "bits/stdc++.h"
# define ll long long
using namespace std;

int ROWS; int COLUMNS;
int MAX_LEFT; int MAX_RIGHT;
int START_X; int START_Y;

struct node {
    node() {};
    node(bool a, int d) { walkable = a; distance = d; };
    bool walkable = false; int distance = INT_MAX;
};
struct cord {
    cord(int a, int b) { x = a; y = b; };
    int x; int y;
};
struct move_t {
    move_t (int a, int b, int c) { x_shift = a; y_shift = b; cost_shift = c; };
    int x_shift; int y_shift; int cost_shift;
};

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> ROWS >> COLUMNS;
    cin >> START_Y >> START_X; START_X--; START_Y--;
    cin >> MAX_LEFT >> MAX_RIGHT;
    vector<vector<node>> graph(COLUMNS, vector<node>(ROWS));
    for (int y = 0; y < ROWS; y ++) {
        for (int x = 0; x < COLUMNS; x ++) {
            char z; cin >> z;
            graph[x][y] = {z == '.', INT_MAX};
        }
    }

    graph[START_X][START_Y] = {true, 0};
    int iter = 0;
    queue<cord> cur; cur.push({START_X, START_Y});
    queue<cord> next;
    while (cur.empty() == false) {
        while (cur.empty() == false) {
            cord top = cur.front();
            cur.pop();
            vector<move_t> moves = {{0, 1, 0}, {0, -1, 0}, {1, 0, 1}, {-1, 0, 1} };
            for (move_t move : moves) {
                if (top.x + move.x_shift >= 0 && top.x + move.x_shift < graph.size() && top.y + move.y_shift >= 0 && top.y + move.y_shift < graph[0].size()) {
                    node& neighbor = graph[top.x + move.x_shift][top.y + move.y_shift];
                    if (neighbor.walkable && neighbor.distance == INT_MAX) {
                        neighbor.distance = iter + move.cost_shift;
                        if (move.cost_shift == 0) cur.push({top.x + move.x_shift, top.y + move.y_shift});
                        else next.push({top.x + move.x_shift, top.y + move.y_shift});
                    }
                }
            }
        }
        iter ++;
        cur = next;
        next = queue<cord>();
    }

    ll ret = 0;
    for (int x = 0; x < graph.size(); x ++) {
        for (int y = 0; y < graph[0].size(); y ++) {
            ll wleft = 0; ll wright = 0;
            ll actualWalk = abs(START_X - x);
            if (START_X < x) {
                wright = actualWalk;
            }
            else {
                wleft = actualWalk;
            }
            ll wasted = (graph[x][y].distance - actualWalk) / 2;
            wleft += wasted;
            wright += wasted;
            if (wleft <= MAX_LEFT && wright <= MAX_RIGHT) {
                ret ++;
            }
        }
    }
    cout << ret << endl;
}
