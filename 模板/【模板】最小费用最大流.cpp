#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int N=5e3+10;
const int M=5e4+10;
const int inf=2e9;
int n,m,s,t,maxflow,mincost;
int dis[N],flow[N],pre[N],last[N];
bool vis[N];
struct node{
	int to,nxt,cost,cap;
}e[2*M];
int head[N],tot=1;
void add(int u,int v,int cap,int cost){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	e[tot].cost=cost;
	e[tot].cap=cap;
	head[u]=tot;
	e[++tot].to=u;
	e[tot].nxt=head[v];
	e[tot].cost=-cost;
	e[tot].cap=0;
	head[v]=tot;
}
bool SPFA(){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(flow,0x3f,sizeof(flow));
	queue<int> que;
	que.push(s);
	dis[s]=0;
	vis[s]=1;
	pre[t]=-1;
	while(!que.empty()){
		int u=que.front();
		que.pop();vis[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to,cap=e[i].cap,cost=e[i].cost;
			if(cap && dis[v]>dis[u]+cost){
				dis[v]=dis[u]+cost;
				pre[v]=u;
				last[v]=i;
				flow[v]=min(flow[u],cap);
				if(vis[v]) continue;
				vis[v]=1;
				que.push(v);
			}
		}
	}
	return pre[t]!=-1;
}
void MCMF(){
	//这里是 EK 
	while(SPFA()){
		mincost+=flow[t]*dis[t];
		maxflow+=flow[t];
		for(int now=t;now!=s;now=pre[now]){
			e[last[now]].cap-=flow[t];
			e[last[now]^1].cap+=flow[t];
		}
	}
	return ;
}
int main(){
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int u,v,cap,cost;
		cin>>u>>v>>cap>>cost;
		add(u,v,cap,cost);
	}
	MCMF();
	cout<<maxflow<<' '<<mincost;
	return 0;
}