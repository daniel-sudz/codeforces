#include <vector>
#include <set>
#include <ostream>
#include <iostream>
#include <cstring>
using namespace std;

// https://informatics.msk.ru/mod/statements/view.php?chapterid=111663#1

struct cord {
    int x; int y;
    cord() {};
    cord (int xi, int yi) { x = xi; y = yi; };
};

struct pipe {
    cord to; pipe* inverse; int capacity;
    pipe (cord t, pipe* i, int c) { to = t; inverse = i; capacity = c; };
};

pipe* pipe_with_inverse (cord from, cord to, int capacity) {
    pipe* p = new pipe(to, nullptr, capacity);
    p->inverse = new pipe(from, p, 0);
    return p;
}

int X; int Y;
cord REMOVE_1; cord REMOVE_2;
pipe* G[202][202][5] = {0};
bool vis[202][202] = {0};
vector<pipe*> SOURCE_SET;
vector<pipe*> SINK_SET;
cord SOURCE(202 - 1, 202 - 1); cord SINK(202 - 2, 202 - 2);

bool is_a_source(int x, int y) {return ((x + y) % 2 == 0);}
bool is_a_cutout(int x, int y) {return ((x == REMOVE_1.x && y == REMOVE_1.y) || (x == REMOVE_2.x && y == REMOVE_2.y));}

bool can_increase_flow(cord node) {
    if (!vis[node.x][node.y]) {
        vis[node.x][node.y] = true;
        if (node.x == SOURCE.x && node.y == SOURCE.y) {
            for (pipe* neighbor : SOURCE_SET) {
                if (neighbor && neighbor->capacity > 0) {
                    if ((neighbor->to.x == SINK.x && neighbor->to.y == SINK.y) || can_increase_flow(neighbor->to)) {
                        neighbor->capacity --;
                        neighbor->inverse->capacity ++;
                        return true;
                    }
                }
            }
        }
        else {
            for (pipe* neighbor : G[node.x][node.y]) {
                if (neighbor && neighbor->capacity > 0) {
                    if ((neighbor->to.x == SINK.x && neighbor->to.y == SINK.y) || can_increase_flow(neighbor->to)) {
                        neighbor->capacity --;
                        neighbor->inverse->capacity ++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void fill_val(int x, int y, pipe* value) {
    int i = 0;
    while (G[x][y][i] != nullptr) i ++;
    G[x][y][i] = value;
}

int main() {
    cin >> X >> Y;

    cin >> REMOVE_1.x >> REMOVE_1.y >> REMOVE_2.x >> REMOVE_2.y;
    REMOVE_1.x --; REMOVE_1.y --; REMOVE_2.x --; REMOVE_2.y --;

    // gen graph
    for (int y = 0; y < Y; y ++) {
        for (int x = 0; x < X; x ++) {
            if (!is_a_cutout(x, y)) {
                if (is_a_source(x, y)) {
                    pipe* p = pipe_with_inverse(cord(SOURCE.x, SOURCE.y), cord(x, y), 1);
                    SOURCE_SET.push_back(p);
                    fill_val(x, y, p->inverse);

                    if (x + 1 < X) { // right
                        pipe* p = pipe_with_inverse(cord(x, y), cord(x + 1, y), 1);

                        fill_val(x, y, p);
                        fill_val(x + 1, y, p->inverse);
                    }
                    if (x - 1 >= 0) { // left
                        pipe* p = pipe_with_inverse(cord(x, y), cord(x - 1, y), 1);
                        fill_val(x,y, p);
                        fill_val(x - 1, y, p->inverse);
                    }
                    if (y + 1 < Y) { // up
                        pipe* p = pipe_with_inverse(cord(x, y), cord(x, y + 1), 1);
                        fill_val(x, y, p);
                        fill_val(x, y + 1, p->inverse);
                    }
                    if (y - 1 >= 0) { // down
                        pipe* p = pipe_with_inverse(cord(x, y), cord(x, y - 1), 1);
                        fill_val(x, y, p);
                        fill_val(x, y - 1, p->inverse);
                    }
                }
                else {
                    pipe* p = pipe_with_inverse(cord(x, y), SINK, 1);
                    fill_val(x, y, p);
                    SINK_SET.push_back(p->inverse);
                }
            }
        }
    }

    // max flow
    while (true) {
        memset(vis,0,202 * 202 * sizeof(bool));
        if (!can_increase_flow(SOURCE)) {
            break;
        }
    }

    for (pipe* p : SOURCE_SET) {
        if (p->capacity != 0) {
            cout << "NO" << endl;
            return 0;
        }
    }
    for (pipe* p : SINK_SET) {
        if (p->inverse->capacity != 0) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
}
