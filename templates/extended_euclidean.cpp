#include<bits/stdc++.h>
using namespace std;
using ll=long long;

/*
	ref: 
	https://cp-algorithms.com/algebra/linear-diophantine-equation.html
	https://youtu.be/IwRtISxAHY4
*/

ll extended_euclidean(ll a,ll b,ll &xa,ll &ya,ll &xb,ll &yb) {
	if(!b) return a;
	ll _xa=xb,_ya=yb,_xb=xa-(a/b)*xb,_yb=ya-(a/b)*yb;
	xa=_xa,ya=_ya,xb=_xb,yb=_yb;
	return extended_euclidean(b,a%b,xa,ya,xb,yb);
}
 
pair<ll,ll> linear_diophantine(ll a,ll b,ll c) {
	/*
		gives one sol to aX + bY = C
		say X0, Y0 satisfies aX + bY = C
		X0 + b/g, Y0 - a/g also satisfies

		general solution:
		X0 + T*(b/g), Y0 - T*(a/g)
	*/
	ll xa=1,ya=0,xb=0,yb=1;
	ll g=extended_euclidean(a,b,xa,ya,xb,yb);
    assert(g!=0 && !(c%g));
	return {xa*(c/g), ya*(c/g)};
}

int main() {
    ll a,b,c;
    cin>>a>>b>>c;
    auto res = linear_diophantine(a,b,c);
    ll X0=res.first, Y0=res.second;
    cout<<X0<<" "<<Y0<<"\n";
    assert(a*X0+b*Y0-c==0);
}