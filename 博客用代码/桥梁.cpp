#include<bits/stdc++.h>
#define N 100010
using namespace std;
constexpr int B=1331;
int n,m,q;
struct Edge{
	int u,v,w,id;
	bool operator < (const Edge &a)const{
		return w>a.w;
	}
}e[N<<1];
struct node{
	int tim,id,w;
	bool operator < (const node &a)const{
		return w>a.w;
	}
};
vector<node> mdf,que;
int fa[N],siz[N],sta[N],top,vis[N],id[N],ans[N];
void init(){for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;}
int find(int x){return x==fa[x] ? x : find(fa[x]);}
void merge(int x,int y){
	int a=find(x),b=find(y);
	if(a==b) return ;
	if(siz[a]>siz[b]) fa[b]=a,siz[a]+=siz[b],sta[++top]=b;
	else fa[a]=b,siz[b]+=siz[a],sta[++top]=a;
}
void goback(int t){
	while(top>t){
		int y=sta[top--];
		siz[fa[y]]-=siz[y];
		fa[y]=y;
	}
}
void Solve(){
	sort(e+1,e+1+m);
	sort(que.begin(),que.end());
	for(int i=1;i<=m;i++) id[e[i].id]=i;
	vector<node> vec;vec.clear();
	for(node i:mdf){
		vis[i.id]=-1;
		vec.push_back({0,i.id,e[id[i.id]].w});
	}
	for(node i:mdf){
		vec.push_back(i);
	}
	init();
	top=0;
	for(int i=0,j=1;i<(int)que.size();i++){
		while(j<=m && e[j].w>=que[i].w){
			if(!vis[e[j].id]) merge(e[j].u,e[j].v);
			j++;
		}
		int lst=top;
		for(node a:vec){
			if(a.tim<=que[i].tim) vis[a.id]=a.w;
		}
		for(node a:mdf){
			if(vis[a.id]>=que[i].w) merge(e[id[a.id]].u,e[id[a.id]].v);
		}
		ans[que[i].tim]=siz[find(que[i].id)];
		goback(lst);
	}
	for(node i:mdf){
		e[id[i.id]].w=i.w;
		vis[i.id]=0;
	}
	mdf.clear();que.clear();
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
		e[i].id=i;
	}
	cin>>q;
	for(int i=1;i<=q;i++){
		int op,id,w;
		cin>>op>>id>>w;
		if(op==1) mdf.push_back({i,id,w});
		else que.push_back({i,id,w});
		if(i%B==0) Solve();
	}
	if(q%B) Solve();
	for(int i=1;i<=q;i++){
		if(ans[i]) 
			cout << ans[i] << '\n';
	}
	return 0;
}
