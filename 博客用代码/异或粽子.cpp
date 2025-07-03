#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5+10;
int n,m,rt[N],tot;
ll a[N],ans;
struct Trie{
	int son[2],sum,id;
}tr[40*N];
void insert(int &now,int pre,int t,int id,ll x){
	now=++tot;tr[now]=tr[pre];tr[now].sum++;
	if(t==-1){tr[now].id=id;return;}
	int i=(x>>t)&1;
	insert(tr[now].son[i],tr[pre].son[i],t-1,id,x);
}
int query(int l,int r,int t,ll x){
	if(t==-1) return tr[r].id;
	int i=(x>>t)&1;
	if(tr[tr[r].son[i^1]].sum>tr[tr[l].son[i^1]].sum) return query(tr[l].son[i^1],tr[r].son[i^1],t-1,x);
	else return query(tr[l].son[i],tr[r].son[i],t-1,x);
}
struct Num{
	int l,r,x,id;
	ll val;
	Num(int nl=0,int nr=0,int nx=0){
		l=nl;r=nr;x=nx;
		id=query(rt[l-1],rt[r],32,a[x]);
		val=a[x]^a[id-1];
	}
	bool operator < (const Num &a)const{
		return val<a.val;
	}
};
priority_queue<Num> que;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int b;cin>>b;
		a[i]=a[i-1]^b;
	}
	for(int i=1;i<=n;i++){
		rt[i]=rt[i-1];
		insert(rt[i],rt[i],32,i,a[i-1]);
	}
	for(int i=1;i<=n;i++){
		que.push(Num(1,i,i));
	}
	for(int i=1;i<=m;i++){
		Num u=que.top();que.pop();
		ans+=u.val;
		if(u.l<u.id) que.push(Num(u.l,u.id-1,u.x));
		if(u.id<u.r) que.push(Num(u.id+1,u.r,u.x));
	}
	cout << ans;
	return 0;
}
