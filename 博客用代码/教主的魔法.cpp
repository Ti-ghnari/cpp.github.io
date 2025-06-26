#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1e6+50;
int n,m;
int a[N],tag[N],rnk[N];
int L[N],R[N],len,tot;
int belong[N];
void segsort(int k){
	for(int i=L[k];i<=R[k];i++){
		rnk[i]=a[i];
	}
	sort(rnk+L[k],rnk+R[k]+1);
}
void modify(int l,int r,int w){
	int x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++){
			a[i]+=w;
		}	
		segsort(x);
		return ;
	}
	for(int i=l;i<=R[x];i++){
		a[i]+=w;
	}
	segsort(x);
	for(int i=L[y];i<=r;i++){
		a[i]+=w;
	}
	segsort(y);
	for(int i=x+1;i<y;i++){
		tag[i]+=w;
	}
	return ;
}
int query(int l,int r,int c){
	int ans=0,x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++){
			if(a[i]+tag[x]>=c) ans++;
		}
		return ans;
	}
	for(int i=l;i<=R[x];i++){
		if(a[i]+tag[x]>=c) ans++;
	}
	for(int i=L[y];i<=r;i++){
		if(a[i]+tag[y]>=c) ans++;
	}
	for(int i=x+1;i<y;i++){
		ans+=R[i]-(lower_bound(rnk+L[i],rnk+R[i]+1,c-tag[i])-rnk)+1;
	}
	return ans;
}
void build(){
	len=sqrt(n);
	tot=n/len;
	if(n%len) tot++;
	for(int i=1;i<=n;i++){
		belong[i]=(i-1)/len+1;
	}
	for(int i=1;i<=tot;i++){
		L[i]=(i-1)*len+1;
		R[i]=min(i*len,n);
		sort(rnk+L[i],rnk+R[i]+1);
	}
	return ;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		rnk[i]=a[i];
	}
	build();
	for(int i=1;i<=m;i++){
		char op;
		int l,r,c;
		cin>>op>>l>>r>>c;
		if(op=='A'){
			cout<<query(l,r,c)<<'\n';
		}else{
			modify(l,r,c);
		}
	}
	return 0;
}
