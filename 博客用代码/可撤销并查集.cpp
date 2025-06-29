#include<iostream>

using namespace std;
const int N=2e5+10;
int n,m;
int op[N],a[N],b[N],tim[N],ans[N];
struct Edge{
	int to,nxt;
}e[2*N];
int head[N],tot=1;
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	return ;
}
int fa[N],siz[N],sta[N],top;
void init(){
	for(int i=1;i<=n;i++){
		fa[i]=i,siz[i]=1;
	}
	return;
}
int find(int x){
	if(x==fa[x]) return x;
	return find(fa[x]);
}
void merge(int x,int y){
	int a=find(x),b=find(y);
	if(a==b) return ;
	if(siz[a]>siz[b]) fa[b]=a,siz[a]+=siz[b],sta[++top]=b;
	else fa[a]=b,siz[b]+=siz[a],sta[++top]=a;
	return ;
}
void goback(int t){
	while(top>t){
		int y=sta[top--];
		siz[fa[y]]-=siz[y];
		fa[y]=y;
	}
	return ;
}
void dfs(int u){
	tim[u]=top;	
	if(op[u]==1) merge(a[u],b[u]);
	if(op[u]==3) ans[u]=(find(a[u])==find(b[u]))?1:0;
	for(int i=head[u];i;i=e[i].nxt){
		dfs(e[i].to);
	}
	goback(tim[u]);
}
int main(){
	cin>>n>>m;
	init();
	for(int i=1;i<=m;i++){
		cin>>op[i]>>a[i];
		if(op[i]!=2) cin>>b[i],add(i-1,i);
		else add(a[i],i);
	}
	dfs(0);
	for(int i=1;i<=m;i++){
		if(op[i]==3) cout<<ans[i]<<'\n';
	}
	return 0;
}
