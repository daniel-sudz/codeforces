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

/*
   visits nodes: 2  0  5  1  4  5
   in this case 5 is repeat 
   pop until first 5 
   connected component: 5 1 4
   drop unrelated nodes: 2 0
 */
struct node{
    short dirx; short diry; int cost=-1;
};
int dfs(pii cord, vector<vector<node>>& graph) {
    if(cord.first<0 || cord.second<0 || cord.first>=graph.size() || cord.second>=graph[0].size()) {
        return 0;
    }
    else if(graph[cord.first][cord.second].cost !=-1) {
        return graph[cord.first][cord.second].cost;
    }
    else {
        int xd = graph[cord.first][cord.second].dirx;
        int yd = graph[cord.first][cord.second].diry;
        int cost = 1 + dfs({cord.first + xd, cord.second + yd}, graph);
        graph[cord.first][cord.second].cost=cost; 
        return cost;
    }
}

void cc(pii cord, vvi& vis, vector<vector<node>>& graph) {
    stack<pii> s; 
    s.push(cord); 
    vis[cord.first][cord.second]=-1;
    while(true) {
        int xd = graph[cord.first][cord.second].dirx;
        int yd = graph[cord.first][cord.second].diry;
        cord.first += xd; cord.second += yd;
        if(cord.first<0 || cord.first>=graph.size() || cord.second<0 || cord.second>=graph[0].size()) break; 
        if(vis[cord.first][cord.second] == 1) break;
        else if(vis[cord.first][cord.second] == 0) {
            vis[cord.first][cord.second] = -1;
            s.push(cord); 
        }
        else {
            int count=1;
            auto c1 = s; auto c2 = s;
            while(c1.size() && c1.top() != cord) {
                count++;
                c1.pop();
            }
            graph[cord.first][cord.second].cost=count;
            while(c2.size() && c2.top() != cord) {
                graph[c2.top().first][c2.top().second].cost=count;
                c2.pop();
            }
            break;
        }
    }
    while(s.size()) {
        vis[s.top().first][s.top().second]=1;
        s.pop();
    }
}

int main() {
    fastio;
    int T;cin>>T;
    for(int tc=0;tc<T;tc++) {
        int H; int W; cin>>H>>W;
        vector<vector<node>> graph(W, vector<node>(H));
        for(int y=0;y<H;y++) {
            for(int x=0;x<W;x++) {
                char c; cin>>c;
                int dirx=0; int diry=0;
                if(c=='U') diry--;
                if(c=='D') diry++;
                if(c=='L') dirx--;
                if(c=='R') dirx++;
                graph[x][y].dirx=dirx;
                graph[x][y].diry=diry;
            }
        }
        vvi vis(W, vi(H));
        for(int y=0;y<H;y++) {
            for(int x=0;x<W;x++) {
                pii cord = {x,y}; 
                if(vis[cord.first][cord.second]==0) cc(cord, vis, graph);
            }
        }
        pair<int, pii> best={1, {0, 0}};
        for(int y=0;y<H;y++) {
            for(int x=0;x<W;x++) {
                pii cord = {x,y};
                best=max(best, {dfs(cord, graph), cord});
            }
        }
        cout<<best.second.second+1<<" "<<best.second.first+1<<" "<<best.first<<endl;
    }
}
