#include "bits/stdc++.h"
# define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
# define pb push_back
using namespace std;typedef pair<int,int> pii;typedef vector<int> vi;typedef vector<pii> vpii;typedef vector<vector<int>> vvi;

// binary jumping and LCA 
// verified using https://www.spoj.com/problems/LCASQ/

int cdepth(int node, vi& G, vi& depth) {
    if(depth[node] != -1) return depth[node];
    depth[node] = cdepth(G[node],G,depth) + 1;
    return depth[node];
}

void jump_init(int node, vi& G, vvi& jump) {
    if(jump[node][0] != -1) return;    
    jump_init(G[node],G,jump);
    int ref = G[node];
    for(int j=0;j<jump[0].size();j++) {
        jump[node][j] = ref;
        ref = jump[ref][j];
    }
}

int cjump(int node, int j, vvi& jump) {
    for(int i=jump[0].size()-1;i>=0;i--) {
        if(j >= (1<<i)) {
            j -= (1<<i); 
            node = jump[node][i];
        }
    }
    return node;
}

int lca(int a, int b, vi& depth, vvi& jump) {
    if(depth[a] < depth[b]) swap(a,b);
    a = cjump(a,depth[a]-depth[b],jump);
    for(int i=jump[0].size()-1;i>=0;i--) {
        if(cjump(a,(1<<i),jump) != cjump(b,(1<<i),jump)) {
            a = cjump(a,(1<<i),jump);
            b = cjump(b,(1<<i), jump);
        }
    }
    if(a == b) return a; 
    return cjump(a,1,jump);
}

int main() {
    fastio;
    int N;cin>>N;
    vi G(N); 
    for(int p=0;p<N;p++) {
        int M;cin>>M;
        for(int j=0;j<M;j++) {
            int c; cin>>c;
            G[c]=p;
        }
    }
    int Q;cin>>Q;
    vpii queries; 
    for(int i=0;i<Q;i++) {
        int a;int b; cin>>a>>b;
        queries.pb({a,b});
    }

    // calc depth of tree 
    vi depth(N,-1); depth[0]=0;
    for(int i=0;i<N;i++) cdepth(i,G,depth);

    // init binary jumping
    int LOG=20;
    vvi jump(N,vi(LOG,-1));
    jump[0] = vi(LOG,0);
    for(int i=0;i<N;i++) jump_init(i,G,jump);
   
    // run lca queries
    for(pii q: queries) cout<<lca(q.first,q.second,depth,jump)<<endl;
}
