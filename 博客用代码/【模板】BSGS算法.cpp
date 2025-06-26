#include<iostream>
#include<map>
#include<cmath>
#define int long long
using namespace std;
map<int,int> mp;
int qpow(int a,int b,int p){
	int ans=1;
	while(b>0){
		if(b&1) ans=(ans*a)%p;
		a=(a*a)%p;
		b>>=1;
	}
	return ans;
}
int BSGS(int a,int b,int p){
	if(a%p==b%p) return 1;
	if(a%p==0 && b!=0) return -1;
	int len=(long long)sqrt(p)+1;
	int tmp=qpow(a,len,p);
	for(int i=0;i<=len;i++){
		mp[b]=i;
		b=(b*a)%p;
	}
	b=1;
	for(int i=1;i<=len;i++){
		b=(b*tmp)%p;
		if(mp[b]) return i*len-mp[b];
	}
	return -1;
}
int p,a,b;
signed main(){
	cin>>p>>a>>b;
	int ans=BSGS(a,b,p);
	if(ans==-1) cout<<"no solution";
	else cout<<ans;
	return 0;
}
