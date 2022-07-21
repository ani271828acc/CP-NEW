#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

class linear_sieve{
private:
	int prime_ct=0, is_computed=0, N=0;
	vector<int> least_prime,primes;
	void compute(int n) {
		prime_ct=0, is_computed=1, N=n;
		primes=least_prime=vector<int>(n+1);
		for(int i=2;i<n+1;i++) {
			if(!least_prime[i]) {
				least_prime[i]=i;
				primes[prime_ct++]=i;
			}
			for(int j=0;j<prime_ct&&primes[j]<=least_prime[i]&&primes[j]*i<n+1;j++) 
				least_prime[i*primes[j]]=primes[j];
		}	
	}
public:
	linear_sieve(int n=1e6) {
		compute(n);
	}

	void test_speed(int n) {
		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		compute(n);
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        cout<<"runtime: "<< (time_span.count()*1000)<<" ms"<<endl;
	}

	bool is_prime(int q) {
		return q<N+1?least_prime[q]==q:-1;
	}

	int kth_prime(int k) {
		return k<prime_ct?primes[k-1]:-1;
	}
};

int main() {
	linear_sieve ls(0);
	ls.test_speed(3e7);
	cout<<ls.is_prime(15651)<<"\n";
	cout<<ls.kth_prime(420)<<"\n";
}