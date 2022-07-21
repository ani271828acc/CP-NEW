#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// merge sort tree: data structure with support for
// queries of the type: find number of elements
// in the range [L, R] smaller than K

// todo:
// implement support for point updates
// using std::ordered_set instead of sorted vectors?

// todo:
// generalise: cmp function

// segtree like structure: 
// for ranges, store a sorted vector of elements
// space: logN*N
// built using merge sort process

template<typename T>
class merge_sort_tree{
private:
	int n; 
	vector<vector<T>> tree;
	vector<T> ar;
	void build(int v,int tl,int tr) {
		if(tl==tr) {
			tree[v]={ar[tl]}; return;
		}
		build(2*v,tl,(tl+tr)/2);
		build(2*v+1,(tl+tr)/2+1,tr);
		int ii=0,jj=0,kk=0,p=tree[2*v].size(),q=tree[2*v+1].size();
		tree[v]=vector<T>(p+q);
		while(kk<tree[v].size()) {
			if(ii==p)
				tree[v][kk++]=tree[2*v+1][jj++];
			else if(jj==q)
				tree[v][kk++]=tree[2*v][ii++];
			else if(tree[2*v][ii]<=tree[2*v+1][jj])
				tree[v][kk++]=tree[2*v][ii++];
			else tree[v][kk++]=tree[2*v+1][jj++];
		}
	}

	int _get(int v,int tl,int tr,int ql,int qr,T K) {
		if(tl>qr||tr<ql) 
			return 0;
		if(tl>=ql&&tr<=qr) 
			return lower_bound(tree[v].begin(),tree[v].end(),K)-tree[v].begin();
		return _get(2*v,tl,(tl+tr)/2,ql,qr,K)+_get(2*v+1,(tl+tr)/2+1,tr,ql,qr,K);
	}
public:
	merge_sort_tree(vector<T> _ar) {
		ar=_ar; n=ar.size();
		tree=vector<vector<T>>(4*n);
		build(1,0,n-1);
	}
	int get(int L,int R,T K) {
		return _get(1,0,n-1,L,R,K);
	}
};

template<typename T>
class bruteforce{
private:
	int n; vector<T> ar;
public:
	bruteforce(vector<T> _ar) {
		n=_ar.size(); ar=_ar;
	}
	int get(int l,int r,T k) {
		int res=0;
		for(int i=l;i<=r;i++) {
			res+=ar[i]<k;
		}
		return res;
	}
};

template<typename T>
class tester{
public:
	void correctness(int n) {
		vector<T> ar(n);
		for(int i=0;i<n;i++) {
			ar[i]=rand();
		}
		bruteforce<T> bt(ar);
		merge_sort_tree<T> st(ar);
		int q=100;
		while(q--) {
			int l=rand()%n;
			int r=l+rand()%(n-l);
			T k=rand();
			int got=st.get(l,r,k),exp=bt.get(l,r,k);
			assert(got==exp);
		}
		cout<<"correct"<<endl;
	}

	void speed(int n,int q) {
		vector<T> ar(n);
		for(int i=0;i<n;i++) {
			ar[i]=rand();
		}
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		merge_sort_tree<T> st(ar);
		while(q--) {
			int l=rand()%n;
			int r=l+rand()%(n-l);
			T k=rand();
			int got=st.get(l,r,k);
		}
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        cout<<"runtime: "<< (time_span.count()*1000)<<" ms"<<endl;
	}
};



int main() {
	srand(time(0));
	tester<int> test;
	for(int i=0;i<10;i++) {
		test.correctness(rand()%1000);
	}
	int n, q;
	cin>>n>>q;
	test.speed(n,q);
}