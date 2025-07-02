#include<bits/stdc++.h>
#define ls u<<1
#define rs u<<1|1
using namespace std;
const int N=2e5+10;
int n,m,k;
struct Edge{
	int u,v;
}e[N<<1];
vector<int> vec[N];
vector<int> tr[N<<2];
void insert(int u,int l,int r,int x,int y,int k){
	if(l>=x && r<=y){
		tr[u].push_back(k);
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) insert(ls,l,mid,x,y,k);
	if(mid<y) insert(rs,mid+1,r,x,y,k);
}
int fa[N],siz[N];
int sta[N],top;
int find(int x){return fa[x]==x ? x : find(fa[x]);}
inline void merge(int x,int y){
	if(siz[x]>siz[y]) swap(x,y);
	fa[x]=y;
	siz[y]+=siz[x];
	sta[++top]=x;
}
inline void goback(int lst){
	while(top>lst){
		int y=sta[top--];
		siz[fa[y]]-=siz[y];
		fa[y]=y;
	}
}
void solve(int u,int l,int r,bool f){
	int lst=top;
	for(auto tim:tr[u]){
		int u=e[tim].u,v=e[tim].v;
		int fu=find(u),fv=find(v);
		if(fu==fv) continue;
		merge(fu,fv);
		if(siz[find(u)]==n){
			f=true;
		}
	}
	if(l==r){
		cout << (f==1 ? "Connected" : "Disconnected") << '\n';
	}else{
		int mid=(l+r)>>1;
		solve(ls,l,mid,f);
		solve(rs,mid+1,r,f);
	}
	goback(lst);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v;
	}
	for(int i=1;i<=m;i++){
		vec[i].push_back(0);
	}
	cin>>k;
	for(int i=1;i<=k;i++){
		int k;cin>>k;
		for(int j=1;j<=k;j++){
			int c;cin>>c;
			vec[c].push_back(i);
		}
	}
	for(int i=1;i<=m;i++){
		vec[i].push_back(k+1);
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<(int)vec[i].size();j++){
			if(vec[i][j-1]+1<=vec[i][j]-1){
				insert(1,1,k,vec[i][j-1]+1,vec[i][j]-1,i);
			}
		}
	}
	for(int i=1;i<=n;i++){
		fa[i]=i,siz[i]=1;
	}
	solve(1,1,k,0);
	return 0;
}
