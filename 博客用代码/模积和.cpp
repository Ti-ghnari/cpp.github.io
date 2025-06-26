#include<iostream>
#define int long long
using namespace std;
const int p=19940417,inv2=9970209,inv6=3323403;
int n,m;
int q1(int i){
	return i*(i+1)%p*inv2%p;
}
int q2(int i){
	return i*(i+1)%p*(2*i+1)%p*inv6%p;
}
signed main(){
	cin>>n>>m;
	if(n<m) n^=m^=n^=m;
	int tmp1=n*n%p;
	int l=1,r;
	while(l<=n){
		r=n/(n/l);
		tmp1=(tmp1-(q1(r)-q1(l-1)+p)%p*(n/l)%p+p)%p;
		l=r+1;
	}
	int tmp2=m*m%p;
	l=1,r=0;
	while(l<=m){
		r=m/(m/l);
		tmp2=(tmp2-(q1(r)-q1(l-1)+p)%p*(m/l)%p+p)%p;
		l=r+1;
	}
	int tmp3=0;
	l=1,r=0;
	while(l<=m){
		int tmp4=0,tmp5=0,tmp6=0;
		r=min(n/(n/l),m/(m/l));
		tmp4=(r-l+1)*n%p*m%p;
		tmp5=((q1(r)-q1(l-1)+p)%p*((m*(n/l)%p+p)%p+(n*(m/l)%p+p)%p))%p;
		tmp6=((q2(r)-q2(l-1)+p)%p*(n/l)%p*(m/l)%p+p)%p;
		tmp3=(tmp3+tmp4-tmp5+tmp6+p)%p;
		l=r+1;
	}
	cout<<(tmp1*tmp2%p-tmp3%p+p)%p;
	return 0;
}
