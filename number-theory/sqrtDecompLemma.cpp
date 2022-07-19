#include "bits/stdc++.h"
# define ll long long

#ifdef ONLINE_JUDGE
    # define watch(x) {}
    # define printv(n) {}
#else
    # define watch(x) {cerr<<(#x)<<" is "<<(x)<<endl;}
    # define printv(n) {for(auto v:n) cerr<<v<<" ";cerr<<endl;}
#endif

using namespace std;

/**
 * lemma: given ints a,n,k
 * a = floor(n / k) <==> k = floor(n / a)
 *
 * it follows that we can trivially find
 * all such unique values of floor(n / k)
 * and that there are at most 2 * sqrt(n) such values
 */
vector<int> sqrtDecomp(int n, int K) {
    vector<int> ret;
    int i;
    for (i = 1; i <= K && i * i <= n; i ++) {
        if (n / K <= i) ret.push_back(i);
    }
    for (i --; i >= 1; i --) ret.push_back(n / i);
    return ret;
}

int solve(vector<int>& nums, int K) {
    vector<int> M(100005); M[1] = 1;
    for (int n : nums) {
        vector<int> decomp = sqrtDecomp(n, K);
        M[1] = max(M[1], decomp[0]);
        for (int i = 1; i < decomp.size(); i ++) {
            M[decomp[i - 1] + 1] = max(M[decomp[i - 1] + 1], decomp[i]);
        }
    }
    int rm = M[0];
    for (int i = 0; i < M.size(); i ++) {
        rm = max(rm, M[i]);
        M[i] = rm;
    }
    pair<int, int> best_sol = make_pair(INT_MAX, 1);
    for (int i = 1; i <= nums[0]; i ++) {
        if (M[i] - i < best_sol.first) {
            best_sol = {M[i] - i, i};
        }
    }
    return best_sol.first;
}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        int N; int K;
        cin >> N >> K;
        vector<int> nums;
        for (int i = 0; i < N; i ++) {
            int a; cin >> a;
            nums.push_back(a);
        }
        cout << solve(nums, K) << endl;
    }
}
