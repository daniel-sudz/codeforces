#include <bits/stdc++.h>
#define pb push_back
#define read cin
#define write cout
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

/* sample input
7 15
15 5 3 7 9 14 0

2.5000000000

2 5
2 5
2.0000000000
*/

int main() {
    int N;
    int L;
    read >> N >> L;

    vector<int> lanterns(N);
    for (int i = 0; i < N; i ++) {
        read >> lanterns[i];
    }
    sort(lanterns.begin(), lanterns.end());

    int max_dist = 0;
    for (int i = 0; i < N - 1; i ++) {
        max_dist = max(max_dist, lanterns[i + 1] - lanterns[i]);
    }
    int endpoints_max_dist = max(lanterns[0], L - lanterns[N -1]);
    if (endpoints_max_dist * 2 > max_dist) {
        write << endpoints_max_dist << endl;
    }
    else {
        // avoid floating point error
        if ((max_dist / 2) * 2 == max_dist) {
            write << (max_dist / 2) << endl;
        }
        else {
            write << (max_dist / 2) << ".5" << endl;
        }
    }
}
