#include "bits/stdc++.h"
#define pb push_back
#define endl '\n'
#define mp make_pair
#define pb push_back
using namespace std;
#define ui unsigned int
# define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


//polyfill std::bit_width for SPOJ
ui bit_width(ui x) {
    int res = 1;
    while(x>>=1) res++;
    return res;
}

// arrange elements in bit_reverse order
// based on CLRS chpt. 17-1 O(N) 
// https://walkccc.me/CLRS/Chap17/Problems/17-1/

void bit_rev(vector<auto>& arr) {
    ui x = 0;
    ui rev = 0;
    for(int i=0; i<(int)arr.size()-1; i++) {
        if(i < rev) iter_swap(arr.begin() + x, arr.begin() + rev);
        ui m = x ^ (x+1);
        rev ^= (m << (bit_width(arr.size()-1) - bit_width(m)));
        x++;
    }
}


double pi = 3.141592653589793238462643383279;

template<typename T> void fft(vector<T>& arr, const bool inv = false) {
    while((arr.size()&(arr.size()-1))) arr.pb(T()); // align power of 2
    int N = arr.size(); 
    //vector<T> w(N);
    //for(int i=0;i<N;i++) w[i] = exp(T(0.0, (inv?-2.0:2.0)*pi*(double)i/(double)N)); 
    bit_rev(arr); 
    for(int s=1, m=2; m<=N; s++, m*=2) {
        complex<double> wn = exp(T(0.0, (inv?-2.0:2.0)*pi/(double)m)); 
        for(int k=0; k<N; k+=m) {
            complex<double> w = 1;
            for(int j=0;j<m/2;j++) {
                T t = w * arr[k + j + m/2]; 
                T u = arr[k + j]; 
                arr[k + j] = (u + t) / (inv?2.0:1.0);
                arr[k + j + m/2] = (u - t) / (inv?2.0:1.0);
                w *= wn;
            }
        }
    }
}

int main() {
    //fastio;
    int T;cin>>T;
    for(int tc=0;tc<T;tc++) {
        int N; cin>>N;
        vector<cd> p1(N+1); 
        vector<cd> p2(N+1); 
        for(int i=0;i<=N;i++) cin>>p1[i];
        for(int i=0;i<=N;i++) cin>>p2[i];
        reverse(p1.begin(),p1.end());
        reverse(p2.begin(),p2.end());
        int exp=1;
        while(exp < p1.size()+p2.size()) exp*=2;
        p1.resize(exp);
        p2.resize(exp);
        fft(p1);
        fft(p2);
        for(int i=0;i<p1.size();i++) p1[i] *= p2[i];
        fft(p1,true);
        while(p1.size() > 2*N+1) p1.pop_back(); 
        reverse(p1.begin(),p1.end());
        for(auto v: p1) cout<<(long long)round(v.real())<<" ";
        cout<<endl;
    }
}
