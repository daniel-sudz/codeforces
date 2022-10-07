//https://leetcode.com/problems/critical-connections-in-a-network/
class Solution {
public:
    struct HASH{
  size_t operator()(pair<int,int>x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
    };
    void dfs(int node, int parent, vector<vector<int>>& G, vector<bool>& vis, vector<int>& order, unordered_set<pair<int,int>,HASH>& backedges, int& time) {
        vis[node]=true;
        order[node]=time;
        time++;
        for(int n: G[node]) {
            if(vis[n] ) {
                if(parent != n) {
                    backedges.insert(make_pair(min(n,node),max(n,node)));
                }
            }
            else dfs(n,node,G,vis,order,backedges,time);
        }
    }
    int calcMinBE(int node, vector<vector<int>>& G, vector<int>& minBE, vector<int>& order, unordered_set<pair<int,int>,HASH>& backedges) {
        if(minBE[node]!=-1) return minBE[node];
        minBE[node]=order[node];
        for(int n: G[node]) {
            if(order[n]>order[node] && order[n]!=order[node]-1) minBE[node]=min(minBE[node],calcMinBE(n,G,minBE,order,backedges));
            else if (backedges.count({min(node,n),max(node,n)})) minBE[node]=min(minBE[node],order[n]);
        }
        return minBE[node];
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        int time=0;
        vector<int> order(n,-1);
        vector<int> minBE(n,-1);
        vector<bool> vis(n);
        unordered_set<pair<int,int>,HASH> backedges;
        vector<vector<int>> G(n); 
        for(auto e: connections) {
                G[e[0]].push_back(e[1]);
                G[e[1]].push_back(e[0]);
        }

        dfs(0,-1,G,vis,order,backedges,time);
        calcMinBE(0,G,minBE,order,backedges);

        vector<vector<int>> ret;
        for(int i=0;i<n;i++) {
            for(int n: G[i]) {
                if(minBE[n]==order[n] && order[n]>order[i]) {
                    ret.push_back({min(i,n),max(i,n)});
                }
            }
        }
        return ret;
    }
};
