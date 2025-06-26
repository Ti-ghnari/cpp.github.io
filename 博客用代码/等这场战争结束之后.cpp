#include<iostream>
#include<vector>
#include<algorithm>
#define re register
using namespace std;
const int N=1e5+3;
const int len=3000;
int n,m,k;
int tot;
short sum[N][N/len+2];
int fa[N],siz[N];
int a[N],b[N],num[N],cnt[N],ans[N];
struct Edge{
	int to,nxt;
}e[N];
int head[N],hd;
void add(int u,int v){
	e[++hd].to=v;
	e[hd].nxt=head[u];
	head[u]=hd;
	return ;
}
struct question{
	int op,x,y;
}q[N];
int find(int x){return fa[x]==x ? x : find(fa[x]);}
inline void merge(int &fx,int &fy){
	if(fx==fy) return ;
	if(siz[fx]<=siz[fy]) swap(fx,fy);
	siz[fx]+=siz[fy];
	fa[fy]=fx;
	for(re int i=1;i<=tot;i++) sum[fx][i]+=sum[fy][i];
	return ;
}
void dfs(int u){
	int op=q[u].op,x=q[u].x,y=q[u].y;
	int fx=0,fy=0;
	if(op!=2) fx=find(x),fy=find(y);
	if(op==1){
		merge(fx,fy);
	}
	if(op==3){
		if(y>siz[fx]) ans[u]=-1;
		else{
			for(re int i=1;i<=tot;i++){
				if(y<=sum[fx][i]){
					for(re int j=(i-1)*len+1;j<=i*len;j++){
						if(find(num[j])==fx){
							y--;
							if(y==0){
								ans[u]=b[j];
								break;
							}
						}
					}
					break;
				}
				y-=sum[fx][i];
			}
		}
	}
	for(re int i=head[u];i;i=e[i].nxt) dfs(e[i].to);
	if(op==1 && fx!=fy){
		siz[fx]-=siz[fy];
		fa[fy]=fy;
		for(int i=1;i<=tot;i++) sum[fx][i]-=sum[fy][i];
	}
}
int main(){
	cin>>n>>m;
	tot=(n-1)/len+1;
	for(re int i=1;i<=n;i++){
		fa[i]=i;siz[i]=1;
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	for(re int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+1+n,a[i])-b;
		a[i]+=cnt[a[i]]++;
		num[a[i]]=i;
		sum[i][(a[i]-1)/len+1]=1;
	}
	for(re int i=1;i<=m;i++){
		cin>>q[i].op;
		if(q[i].op==1){
			cin>>q[i].x>>q[i].y;
		}else if(q[i].op==2){
			cin>>q[i].x;
			add(q[i].x,i);
			continue;
		}else if(q[i].op==3){
			cin>>q[i].x>>q[i].y;
		}
		add(i-1,i);
	}
	dfs(0);
	for(re int i=1;i<=m;i++){
		if(q[i].op==3){
			cout << ans[i] << '\n';
		}
	}
	return 0;
}
