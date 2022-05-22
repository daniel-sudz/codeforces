#include <vector>
#include <set>
#include <ostream>
#include <iostream>
using namespace std;

// "chemistry" problem
// https://informatics.msk.ru/mod/statements/view.php?chapterid=2785#1

struct cord {
    int x; int y;
    cord (int xi, int yi) { x = xi; y = yi; };
};

struct pipe {
    cord to = cord(-1, -1); int capacity; pipe* inverse;
    pipe(cord t, int c, pipe *i) {
        to = t; capacity = c; inverse = i;
    }
};

pipe* pipe_with_residual(cord node, cord to, int capacity) {
    pipe* p = new pipe(to, capacity, nullptr);
    pipe* p_inverse = new pipe(node, 0, nullptr);
    p->inverse = p_inverse;
    p_inverse->inverse = p;
    return p;
}

int X; int Y; int TOTAL_VALENCE = 0; int BOARD_SIZE = 50; int TOTAL_VALID_CHARS = 0;
cord SOURCE(BOARD_SIZE, BOARD_SIZE + 0);
cord SINK(BOARD_SIZE + 1, BOARD_SIZE + 1);
vector<vector<vector<pipe*>>> G(BOARD_SIZE + 2, vector<vector<pipe*>>(BOARD_SIZE + 2));
vector<vector<char>> B(BOARD_SIZE + 2, vector<char>(BOARD_SIZE + 2));

// alternate source/sink based on chessboard coloring
bool is_source(int x, int y) {
    if (x % 2 == 0 && y % 2 == 0) return true;
    if (x % 2 == 1 && y % 2 == 1) return true;
    return false;
}

// find a path increasing flow by 1
// return value signifies if we have found such a path
// and if we need to unwind the stack to record it so that augmentation of network can be calculated
bool dfs(cord node, vector<vector<bool>>& vis, vector<pipe*>& collector) {
    if (!vis[node.x][node.y]) {
        vis[node.x][node.y] = true;
        for (pipe* neighbor : G[node.x][node.y]) {
            if (neighbor->capacity > 0) {
                bool terminal = dfs(neighbor->to, vis, collector);
                if (terminal || (neighbor->to.x == SINK.x && neighbor->to.y == SINK.y)) {
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

int main() {
    cin >> Y >> X;
    // build the flow network
    // based on the pattern of a chessboard, we mark elements as sources or sinks
    // this allows satisfying the valence requirement of all elements
    for (int y = 0; y < Y; y ++) { for (int x = 0; x < X; x ++) { char c; cin >> c; B[x][y] = c;}}
    for (int y = 0; y < Y; y ++) {
        for (int x = 0; x < X; x ++) {
            char c = B[x][y];
            if (c == '.') continue;
            TOTAL_VALID_CHARS ++;
            int valence;
            if (c == 'H') valence = 1;
            if (c == 'O') valence = 2;
            if (c == 'N') valence = 3;
            if (c == 'C') valence = 4;
            TOTAL_VALENCE += valence;
            if (is_source(x, y)) {
                // connect with super source
                pipe* p = pipe_with_residual(SOURCE, cord(x, y), valence);
                G[SOURCE.x][SOURCE.y].push_back(p);
                G[x][y].push_back(p->inverse);

                // right pipe
                if (x + 1 < X && B[x + 1][y] != '.') {
                    pipe* p = pipe_with_residual(cord(x, y), cord(x + 1, y), 1);
                    G[x][y].push_back(p);
                    G[x + 1][y].push_back(p->inverse);
                }
                // left pipe
                if (x - 1 >= 0 && B[x - 1][y] != '.') {
                    pipe* p = pipe_with_residual(cord(x, y), cord(x - 1, y), 1);
                    G[x][y].push_back(p);
                    G[x - 1][y].push_back(p->inverse);
                }
                // up pipe
                if (y + 1 < Y && B[x][y + 1] != '.') {
                    pipe* p = pipe_with_residual(cord(x, y), cord(x, y + 1), 1);
                    G[x][y].push_back(p);
                    G[x][y + 1].push_back(p->inverse);
                }
                // down pipe
                if (y - 1 >= 0 && B[x][y - 1] != '.') {
                    pipe* p = pipe_with_residual(cord(x, y), cord(x, y - 1), 1);
                    G[x][y].push_back(p);
                    G[x][y - 1].push_back(p->inverse);
                }
            }
            else {
                // connect with super sink
                pipe* p = pipe_with_residual(cord(x, y), SINK, valence);
                G[x][y].push_back(p);
                G[SINK.x][SINK.y].push_back(p->inverse);
            }
        }
    }

    // run the max flow algo
    while (true) {
        vector<vector<bool>> vis(BOARD_SIZE + 2, vector<bool>(BOARD_SIZE + 2));
        vector<pipe*> collector;
        if (dfs(SOURCE, vis, collector)) {
            augment(collector);
        }
        else {
            break;
        }
    }
    // requirement of problem that we have at least one element
    if (TOTAL_VALID_CHARS == 0) {
        cout << "Invalid" << endl;
        return 0;
    }

    // all sources filled
    for (pipe* pipe : G[SINK.x][SINK.y]) {
        if (pipe->inverse->capacity != 0) {
            cout << "Invalid" << endl;
            return 0;
        }
    }

    // all sinks filled
    for (pipe* pipe : G[SOURCE.x][SOURCE.y]) {
        if (pipe->capacity != 0) {
            cout << "Invalid" << endl;
            return 0;
        }
    }

    cout << "Valid" << endl;
}
