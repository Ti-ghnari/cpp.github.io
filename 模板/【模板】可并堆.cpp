#include<bits/stdc++.h>

using namespace std;
const int N=1e5+10;
int n,m;
//dis是树高，rt是堆内的堆顶
int ls[N],rs[N],dis[N],rt[N];
//删除懒标记
bool f[N];
struct node{
	int id,v;
	bool operator <(const node &x)const{
		return v==x.v ? id <x.id : v<x.v;
	} 
}v[N];
int find(int x){return rt[x]==x ? x :rt[x]=find(rt[x]);}
int merge(int x,int y){
	if(!x || !y) return x|y;
	if(v[y]<v[x]) swap(x,y);
	rs[x]=merge(rs[x],y);
	if(dis[ls[x]]<dis[rs[x]]) swap(ls[x],rs[x]);
	dis[x]=dis[rs[x]]+1;
	return x;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	dis[0]=-1;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>v[i].v;
		rt[i]=i;
		v[i].id=i;
	}
	while(m--){
		int op,x,y;
		cin>>op>>x;
		if(op==1){
			cin>>y;
			if(f[x] || f[y]) continue;
			int fx=find(x),fy=find(y);
			if(fx!=fy) rt[fx]=rt[fy]=merge(fx,fy);
		}else{
			if(f[x]){cout << "-1\n";continue;}
			int fx=find(x);
			cout << v[fx].v << '\n';
			f[fx]=1;
			rt[ls[fx]]=rt[rs[fx]]=rt[fx]=merge(ls[fx],rs[fx]);
			ls[fx]=rs[fx]=dis[fx]=0;
		}
	}
	return 0;
}
