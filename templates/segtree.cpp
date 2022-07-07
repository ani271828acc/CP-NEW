#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

template<typename T>
class segtree{
/*
    ref: https://youtu.be/2FShdqn-Oz8
    ref: https://cp-algorithms.com/data_structures/segment_tree.html
*/
private:
    int n; T basecase;
    T(* f)(T a,T b);
    vector<T> tree,ar;
    T build(int v,int tl,int tr) {
        if(tl==tr) 
            return tree[v]=ar[tl]; 
        int tm=(tl+tr)/2;
        return tree[v]=f(build(2*v,tl,tm),build(2*v+1,tm+1,tr));
    }
    T _get(int v,int tl,int tr,int ql,int qr) {
        if(tl>qr||tr<ql) 
            return basecase;
        if(tl>=ql&&tr<=qr) 
            return tree[v];
        int tm=(tl+tr)/2;
        return f(_get(2*v,tl,tm,ql,qr),_get(2*v+1,tm+1,tr,ql,qr));
    }   
    T _set(int v,int tl,int tr,int idx,T val) {
        if(tl>idx||tr<idx) 
            return tree[v];
        if(tl==tr) 
            return tree[v]=val;
        int tm=(tl+tr)/2;
        return tree[v]=f(_set(2*v,tl,tm,idx,val),_set(2*v+1,tm+1,tr,idx,val));
    }
public:
    // constructor:
    // examples: 
    // segtree<int> st(ar);
    // segtree<int> st(ar,-inf,[](int a,int b){return max(a,b);})
    segtree(vector<T>&_,T _basecase=0,T(*_f)(T a,T b)=[](T a,T b){
        return a+b;
    }) {
        // f should be an associative function
        // basecase and f are optional parameters
        // defaults to 0 and addition
        f=_f; ar=_; basecase=_basecase;
        n=ar.size(); tree=vector<T>(4*n,basecase);
        build(1,0,n-1);
    }
    // call st.get(left,right), 0 indexed
    T get(int ql,int qr) {
        return _get(1,0,n-1,ql,qr);
    }
    // call st.set(idx, newVal), 0 indexed
    void set(int idx,T val) {
        _set(1,0,n-1,idx,val);
    }
};

// brute force checker
template<typename T>
class bruteforce {
public:
    vector<T> ar;
    T basecase;
    T(* f)(T a,T b);
    int n;
    bruteforce(vector<T> _ar,T _basecase=0,T(* _f)(T a,T b)=[](T a,T b){
        return a+b;
    }) {
        n=_ar.size(); ar=_ar; basecase=_basecase; f=_f;
    }
    T get(int l,int r) {
        T res=0;
        for(int i=l;i<=r;i++) {
            res=f(res,ar[i]);
        }
        return res;
    }
    void set(int idx,T val) {
        ar[idx]=val;
    }
};

// supports speed and correctness test
class tester{
private:
    long long mxv=1e9+7;
public:
    tester(long long _mxv=1e9+7) {mxv=_mxv;}
    void test_correctness(int n,int q,long long bc=0,long long(*f)(long long a,long long b)=[](long long a,long long b){
        return a+b;
    }) {
        // CALL THIS WITH SMALL N AND Q
        // BECOS BRUTE FORCE
        mt19937 mt(rand()); 
        vector<long long> ar(n);
        for(int i=0;i<n;i++) {
            ar[i]=mt()%mxv;
        }

        segtree<long long> st(ar,0,f);
        bruteforce<long long> bt(ar,0,f);

        for(int i=0;i<q;i++) {
            int type=mt()%2;

            if(type) {
                int l=mt()%n,r=l+mt()%(n-l);
                int st_ans=st.get(l,r),bt_ans=bt.get(l,r);
                assert(st_ans==bt_ans);
                // cout<<"query is: left->"<<l<<", right-> "<<r<<"\n";
                // cout<<"bt: "<<bt_ans<<", st: "<<st_ans<<"\n\n";
            } else {
                int idx=mt()%n;long long val=mt()%mxv;
                st.set(idx,val);
                bt.set(idx,val);
                // cout<<"changed\n";
            }
        }
        cout<<"correct"<<endl;
    }

    void test_speed(int n,int q,long long(*f)(long long a,long long b)=[](long long a,long long b){
        return a+b;
    }) {
        // have large n,q
        mt19937 mt(rand()); 
        vector<long long> ar(n);
        for(int i=0;i<n;i++) {
            ar[i]=mt();
        }

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        segtree<long long> st(ar,0,f);

        while(q--) {
            int type=rand()%2;
            if(type) {
                int l=rand()%n,r=l+rand()%(n-l);
                long long res=st.get(l,r);
            } else {
                int idx=rand()%n; long long val=mt();
                st.set(idx,val);
            }
        }

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        cout<<"runtime: "<< (time_span.count()*1000)<<" ms"<<endl;
    }
};

int main() {
    srand(time(0));

    int n,q;
    cin>>n>>q;
    tester tc;
    tc.test_correctness(1000,10000);
    tc.test_speed(n,q,[](long long a,long long b){
        return __gcd(a,b);
    });
}