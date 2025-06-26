#include<bits/stdc++.h>
#define lowbit(i) i&-i
using namespace std;
const int N=1e5+10;
const int K=2e5+10;
int n,k;
struct node{
	int a,b,c;
}p[N];
bool cmp(node a,node b){
	return a.a!=b.a ? a.a<b.a : (a.b!=b.b ? a.b<b.b : a.c<b.c);
}
struct Tree{
	int val;
	int ls,rs;
}tr[K<<5];
int tot,rt[K];
void pushup(int u){
	tr[u].val=tr[tr[u].ls].val+tr[tr[u].rs].val;
}
void modify(int &u,int l,int r,int x,int val){
	if(!u) u=++tot;
	if(l==r){
		tr[u].val+=val;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) modify(tr[u].ls,l,mid,x,val);
	else modify(tr[u].rs,mid+1,r,x,val);
	pushup(u);
}
int query(int u,int l,int r,int x,int y){
	if(!u) return 0;
	if(l>=x && r<=y){
		return tr[u].val;
	}
	int res=0;
	int mid=(l+r)>>1;
	if(x<=mid) res+=query(tr[u].ls,l,mid,x,y);
	if(mid<y) res+=query(tr[u].rs,mid+1,r,x,y);
	return res;
}
void update(int x,int y,int val){
	if(x==0) return ;
	for(int i=x;i<=k;i+=lowbit(i)){
		modify(rt[i],1,k,y,val);
	}
}
int qry(int x,int y){
	int res=0;
	for(int i=x;i;i-=lowbit(i)){
		res+=query(rt[i],1,k,1,y);
	}
	return res;
}
int Ans[K];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>p[i].a>>p[i].b>>p[i].c;
	}
	sort(p+1,p+1+n,cmp);
	int cnt=1;
	for(int i=1;i<=n;i++){
		if(p[i].a==p[i+1].a && p[i].b==p[i+1].b && p[i].c==p[i+1].c){
			cnt++;
			continue;
		}else{
			update(p[i].b,p[i].c,cnt);
			int ans=qry(p[i].b,p[i].c);
			Ans[ans]+=cnt;
			cnt=1;
		}
	}
	for(int i=1;i<=n;i++){
		cout << Ans[i] << '\n';
	}
	return 0;
}