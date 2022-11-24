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
Iterative version of extended GCD algorithm 
Locates integer solutions to (x_k)*(A) + (y_k)*(B) = gcd(A,B) for given (A,B)
O(1) space, O(log(min(A,B))) time
https://cp-algorithms.com/algebra/extended-euclid-algorithm.html#implementation
https://www.baeldung.com/cs/extended-euclidean-algorithm

    (Step 1) Define the series a:
        a1 = A
        a2 = B
        a_k+2 = a_k - (q_k)*(a_k+1)
        Where q_k = floor(a_k/a_k+1)

    (Step 2) Define the series x, y: 
        x1 = 1
        x2 = 0
        x_k+2 = x_k - (q_k)*(x_k+1)

        y1 = 0
        y2 = 1
        y_k+2 = y_k - (q_k)*(y_k+1)

    (Step 3) Show in general that: a_k = (x_k)*(a_1) +(y_k)*(a_2)
        a_1 = (x_1)*(a_1) + (y_1)*(a_2) = (1)*(a_1) + (0)*(a_2) = a_1
        a_2 = (x_2)*(a_1) + (y_2)*(a_2) = (0)*(a_1) + (1)*(a_2) = a_2 

        From the definition of series a:
        a_k+2 = (a_k) - (q_k)*(a_k+1) 
        
        Substitute inductive assumption:
        a_k+2 = ((x_k)*(a_1) + (y_k)*(a_2)) - (q_k)*((x_k+1)(a_1) + (y_k+1)*(a_2))

        Combine a_1 and a_2:
        a_k+2 = (a_1)*(x_k - (q_k)*(x_k+1)) + (a_2)*(y_k - (q_k)*(q_k+1))

        Based on how we have defined the series x and y this simplifies: 
        a_k+2 = (x_k)*(a_1) + (y_k)*(a_2) 
        
        Which is what we wanted to prove 

    (Step 4) 
       Since the series a converges on gcd(A,B) for some a_n, 
       we know that (x_n, y_n) satisfy (x_k)*(A) + (y_k)*(B) = gcd(A,B) 
       which is what we wanted to find. 
*/
pair<int, pii>  egcd(int A, int B) {
    if(A == 0) return {B, {0, 1}};
    int a1 = A, a2 = B; 
    int x1 = 1, x2 = 0;
    int y1 = 0, y2 = 1;
    while(a2 != 0) {
        int q1 = a1/a2; 
        int a3 = a1 - q1*a2;
        int x3 = x1 - q1*x2;
        int y3 = y1 - q1*y2;
        a1 = a2; a2 = a3; 
        x1 = x2; x2 = x3; 
        y1 = y2; y2 = y3;
    }
    return {a1, {x1, y1}};
}

// verification https://informatics.msk.ru/mod/statements/view.php?chapterid=3299#1
int main() {
    fastio;
    int A; int B; int C; cin>>A>>B>>C;
    auto gcdres = egcd(A,B);
    if(gcdres.first == 0 && C == 0) cout<<"0 0 0"<<endl;
    else if(gcdres.first == 0 && C != 0) cout<<"Impossible"<<endl;
    else if(C%gcdres.first != 0) cout<<"Impossible"<<endl;
    else cout<<gcdres.first<<" "<<(C/gcdres.first)*gcdres.second.first<<" "<<(C/gcdres.first)*gcdres.second.second<<endl;
}
