#include<bits/stdc++.h>
#define N 200010
#define ll long long
#define B 1025
#define inf 200001
using namespace std;
int n,m,a[N],ans[N];
struct Q{
	int l,r,id;
	bool operator < (const Q &a)const{
		return (l/B==a.l/B) ? (l/B&1) ? r<a.r : r>a.r : l<a.l;
	}
}q[N];
int b[N],sum[505],L[N],R[N],bel[N],tot;
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
	sum[bel[x]]-=(b[x]>0);
	b[x]+=k;
	sum[bel[x]]+=(b[x]>0);
}
int query(){
	for(int i=1;i<=tot;i++){
		if(sum[i]!=R[i]-L[i]+1){
			for(int j=L[i];j<=R[i];j++){
				if(b[j]==0){
					return j;
				}
			}
		}
	}
	return inf;
}
void add(int x){
	modify(a[x],1);
}
void del(int x){
	modify(a[x],-1);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);	
	cin>>n>>m;
	init();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=1;
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	int l=0,r=0;
	for(int i=1;i<=m;i++){
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(l<q[i].l) del(l++);
		while(r>q[i].r) del(r--);
		ans[q[i].id]=query()-1;
	}
	for(int i=1;i<=m;i++){
		cout << ans[i] << '\n';
	}
	return 0;
}
