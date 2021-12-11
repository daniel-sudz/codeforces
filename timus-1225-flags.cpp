#include <bits/stdc++.h>
using namespace std;

# define ll long long

/*
 *  On the Day of the Flag of Russia a shop-owner decided to decorate the show-window of his shop with textile stripes of white, blue and red colors. He wants to satisfy the following conditions:
    Stripes of the same color cannot be placed next to each other.
    A blue stripe must always be placed between a white and a red or between a red and a white one.
    Determine the number of the ways to fulfill his wish
 */

int N;

// positions
ll R_X = 1;
ll W_X = 1;

ll W_B = 0;
ll R_B = 0;

int main() {
    cin >> N;

    for (int i = 1; i < N; i ++) {
        if (N == 1) break; // base case

        // step transition
        ll new_R_X = W_X + W_B;
        ll new_W_X = R_X + R_B;
        ll new_W_B = W_X;
        ll new_R_B = R_X;

        R_X = new_R_X;
        W_X = new_W_X;
        W_B = new_W_B;
        R_B = new_R_B;
    }

    cout << R_X + W_X << endl;
}
