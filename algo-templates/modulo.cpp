/* Fast exponent and Fermat's Little Theorem for modular inverse */
 
ll exp(ll base, ll exp, ll MOD) {
    vll nums = {base};
    while((1ll<<(ll)(nums.size()-1))<exp) {
        nums.pb(((nums.back())*nums.back())%MOD);
    }
    ll ans = 1ll; 
    while(exp > 0) {
        if(exp >= (1ll<<(ll)(nums.size()-1))) {
            exp -= (1ll<<(ll)(nums.size()-1));
            ans = (ans * nums.back()) % MOD;
        }
        nums.pop_back();
    }
    return ans;
}

ll divmod(ll num, ll denom, ll MOD) {
    return (((num%MOD)+MOD)%MOD * ((exp(denom, MOD-2, MOD)%MOD)+MOD)%MOD) % MOD;
}
