#include<bits/stdc++.h>
#define B 1025
using namespace std;
constexpr int N=1e6+10;
constexpr int M=5e5+10;
constexpr int V=1e5+10;
int n,m,a[N],tot,sum0[N],ans[M];
int mx,tag,fa[V],cnt[V];
struct Q{
	int op,l,r,x;
}q[M];
int find(int x){return fa[x]==x ? x : fa[x]=find(fa[x]);}
inline void init(const int &x){
	memset(cnt,0,sizeof(cnt));
	mx=0,tag=0;
	int l=(x-1)*B+1,r=min(x*B,n);
	for(int i=l;i<=r;i++){
//		if(a[i]==0) continue;
		mx=max(mx,a[i]);
		cnt[a[i]]++;
	}
	for(int i=0;i<=mx;i++){
		fa[i]=i;
	}
}
inline void merge(const int &x,const int &y){
	int fx=find(x),fy=find(y);
	if(fx==fy) return;
	fa[fx]=fy;
	cnt[fy]+=cnt[fx];
	cnt[fx]=0;
}
inline void mdf1(const int &x){
	if((x<<1)<mx-tag){
		for(int i=tag+1;i<=x+tag;i++){
			merge(i,i+x);
		}
		tag+=x;
	}else{
		for(int i=mx;i>tag+x;i--){
			merge(i,i-x);
		}
		while(!cnt[mx] && mx>0) mx--;
	}
}
inline void mdf2(const int &id,int l,int r,const int &x){
	int ll=(id-1)*B+1,rr=min(id*B,n);
	l=max(l,ll),r=min(rr,r);
	for(int i=ll;i<=rr;i++){
		while(fa[a[i]]!=a[i]){
			a[i]=fa[a[i]];
		}
	}
	for(int i=l;i<=r;i++){
		if(a[i]-tag>x){
			cnt[a[i]]--;
			a[i]-=x;
			cnt[a[i]]++;
		}
	}
	while(!cnt[mx] && mx>0) mx--;
}
inline int query(const int &id,int l,int r,const int &x){
	int res=0,ll=(id-1)*B+1,rr=min(id*B,n);
	l=max(ll,l),r=min(rr,r);
	for(int i=ll;i<=rr;i++){
		while(fa[a[i]]!=a[i]){
			a[i]=fa[a[i]];
		}
	}
	for(int i=l;i<=r;i++){
		if(a[i]==x+tag) res++;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	tot=(n-1)/B+1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum0[i]=sum0[i-1]+(a[i]==0);
	}
	for(int i=1;i<=m;i++){
		cin>>q[i].op>>q[i].l>>q[i].r>>q[i].x;
	}
	for(int i=1;i<=tot;i++){
		int nl=(i-1)*B+1,nr=min(i*B,n);
		init(i);
		for(int j=1;j<=m;j++){
			int op=q[j].op,l=q[j].l,r=q[j].r,x=q[j].x;
			if(x==0){
				if(op==2) ans[j]+=sum0[r]-sum0[l-1];
				continue;
			}
			if(nl>r || nr<l) continue;
			if(op==1){
				if(x>=mx-tag) continue;
				if(nl>=l && nr<=r) mdf1(x);
				else mdf2(i,l,r,x);
			}else{
				if(tag+x>mx) continue;
				if(nl>=l && nr<=r) ans[j]+=cnt[x+tag];
				else ans[j]+=query(i,l,r,x);
			}
		}
	}
	for(int i=1;i<=m;i++){
		if(q[i].op==2)
			cout << ans[i] << '\n';
	}
	return 0;
}
