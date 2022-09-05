#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;

void multisource_bfs() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> e(n);
    for(int i=0;i<m;i++) {
        int u,v,w;
        cin>>u>>v>>w;
        e[u-1].push_back(v-1);
    }

    auto bfs=[&](vector<int> from)->vector<int>{
        queue<int> q;
        vector<int> res(n,inf);
        for(auto node:from) {
            q.push(node);
            res[node]=0;
        }
        while(!q.empty()) {
            int cur=q.front(); q.pop();
            for(int node:e[cur]) {
                if(res[node]>res[cur]+1) {
                	res[node]=res[cur]+1;
                	q.push(node);
                }
            }
        }
        return res;
    };

    vector<int> dist=bfs({0});
    for(int i=0;i<n;i++)
    	cout<<dist[i]<<" ";
}

int main() {
    multisource_bfs();
}