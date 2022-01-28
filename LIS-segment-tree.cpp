#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
    struct segment_tree {
        constexpr static int exp() {
            int n = 1;
            for (int i = 0; i < query_range_exp; i ++) n *= 2;
            return n;
        }
        static const int query_range_exp = 15;
        static const int query_range_max;
        vector<int> graph;
        segment_tree() {
            graph.resize(query_range_max * 2 - 1);
        }

        int g_left(int x) { return (2 * x + 1); };
        int g_right(int x) { return (g_left(x) + 1); };
        int g_up(int x) { return ((x + 1) / 2) - 1; };
        bool seg_1_completely_in_seg_2(int l_1, int r_1, int l_2, int r_2) { return (l_1 >= l_2 && r_1 <= r_2); };
        bool seg_1_no_overlap_seg_2(int l_1, int r_1, int l_2, int r_2) { return (l_1 > r_2 || r_1 < l_2); };

        void update(int key, int value) {
            int node = (query_range_max - 2) + key;
            graph[node] = value;
            while (node != 0) {
                graph[g_up(node)] = max(graph[node], graph[g_right(g_up(node))]);
                node = g_up(node);
            }
        }

        int calculate(int l, int r, int n_l = 1, int n_r = query_range_max, int c_n = 0) {
            if (seg_1_completely_in_seg_2(n_l, n_r, l, r)) return graph[c_n];
            if (seg_1_no_overlap_seg_2(n_l, n_r, l, r)) return 0;
            int l_calc = calculate(l, r, n_l, ((n_l + n_r)/2), g_left(c_n));
            int r_calc = calculate(l, r, ((n_l + n_r)/2) + 1, n_r, g_right(c_n));
            return max(l_calc, r_calc);
        }
    };
    int lengthOfLIS(vector<int>& nums) {
        segment_tree t;
        for (int num: nums) {
            num += 10001; // normalize input
            int append = t.calculate(1, num - 1);
            t.update(num, append + 1);
        }
        return t.calculate(1, segment_tree::query_range_max);
    }
};
const int Solution::segment_tree::query_range_max = Solution::segment_tree::exp();


int main () {
    vector<int> test = {10,9,2,5,3,7,101,18};
    Solution sol;
    cout << sol.lengthOfLIS(test) << endl;
}
