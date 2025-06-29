#include<bits/stdc++.h>
#define N 100010
#define ll long long
#define B 1025
#define inf 100000
using namespace std;
int n,m,a[N],l,r;
struct Q{
	int l,r,a,b,id;
	bool operator < (const Q &a)const{
		return l/B==a.l/B ? (l/B&1) ? r<a.r : r>a.r : l<a.l;
	}
}q[N];
int b[N],sum[500],cnt[500],L[N],R[N],bel[N],tot;
int ans1[N],ans2[N];
void init(){
	tot=(inf-1)/B+1;
	for(int i=1;i<=inf;i++){
		bel[i]=(i-1)/B+1;
	}
	for(int i=1;i<=tot;i++){
		L[i]=(i-1)*B+1;
		R[i]=min(i*B,inf);
	}
}
void modify(int x,int k){
	sum[bel[x]]-=b[x];
	cnt[bel[x]]-=(b[x]>0);
	b[x]+=k;
	sum[bel[x]]+=b[x];
	cnt[bel[x]]+=(b[x]>0);
}
int query1(int l,int r){
	int res=0;
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;i++){
			res+=b[i];
		}
		return res;
	}
	for(int i=l;i<=R[bel[l]];i++){
		res+=b[i];
	}
	for(int i=bel[l]+1;i<bel[r];i++){
		res+=sum[i];
	}
	for(int i=L[bel[r]];i<=r;i++){
		res+=b[i];
	}
	return res;
}
int query2(int l,int r){
	int res=0;
	if(bel[l]==bel[r]){
		for(int i=l;i<=r;i++){
			res+=(b[i]>0);
		}
		return res;
	}
	for(int i=l;i<=R[bel[l]];i++){
		res+=(b[i]>0);
	}
	for(int i=bel[l]+1;i<bel[r];i++){
		res+=cnt[i];
	}
	for(int i=L[bel[r]];i<=r;i++){
		res+=(b[i]>0);
	}
	return res;
}
void add(int x){
	modify(a[x],1);
}
void del(int x){
	modify(a[x],-1);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);	
	init();
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r>>q[i].a>>q[i].b;
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	for(int i=1;i<=m;i++){
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(l<q[i].l) del(l++);
		while(r>q[i].r) del(r--);
		ans1[q[i].id]=query1(q[i].a,q[i].b);
		ans2[q[i].id]=query2(q[i].a,q[i].b);
	}
	for(int i=1;i<=m;i++){
		cout<<ans1[i]<<' '<<ans2[i]<<'\n';
	}
	return 0;
}
