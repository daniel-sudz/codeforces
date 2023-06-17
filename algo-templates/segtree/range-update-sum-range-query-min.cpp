#include "bits/stdc++.h"
#define pb push_back
#define endl '\n'
#define mp make_pair
#define pb push_back
using namespace std; typedef complex<double> cd;typedef complex<long double> cld;typedef unsigned int ui;typedef unsigned long long ull;typedef long long ll;typedef vector<int> vi;typedef vector<bool> vb;typedef vector<long long> vll;typedef vector<vector<int>> vvi;typedef vector<vector<long long>> vvll;typedef pair<int, int> pii;typedef pair<long long, long long> pll;typedef vector<pair<int, int>> vpii;typedef vector<vector<pair<int, int>>> vvpii;typedef vector<pair<long long, long long>> vpll;typedef vector<vector<pair<long long, long long>>> vvpll;
#ifdef ONLINE_JUDGE
# define debug(x...)
# define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#else
# define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
# define fastio
#endif

//https://codeforces.com/contest/1838/submission/209987722

struct lazy_segtree {
    vpll st; int N=1;
    lazy_segtree(int n) { // indicies [0...n-1] supported
        N = bit_ceil((ui)n);
        st.resize(2*N-1);
    }
    void push_down(int node) {
        if(node*2+2 < st.size()) {
            st[node*2+1].first += st[node].second;
            st[node*2+1].second += st[node].second;
            st[node*2+2].first += st[node].second;
            st[node*2+2].second += st[node].second;
            st[node].second = 0ll;
        }
    }
    void update(int node,int ul,int ur,int cl,int cr,ll diff) {
        push_down(node);
        if(ul <= cl && ur >= cr) {
            st[node].first += diff;
            st[node].second += diff;
            push_down(node);
        }
        else if(!(ul > cr || ur < cl)) {
            update(node*2+1,ul,ur,cl,cl+(cr-cl)/2,diff);
            update(node*2+2,ul,ur,cl+(cr-cl+2)/2,cr,diff);
        }
        push_down(node);
        if(cl!=cr) st[node].first = min(st[node*2+1].first, st[node*2+2].first);
    }
    ll query(int node,int ul,int ur,int cl,int cr) {
        push_down(node);
        if(ul <= cl && ur >= cr) return st[node].first;
        else if(!(ul > cr || ur < cl)) return min(query(node*2+1,ul,ur,cl,cl+(cr-cl)/2), query(node*2+2,ul,ur,cl+(cr-cl+2)/2,cr));
        return INT_MAX;
    }
    void update(int l, int r,ll diff) {update(0,l,r,0,N-1,diff);}
    ll query(int l,int r) {return query(0,l,r,0,N-1);}
};

void update_bracket(string& s, set<int>& open, set<int>& close, int idx, bool append) {
    if(idx > 0) {
        if(s[idx-1] == '(' && s[idx] == '(') {
            if(append) open.insert(idx-1);
            else open.erase(idx-1);
        }
        if(s[idx-1] == ')' && s[idx] == ')') {
            if(append) close.insert(idx-1);
            else close.erase(idx-1);
        }
    }
    if(idx + 1 < s.size()) {
        if(s[idx] == '(' && s[idx+1] == '(') {
            if(append) open.insert(idx);
            else open.erase(idx);
        }
        if(s[idx] == ')' && s[idx+1] == ')') {
            if(append) close.insert(idx);
            else close.erase(idx);
        }
    }
}

string update_char(lazy_segtree& segtree, string& s, int& counter, int N, set<int>& open, set<int>& close, int idx) {
    update_bracket(s,open,close,idx,false);
    update_bracket(s,open,close,idx,false);
    segtree.update(idx,N-1,s[idx]=='('?-2:2);
    counter += (s[idx] == '(' ? -2 : 2);
    s[idx] = (s[idx] == '(' ? ')' : '(');
    update_bracket(s,open,close,idx,true);
    if(abs(counter)%2 != 0) return "NO";

    int min_val = segtree.query(0,N-1);
    int to_inc = 0;
    if(min_val < 0) to_inc = ((abs(min_val)+1)/2)*2;

    if(min_val < 0 && (open.size() == 0 || segtree.query(0,*open.begin()) < 0)) {
        return "NO";
    }
    if(segtree.query(N-1,N-1) + to_inc == 0) return "YES";
    if(close.size() == 0 || segtree.query(*close.rbegin(),N-1) < segtree.query(N-1,N-1)) {
        return "NO";
    }
    return "YES";
}

int main() {
    fastio;
    int N; int Q; cin>>N>>Q;
    string s; cin>>s;
    vi qs(Q); for(int i=0;i<Q;i++) {int a;cin>>a;qs[i]=a-1;}
    lazy_segtree segtree(N);
    set<int> open;
    set<int> close;
    int counter = 0;
    for(int i=0;i<N;i++) {
        counter += (s[i] == '('?1:-1);
        segtree.update(i,N-1,(s[i]=='('?1:-1));
        update_bracket(s,open,close,i,true);
    }
    for(int q: qs) cout<<update_char(segtree,s,counter,s.size(),open,close,q)<<endl;
}

