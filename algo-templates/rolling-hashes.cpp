class Solution {
public:
    #define ll long long 

    struct RollingHash {
        static constexpr uint64_t mod = (1ull<<61) - 1;
        inline uint64_t modmul(uint64_t a, uint64_t b){
            uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
            uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
            uint64_t ret = (l&mod) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
            ret = (ret & mod) + (ret>>61);
            ret = (ret & mod) + (ret>>61);
            return ret-1;
        }
        inline uint64_t modadd(uint64_t a, uint64_t b) {return (a+b)%mod;}
        
        #define u64 uint64_t
        u64 hash = 0;    
        u64 base = (ll)1e8;
        u64 tail = 1;
        queue<char> state;

        RollingHash(string start) {
            for(char c: start) state.push(c);
            reverse(start.begin(),start.end());
            ll exp = 1;
            for(char c: start) {
                hash = modadd(hash,modmul(c,exp));
                exp = modmul(exp, base);
            }  
            tail = exp;
        }

        u64 push(char c) {
            hash = modmul(hash, base);
            hash = modadd(hash, modmul(tail,mod-state.front()));
            hash = modadd(hash, c);
            state.pop();
            state.push(c);
            return hash;
        }

        bool equal(RollingHash b) {
            return hash == b.hash;
        }

    };

    vector<int> get_matches(string s, string m) {
        if(m.size() > s.size()) return {};
        RollingHash patt(m);
        RollingHash tar(string(s.begin(),s.begin()+m.size()));
        vector<int> ret = (patt.equal(tar) ? vector<int>({0}) : vector<int>()); 
        for(int i=m.size();i<s.size();i++) {
            tar.push(s[i]);
            if(patt.equal(tar)) ret.push_back(i-m.size()+1);
        }
        return ret;
    }

    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> ma = get_matches(s,a);
        return {};
        vector<int> mb = get_matches(s,b);
        set<int> mbs = set<int>(mb.begin(),mb.end());
        vector<int> ans;
        for(int v: ma) {
            if(mbs.size()) {
                int spread = INT_MAX;
                auto lb = mbs.lower_bound(v);
                if(lb != mbs.end() && *lb == v) spread = 0;
                else if(lb != mbs.begin()) {
                    lb = prev(lb);
                    spread = min(spread, v-*lb);
                }
                auto ub = mbs.upper_bound(v);
                if(ub != mbs.end()) spread = min(spread, *ub-v);
                if(spread <= k) ans.push_back(v);
            }
        }
        return ans;
    };
};
