#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int M=1e6+10;
int n,m;
int a[N],tag[N],sum[N];
int len,tot,L[N],R[N],belong[N];
void build(){
	len=sqrt(n);
	tot=n/len;
	if(n%len) tot++;
	for(int i=1;i<=n;i++){
		belong[i]=(i-1)/len+1;
		sum[belong[i]]+=a[i];
	}
	for(int i=1;i<=tot;i++){
		L[i]=(i-1)*len+1;
		R[i]=min(i*len,n);
	}
	return ;
}
void modify(int l,int r,int w){
	int x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++){
			a[i]+=w;
			sum[x]+=w;
		}
		return ;
	}else{
		for(int i=l;i<=R[x];i++){
			a[i]+=w;
			sum[x]+=w;
		}
		for(int i=L[y];i<=r;i++){
			a[i]+=w;
			sum[y]+=w;
		}
		for(int i=x+1;i<y;i++){
			tag[i]+=w;
			sum[i]+=(R[i]-L[i]+1)*w;
		}
		return ;
	}
}
int query(int l,int r){
	int x=belong[l],y=belong[r];
	int ans=0;
	if(x==y){
		for(int i=l;i<=r;i++){
			ans+=a[i]+tag[x];
		}
		return ans;
	}else{
		for(int i=l;i<=R[x];i++){
			ans+=a[i]+tag[x];
		}
		for(int i=L[y];i<=r;i++){
			ans+=a[i]+tag[y];
		}
		for(int i=x+1;i<y;i++){
			ans+=sum[i];
		}
		return ans;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build();
	for(int i=1;i<=m;i++){
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1){
			int k;
			cin>>k;
			modify(l,r,k);
		}else{
			cout<<query(l,r)<<'\n';
		}
	}
	return 0;
}
