#include "bits/stdc++.h"
#define pb push_back
#define endl '\n'
#define mp make_pair
#define pb push_back
using namespace std;;void __print(const int& x) {cerr << x;};void __print(const long& x) {cerr << x;};void __print(const long long& x) {cerr << x;};void __print(const unsigned& x) {cerr << x;};void __print(const unsigned long& x) {cerr << x;};void __print(const unsigned long long& x) {cerr << x;};void __print(const float& x) {cerr << x;};void __print(const double& x) {cerr << x;};void __print(const long double& x) {cerr << x;};void __print(const char& x) {cerr << '\'' << x << '\'';};void __print(const char *x) {cerr << '\"' << x << '\"';};void __print(const string &x) {cerr << '\"' << x << '\"';};void __print(const bool& x) {cerr << (x ? "true" : "false");};template<typename T> concept Container = requires(T t) { begin(t); end(t); size(t); };void __print(const stack<auto>& s);void __print(const deque<auto>& x);void __print(const queue<auto>& q);void __print(const pair<auto, auto>& p);template <Container C> void __print(const C& c);;        void __print(const stack<auto>& s) {;            auto c = s; ;            cerr<<"{STACK_TOP  ";;            while(c.size()) {;                auto v=c.top();;                c.pop(); ;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const queue<auto>& q) {;            auto c = q;;            cerr<<"{QUEUE_FONT ";;            while(c.size()) {;                auto v=c.front();;                c.pop();;                __print(v);;                cerr<<(c.size()?",":"");;            };            cerr<<"}";;        };    ;;        void __print(const deque<auto>& x) {;            cerr<<"{"; ;            for(auto& v: x) {;                __print(v);;;                if(&v != &x.back()) cerr<<","; ;            };            cerr<<"}";;        };    ;void __print(const pair<auto, auto> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';};template <Container C> void __print(const C &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";};void _print() {cerr << "]\n";};template <typename T, typename... V> void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);};auto min_many(auto a) {return a;};auto min_many(auto a, auto b, auto... c) {return min_many(std::min(a,b),c...);};auto max_many(auto a) {return a;};auto max_many(auto a, auto b, auto... c) {return max_many(std::max(a,b),c...);};typedef long long ll;typedef vector<int> vi;typedef vector<bool> vb;typedef vector<long long> vll;typedef vector<vector<int>> vvi;typedef vector<vector<long long>> vvll;typedef pair<int, int> pii;typedef pair<long long, long long> pll;typedef vector<pair<int, int>> vpii;typedef vector<vector<pair<int, int>>> vvpii;typedef vector<pair<long long, long long>> vpll;typedef vector<vector<pair<long long, long long>>> vvpll;
#ifdef ONLINE_JUDGE
# define debug(x...)
# define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#else
# define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
# define fastio
#endif

// VALIDATION: (AC) https://leetcode.com/problems/erect-the-fence/submissions/863466794/

namespace convex_hull {
    // conduct a right hand rule sweep using origin from p1 to p2 
    // return 1 if the z-direction points out of the paper, -1 if into the paper
    int cmp(pll o, pll p1, pll p2) {
        auto diff = (p1.first-o.first)*(p2.second-o.second) - (p1.second-o.second)*(p2.first-o.first); 
        return (diff > 0) - (diff < 0);
    }
    ll sqrdist(pll p1, pll p2) {
        return (p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second);
    }
    vector<pll> graham_sweep(vector<pll> points) {
        if(points.size() <= 3) return points;
        pll lowest = *min_element(points.begin(),points.end()); 
        sort(points.begin(),points.end(),[lowest](pll a, pll b) {
                if(cmp(lowest,a,b) != 0) return cmp(lowest,a,b) > 0;
                return sqrdist(lowest,a) < sqrdist(lowest,b);
                });
        vector<pll> ch;
        for(pll c: points) {
            ch.pb(c); 
            while(ch.size() >= 3 && cmp(ch[ch.size()-3],ch[ch.size()-2],ch[ch.size()-1]) < 0) {
                pll top = ch.back();
                ch.pop_back(); 
                ch.pop_back(); 
                ch.pb(top);
            }
        }
        // add back colinear points at the end
        vector<pll> colin; 
        for(pll p: points) {
            if(cmp(ch.front(),ch.back(),p)==0 && cmp(ch[0],ch[1],p)!=0 && p != ch.front() && p != ch.back()) {
                colin.pb(p);
            }
        }
        sort(colin.begin(),colin.end(),[lowest](pll a, pll b){return sqrdist(lowest,a) > sqrdist(lowest,b);});
        for(pll p: colin) ch.pb(p);
        return ch;
    }
    vector<pll> jarvis_gift(vector<pll> points) {
        vb used(points.size());
        vector<pll> ch;
        pll* widest = &*min_element(points.begin(),points.end());
        while((ch.size() == 0) || (!used[widest - &*points.begin()] && cmp(ch.front(),ch.back(),*widest) >= 0)) {
            ch.pb(*widest);
            used[widest - &*points.begin()] = true;
            widest = &*points.begin();
            for(auto& p: points) {
                if(used[widest - &*points.begin()]) widest = &p;
                else if(!used[&p - &*points.begin()]) {
                    if(cmp(ch.back(),p,*widest) > 0) widest = &p;
                    else if(cmp(ch.back(),p,*widest) == 0 && sqrdist(ch.back(),*widest) > sqrdist(ch.back(),p)) {
                        widest = &p;
                    }
                }
            }
        }
        //debug(*widest);
        return ch;
    }
};

int main() {
    fastio;
    int N; cin>>N; 
    set<pll> spoints;
    vpll points; 
    for(int i=0;i<N;i++) {
        int a; int b;  cin>>a>>b;
        spoints.insert({a,b});
    }
    points = vpll(spoints.begin(),spoints.end());
    cout<<endl<<endl<<endl;
    cout<<convex_hull::jarvis_gift(points).size()<<endl;
    for(auto v: convex_hull::jarvis_gift(points)) cout<<v.first<<" "<<v.second<<endl;
    cout<<endl<<endl<<endl;
    cout<<convex_hull::graham_sweep(points).size()<<endl;
    for(auto v: convex_hull::graham_sweep(points)) cout<<v.first<<" "<<v.second<<endl; 
}
