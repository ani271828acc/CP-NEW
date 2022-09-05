#include<bits/stdc++.h>
using namespace std;
using ll=long long;

class dsu{
private:
    int n;
    vector<int> sz,pr;
public:
    dsu(int _n) {
        n=_n;
        sz=pr=vector<int>(n,1);
        for(int i=0;i<n;i++) pr[i]=i;
    }
    int find(int u) {
        return pr[u]==u?u:pr[u]=find(pr[u]);
    }
    bool join(int u,int v) {
        u=find(u),v=find(v);
        if(u==v) return 0;
        if(sz[u]<sz[v]) swap(u,v);
        sz[u]+=sz[v]; pr[v]=u;
        return 1;
    }
};
 
int main() {
    ll n,m;
    cin>>n>>m;
    dsu d(n);
    while(m--){
        ll a,b;
        cin>>a>>b;
        d.join(--a,--b);
    }
    ll q;
    cin>>q;
    while(q--){
        ll a,b;
        cin>>a>>b;
        if(d.find(--a)==d.find(--b))
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
}
