template<typename T> class segment_tree {
private: vector<T> G;
    function<T(T,T)> op;
    T zero_val;
    int levels = 1;

    // construct a segment tree with interval [1, range]
    // and associative binary operation (T, T) -> T
public: segment_tree(function<T(T, T)> op_init, int range) {
        while (range >>= 1) levels ++;
        G.resize((1 << levels) - 1);
        op = op_init;
    }

private: int LEFT(int n) { return (n * 2) + 1; }
    int RIGHT(int n) { return (n * 2) + 2; }
    int UP(int n) { return (n - 1) / 2; }
    bool ONE_IN_TWO(int l1, int r1, int l2, int r2) { return (l1 >= l2 && l1 <= r2 && r1 >= l2 && r1 <= r2); }
    bool ONE_PARTIAL_TWO(int l1, int r1, int l2, int r2) { return ((l1 >= l2 && l1 <= r2) || (r1 >= l2 && r1 <= r2)); }
    bool EITHER_PARTIAL(int l1, int r1, int l2, int r2) { return ONE_PARTIAL_TWO(l1, r1, l2, r2) || ONE_PARTIAL_TWO(l2, r2, l1, r1); }

    // update a single index in interval [1, range] with a new value
public: void update(int index, T val) {
        int ref = (1 << levels - 1) - 2 + index;
        G[ref] = val;
        while (ref != 0) {
            G[UP(ref)] = op(G[LEFT(UP(ref))], G[RIGHT(UP(ref))]);
            ref = UP(ref);
        }
    }

    // query interval [l, r] with 1 >= l,r <= range
public: T query(int l, int r) { return query(l, r, 0, 1, (1 << (levels - 1))); }
private: T query(int l, int r, int node, int nl, int nr) {
        if (ONE_IN_TWO(nl, nr, l, r)) return G[node];
        int ll = nl;
        int lr = nl + (nr - nl) / 2;
        int rl = lr + 1;
        int rr = nr;
        if (EITHER_PARTIAL(l, r, ll, lr) && EITHER_PARTIAL(l, r, rl, rr)) {
            return op(query(l, r, LEFT(node), ll, lr), query(l, r, RIGHT(node), rl, rr));
        }
        else if (EITHER_PARTIAL(l, r,ll, lr)) { return query(l, r, LEFT(node), ll, lr); }
        else { return query(l, r, RIGHT(node), rl, rr); }
    }
};


class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int offset = 100000;
        segment_tree<int> st([](int a, int b){ return a + b;}, 200002 );
        vector<int> ret(nums.size());
        for (int i = nums.size() - 1; i >= 0; i --) {
            if (nums[i] + offset == 1) ret[i] = 0;
            else ret[i] = st.query(1, nums[i] + offset - 1);
            st.update(nums[i] + offset, 1 + st.query(nums[i] + offset, nums[i] + offset));
        }
        return ret;
    }
};
