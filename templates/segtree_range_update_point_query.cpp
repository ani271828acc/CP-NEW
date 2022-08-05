#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
// segtree: range update point query
// for ranges store: count added to that range
// for queries, simply follow the path to the root

template<typename T>
class segtree{
private:
    int n; vector<T> tree,a; T bc; T(*f)(T a,T b);
    T build(int v,int tl,int tr) {
        return tl==tr?tree[v]=a[tl]:f(build(2*v,tl,(tl+tr)/2),build(2*v+1,(tl+tr)/2+1,tr));
    }
    T _get(int v,int tl,int tr,int idx) {
        if(idx<tl||idx>tr)
            return bc;
        if(tl==tr)
            return tree[v];
        return f(tree[v],f(_get(2*v,tl,(tl+tr)/2,idx),_get(2*v+1,(tl+tr)/2+1,tr,idx)));
    } 
    void _set(int v,int tl,int tr,int ql,int qr,T add) {
        if(tl>qr||tr<ql)
            return;
        if(ql<=tl&&qr>=tr) {
            tree[v]=f(tree[v],add);
            return;
        }
        _set(2*v,tl,(tl+tr)/2,ql,qr,add);
        _set(2*v+1,(tl+tr)/2+1,tr,ql,qr,add);
    }
public:
    segtree(vector<T> _,T _bc=0,T(*_f)(T x,T y)=[](T x,T y){return x+y;}) {
        a=_; n=a.size(); bc=_bc; f=_f; tree=vector<T>(4*n); build(1,0,n-1);
    }
    T get(int idx) {
        return _get(1,0,n-1,idx);
    }
    void set(int L,int R,T val) {
        if(R>=L) _set(1,0,n-1,L,R,val);
    }
};
 
int main() {
    int n,q;
    cin>>n>>q;
    vector<ll> a(n);
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    segtree<ll> st(a,0ll,[](ll p,ll q){
        return p+q;
    });
 
    while(q--) {
        int t;
        cin>>t;
        if(t==1) {
            int a,b,u;
            cin>>a>>b>>u;
            st.set(a-1,b-1,u);
        } else {
            int idx;
            cin>>idx;
            cout<<st.get(idx-1)<<"\n";
        }
    }
}