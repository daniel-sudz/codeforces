#include "bits/stdc++.h"
using namespace std;

struct segment_tree {
    static const int min_l = 0;
    static const int max_r = 32000;
    struct node {
        int value = 0;
        node* left_ptr = nullptr;
        node* right_ptr = nullptr;
        node* parent_ptr = nullptr;
    };
    node* root = new node();
    node* bottom_row[max_r + 1];
    bool seg_1_completely_in_seg_2(int l_1, int r_1, int l_2, int r_2) { return (l_1 >= l_2 && r_1 <= r_2); };
    bool seg_1_no_overlap_seg_2(int l_1, int r_1, int l_2, int r_2) { return (l_1 > r_2 || r_1 < l_2); };
    void init(node* parent, int l = min_l, int r = max_r) {
        if (l == r) bottom_row[l] = parent;
        if (l != r) {
            parent->left_ptr = new node;
            parent->right_ptr = new node;
            parent->left_ptr->parent_ptr = parent;
            parent->right_ptr->parent_ptr = parent;
            init(parent->left_ptr, l, (l + r) / 2);
            init(parent->right_ptr,(l + r + 2) / 2, r);
        }
    }
    int calculate(int l, int r, int node_l, int node_r, node* cur_node) {
        if (seg_1_completely_in_seg_2(node_l, node_r, l, r)) {
            return cur_node->value; // full overlap
        }
        else if (!seg_1_no_overlap_seg_2(node_l, node_r, l, r)) {
            int l_val = calculate(l, r, node_l, (node_l + node_r) / 2, cur_node->left_ptr);
            int r_val = calculate(l, r, (node_l + node_r + 2) / 2, node_r, cur_node->right_ptr);
            return l_val + r_val; // partial overlap
        }
        return 0; // no overlap
    }
    int calculate(int l, int r) { return calculate(l, r, min_l, max_r, root); };
    void refresh_from_node(node* cur_node) {
        if (cur_node == root) return;
        cur_node->parent_ptr->value = cur_node->parent_ptr->left_ptr->value + cur_node->parent_ptr->right_ptr->value;
        refresh_from_node(cur_node->parent_ptr);
    }
    void update_from_key(int key, int value) {
        bottom_row[key]->value = value;
        refresh_from_node(bottom_row[key]);
    }
};

int main () {
    segment_tree t;
    t.init(t.root);
    int N; cin >> N;
    vector<int> level(N);
    for (int i = 0; i < N; i ++) {
        int a; int b; cin >> a >> b;
        int calc = t.calculate(0, a);
        level[calc] ++;
        t.update_from_key(a, t.bottom_row[a]->value + 1);
    }
    for (int i = 0; i < N; i ++) cout << level[i] << endl;
}
