#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5e4+10;
int n,m,len;
int c[N];
ll sum;
int cnt[N];
ll ans1[N],ans2[N];
struct Query{
	int l,r,id;
}q[N];
bool cmp(Query a,Query b){
	if(a.l/len==b.l/len) return ((a.l/len)&1) ? a.r<b.r : a.r>b.r;
	return a.l<b.l;
}
void add(int u){
	sum+=cnt[u];
	cnt[u]++;
}
void del(int u){
	cnt[u]--;
	sum-=cnt[u];
}
int main(){
	cin>>n>>m;
	len=sqrt(n);
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].l>>q[i].r;
		q[i].id=i;
	}
	sort(q+1,q+1+m,cmp);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		if(q[i].l==q[i].r){
			ans1[q[i].id]=0;
			ans2[q[i].id]=1;
			continue;
		}
		while(l>q[i].l) add(c[--l]);
		while(r<q[i].r) add(c[++r]);
		while(l<q[i].l) del(c[l++]);
		while(r>q[i].r) del(c[r--]);
		ans1[q[i].id]=sum;
		ans2[q[i].id]=(ll)(r-l+1)*(r-l)/2;
	}
	for(int i=1;i<=m;i++){
		if(ans1[i]!=0){
			ll gcd=__gcd(ans1[i],ans2[i]);
			ans1[i]/=gcd,ans2[i]/=gcd;
		}else{
			ans2[i]=1;
		}
		cout << ans1[i]<<'/'<<ans2[i]<<'\n';
	}
	return 0;
}
