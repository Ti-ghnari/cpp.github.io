#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+10;
const int M = 2e6+10;
int n,m,s;
struct node{
	int v,w;
};
struct Que{
	int u,v,x,y,w;
}que[M];
int cnt,lim,tot;
vector<node> G[N*20];
vector<int> tr[N];
int fa[50010],f[N][18],dep[50010];
int in[N][18],out[N][18];
int find(int x){return fa[x]==x ? x : fa[x]=find(fa[x]);}
void dfs(int u,int father){
	dep[u]=dep[father]+1;f[u][0]=father;
	in[u][0]=++tot;G[tot].push_back({u,0});G[tot].push_back({father,0});
	out[u][0]=++tot;G[u].push_back({tot,0});G[father].push_back({tot,0});
	for(int j=1;j<=lim;j++){
		f[u][j]=f[f[u][j-1]][j-1];
		in[u][j]=++tot;G[tot].push_back({in[u][j-1],0});G[tot].push_back({in[f[u][j-1]][j-1],0});
		out[u][j]=++tot;G[out[u][j-1]].push_back({tot,0});G[out[f[u][j-1]][j-1]].push_back({tot,0});
	}
	for(int v:tr[u]){
		if(v==father) continue;
		dfs(v,u);
	}
}
void lca1(int x,int y,int k){
	if(dep[x]<dep[y]) swap(x,y);
	G[y].push_back({k,0});
	for(int i=lim;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]){
			G[out[x][i]].push_back({k,0});
			x=f[x][i];
		}
	}
	if(x==y) return ;
	for(int i=lim;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			G[out[x][i]].push_back({k,0});x=f[x][i];
			G[out[y][i]].push_back({k,0});y=f[y][i];
		}
	}
	G[out[x][0]].push_back({k,0});
}
void lca2(int x,int y,int k){
	if(dep[x]<dep[y]) swap(x,y);
	G[k].push_back({y,0});
	for(int i=lim;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]){
			G[k].push_back({in[x][i],0});
			x=f[x][i];
		}
	}
	if(x==y) return ;
	for(int i=lim;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			G[k].push_back({in[x][i],0});x=f[x][i];
			G[k].push_back({in[y][i],0});y=f[y][i];
		}
	}
	G[k].push_back({in[x][0],0});
}
struct DIJ{
	int id,val;
	bool operator < (const DIJ &a)const{
		return val>a.val;
	}
};
int dis[N*20];
bool vis[N*20];
void dijsktra(){
	memset(dis,0x3f,sizeof(dis));
	priority_queue<DIJ> q;
	q.push({s,0});
	dis[s]=0;
	while(!q.empty()){
		auto u=q.top();q.pop();
		if(vis[u.id]) continue;
		vis[u.id]=1;
		for(auto to:G[u.id]){
			int v=to.v,w=to.w;
			if(dis[v]>dis[u.id]+w){
				dis[v]=dis[u.id]+w;
				q.push({v,dis[v]});
			}
		}
	}
	for(int i=1;i<=n;i++){
		cout << (dis[i]==0x3f3f3f3f ? -1 : dis[i]) << ' ';
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>s;
	while((1<<lim)<=n) ++lim;
	lim--;tot=n;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1,op,u,v,w;i<=m;i++){
		cin>>op>>u>>v;
		if(op==1){
			int x,y;
			cin>>x>>y>>w;
			if(find(x)!=find(y) || find(u)!=find(v)) continue;
			que[++cnt]={u,v,x,y,w};
		}else{
			cin>>w;
			int fu=find(u),fv=find(v);
			if(fu==fv) continue;
			tr[u].push_back(v);tr[v].push_back(u);
			G[u].push_back({v,w});
			G[v].push_back({u,w});
			fa[fu]=fv;
		}
	}
	for(int i=1;i<=n;i++){
		if(!dep[i]) dfs(i,0);
	}
	for(int i=1;i<=cnt;i++){
		lca1(que[i].u,que[i].v,++tot);
		lca2(que[i].x,que[i].y,++tot);
		G[tot-1].push_back({tot,que[i].w});
	}
	dijsktra();
	
	return 0;
}
