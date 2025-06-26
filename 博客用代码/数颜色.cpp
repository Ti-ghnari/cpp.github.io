#include<bits/stdc++.h>
#define ll long long
#define N 233333
#define M 1000010
using namespace std;
struct Q{
	int x,y,t,id;
}qry[N],mdf[N];
int cntq,cntm;
int n,m,a[N],ans[N];
int len,cnt[M],sum;
bool cmp(Q a,Q b){
	return a.x/len==b.x/len ? a.y/len==b.y/len ? a.t<b.t : a.y < b.y : a.x<b.x;
}
inline void add(int x){
	sum+=!cnt[x]++;
}
inline void del(int x){
	sum-=!--cnt[x];
}
inline void upd(int x,int t){
	if(qry[x].x<=mdf[t].x && mdf[t].x <= qry[x].y){
		del(a[mdf[t].x]);
		add(mdf[t].y);
	}
	swap(a[mdf[t].x],mdf[t].y);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	len=pow(n,0.666);
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		char op;int x,y;
		cin>>op>>x>>y;
		if(op=='Q'){
			qry[++cntq]={x,y,cntm,cntq};
		}else{
			mdf[++cntm]={x,y,cntm,cntm};
		}
	}
	sort(qry+1,qry+1+cntq,cmp);
	int l=1,r=0,t=0;
	for(int i=1;i<=cntq;i++){
		while(l>qry[i].x) add(a[--l]);
		while(l<qry[i].x) del(a[l++]);
		while(r>qry[i].y) del(a[r--]);
		while(r<qry[i].y) add(a[++r]);
		while(t<qry[i].t) upd(i,++t);
		while(t>qry[i].t) upd(i,t--);
		ans[qry[i].id]=sum;
	}
	for(int i=1;i<=cntq;i++){
		cout << ans[i] << '\n';
	}
	return 0;
}
