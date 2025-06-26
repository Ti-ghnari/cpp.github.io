#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
unordered_map<int,int> mp;
int mul(int a,int b,int p){
	int l=a*(b>>25ll)%p*(1ll<<25)%p;
	int r=a*(b&((1ll<<25)-1))%p;
	return (l+r)%p;
}
int qpow(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1) res=mul(res,a,p);
		a=mul(a,a,p);
		b>>=1;
	}
	return res;
}
int BSGS(int a,int b,int p){
	int len=ceil(sqrt(p));
	for(int i=0;i<len;i++) mp[mul(b,qpow(a,i,p),p)]=i;
	int tmp=qpow(a,len,p);
	for(int i=0;i<=len;i++){
		int x=qpow(tmp,i,p);
		int k=mp.count(x) ? mp[x] : -1;
		if(k>=0 && i*len-k>=0) return i*len-k;
	}
	return -1;
}
int n,m;
signed main(){
	cin>>n>>m;
	n=n*9+1;
	n%=m;
	cout<<BSGS(10,n,m);
	return 0;
}
