#include <bits/stdc++.h>
#define read cin
#define write cout
using namespace std;
 
/* sample cases
*/
# define ll long long int
 
ll N;
ll heat_times;
vector<ll> particles;
 
 
bool check_sol(ll cauldron_size) {
    ll cauldron_attemps = 0;
    ll particle_loc = 0;
    ll partial_fill = 0;
    while (cauldron_attemps < heat_times && particle_loc < N) {
        if (partial_fill + particles[particle_loc] > cauldron_size) {
            cauldron_attemps ++;
            partial_fill = 0;
        }
        else {
            partial_fill += particles[particle_loc];
            particle_loc ++;
        }
    }
    if (particle_loc == N) {
        return true;
    }
    return false;
}
 
int main() {
 
    read >> N >> heat_times;
    particles.resize(N);
    for (ll i = 0; i < N; i ++) {
        read >> particles[i];
    }
    ll low = 0;
    ll high = 500000000001LL;
    ll med;
    while (low < high) {
        med = (low + high) / 2;
        bool sol_good = check_sol(med);
        if (sol_good) {
            high = med;
           // cout << high << endl;
        }
        else {
            low = med + 1;
        }
    }
    cout << high << endl;
}
