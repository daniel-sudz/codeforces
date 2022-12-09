#include "bits/stdc++.h"
#define pb push_back
#define endl '\n'
#define mp make_pair
#define pb push_back
using namespace std;;void __print(const int& x) {cerr << x;};void __print(const long& x) {cerr << x;};void __print(const long long& x) {cerr << x;};void __print(const unsigned& x) {cerr << x;};void __print(const unsigned long& x) {cerr << x;};void __print(const unsigned long long& x) {cerr << x;};void __print(const float& x) {cerr << x;};void __print(const double& x) {cerr << x;};void __print(const long double& x) {cerr << x;};void __print(const char& x) {cerr << '\'' << x << '\'';};void __print(const char *x) {cerr << '\"' << x << '\"';};void __print(const string &x) {cerr << '\"' << x << '\"';};void __print(const bool& x) {cerr << (x ? "true" : "false");};template<typename T> concept Container = requires(T t) { begin(t); end(t); size(t); };void __print(const stack<auto>& s);void __print(const deque<auto>& x);void __print(const queue<auto>& q);void __print(const pair<auto, auto>& p);template <Container C> void __print(const C& c);;        void __print(const stack<auto>& s) {;            auto c = s; ;            cerr<<"{STACK_TOP  ";;            while(c.size()) {;                auto v=c.top();;                c.pop(); ;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const queue<auto>& q) {;            auto c = q;;            cerr<<"{QUEUE_FONT ";;            while(c.size()) {;                auto v=c.front();;                c.pop();;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const deque<auto>& x) {;            cerr<<"{"; ;            for(auto& v: x) {;                __print(v);;;                if(&v != &x.back()) cerr<<","; ;            };            cerr<<"}";;        };    ;void __print(const pair<auto, auto> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';};template <Container C> void __print(const C &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";};void _print() {cerr << "]\n";};template <typename T, typename... V> void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);};typedef long long ll;typedef vector<int> vi;typedef vector<bool> vb;typedef vector<long long> vll;typedef vector<vector<int>> vvi;typedef vector<vector<long long>> vvll;typedef pair<int, int> pii;typedef pair<long long, long long> pll;typedef vector<pair<int, int>> vpii;typedef vector<vector<pair<int, int>>> vvpii;typedef vector<pair<long long, long long>> vpll;typedef vector<vector<pair<long long, long long>>> vvpll;
#ifdef ONLINE_JUDGE
# define debug(x...)
# define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#else
# define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
# define fastio
#endif

// verification 
// https://cses.fi/problemset/task/1651/

struct lazy_segtree {
    vpll st; int N=1;
    lazy_segtree(int n) {
        while(N < (n+1)) N *= 2;
        N--;
        st.resize(2*N+1); 
    }
    void update(int node,int ul,int ur,int cl,int cr,ll diff) {
        if(ul <= cl && ur >= cr) {
            st[node].first += diff;
            st[node].second += diff;
        }
        else if(!(ul > cr || ur < cl)) {
            st[node].first += diff;
            update(node*2+1,ul,ur,cl,cl+(cr-cl)/2,diff);
            update(node*2+2,ul,ur,cl+(cr-cl+2)/2,cr,diff);
        }
    }
    ll query(int node,int ul,int ur,int cl,int cr) {
        if(ul <= cl && ur >= cr) {
            return st[node].first;
        }
        else if(!(ul > cr || ur < cl)) {
            st[node*2+1].first += st[node].second;
            st[node*2+1].second += st[node].second;
            st[node*2+2].first += st[node].second;
            st[node*2+2].second += st[node].second;
            st[node].second = 0ll;
            return query(node*2+1,ul,ur,cl,cl+(cr-cl)/2) + query(node*2+2,ul,ur,cl+(cr-cl+2)/2,cr);
        }
        return 0ll; 
    }
    void update(int l, int r,ll diff) {update(0,l,r,0,N-1,diff);}
    ll query(int l,int r) {return query(0,l,r,0,N-1);}

};


int main() {
    fastio;
    int N; int Q; cin>>N>>Q;
    lazy_segtree st(N);
    for(int i=1;i<=N;i++) {
        int a;cin>>a; st.update(i,i,a);
    }
    for(int i=0;i<Q;i++) {
        int type; cin>>type; 
        if(type == 1) {
            int a; int b; int u; cin>>a>>b>>u;
            st.update(a,b,u);
        }
        else {
           int k; cin>>k;
           cout<<st.query(k,k)<<endl;
        }
    }
}
