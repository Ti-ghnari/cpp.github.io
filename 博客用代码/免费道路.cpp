#include<bits/stdc++.h>

using namespace std;
const int N = 2e4+10;
int n,m,k,fa[N];
int find(int x){return x==fa[x] ? x : fa[x]=find(fa[x]);}
struct Edge{
	int u,v,w;
}e[N<<3],ans[N<<3];
int tot,cnt,sum;
bool cmp1(Edge a,Edge b){
	return a.w>b.w;
}
bool cmp2(Edge a,Edge b){
	return a.w<b.w;
}
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v>>e[i].w;
	}
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	sort(e+1,e+1+m,cmp1);
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v;
		int fu=find(u),fv=find(v);
		if(fu==fv) continue;
		fa[fv]=fu;sum++;
		if(e[i].w==0){
			e[i].w=-1;
			tot++;
		}
	}
	if(tot>k || sum!=n-1){
		cout << "no solution";return 0;
	}
	sort(e+1,e+1+m,cmp2);
	for(int i=1;i<=n;i++) fa[i]=i;
	sum=0,tot=0;
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v;
		int fu=find(u),fv=find(v);
		if(fu==fv) continue;
		if(e[i].w==1 || tot<k){
			fa[fv]=fu,ans[++cnt]=e[i];
			sum++;
			if(e[i].w<1){
				tot++,e[i].w=0;
			}
		}
	}
	if(tot<k || sum!=n-1){
		cout << "no solution";return 0;
	}
	for(int i=1;i<=cnt;i++){
		if(ans[i].w==-1) ans[i].w=0;
		cout<<ans[i].u<<' '<<ans[i].v<<' '<<ans[i].w<<'\n';
	}
	return 0;
}
