#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#define int long long
using namespace std;
const int N=2e2+10;
const int M=5e3+10;
const int inf=2e17;
struct Edge{
	int u,v,cap,flow;
};
struct EK{
	int n,m;
	vector<Edge> e;
	vector<int> G[N];
	int a[N],p[N];
	void init(int n){
		for(int i=0;i<n;i++) G[i].clear();
		e.clear();
		return;
	}
	void add(int u,int v,int cap){
		e.push_back({u,v,cap,0});
		e.push_back({v,u,0,0});
		m=e.size();
		G[u].push_back(m-2);
		G[v].push_back(m-1);
		return ;
	}
	int maxflow(int s,int t){
		int res=0;
		while(1){
			memset(a,0,sizeof(a));
			queue<int> que;
			que.push(s);
			a[s]=inf;
			while(!que.empty()){
				int u=que.front();
				que.pop();
				for(auto i: G[u]){
					Edge edge=e[i];
					if(!a[edge.v] && edge.cap > edge.flow){
						p[edge.v]=i;
						a[edge.v]=min(a[u],edge.cap-edge.flow);
						que.push(edge.v);
					}
				}
				if(a[t]) break;
			}
			if(!a[t]) break;
			for(int x=t;x!=s;x=e[p[x]].u){
				e[p[x]].flow+=a[t];
				e[p[x]^1].flow-=a[t];
			}
			res+=a[t];
		}
		return res;
	}
}ek;
signed main(){
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	ek.n=n;
	for(int i=1;i<=m;i++){
		int u,v,cap;
		cin>>u>>v>>cap;
		ek.add(u,v,cap);
	}
	cout<<ek.maxflow(s,t);
	return 0;
}