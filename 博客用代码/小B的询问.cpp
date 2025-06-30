#include<bits/stdc++.h>
#define N 50010
#define ll long long
#define B 250
using namespace std;
int n,m,k,a[N];
ll ans[N],res;
struct Q{
	int l,r,id;
	bool operator < (const Q &a)const{
		return (l/B==a.l/B) ? (l/B)&1 ? r<a.r : r>a.r : l<a.l; 
	}
}q[N];
int cnt[N];
void add(int x){
	res-=cnt[a[x]]*cnt[a[x]];
	++cnt[a[x]];
	res+=cnt[a[x]]*cnt[a[x]];
}
void del(int x){
	res-=cnt[a[x]]*cnt[a[x]];
	--cnt[a[x]];
	res+=cnt[a[x]]*cnt[a[x]];
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);	
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
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
		ans[q[i].id]=res;
	}
	for(int i=1;i<=m;i++){
		cout << ans[i]-1 << '\n';
	}
	return 0;
}
