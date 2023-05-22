struct dsu {
    vi arr;
    dsu(int N) {
        arr.resize(N,-1);
    }
    int FIND(int a) {
        if(arr[a] == -1) return a;
        return arr[a] = FIND(arr[a]);  
    }
    void UNION(int a, int b) {
       if(rand() & 1) swap(a,b);
       if(FIND(a) != FIND(b)) arr[FIND(a)] = FIND(b);
    }
};
