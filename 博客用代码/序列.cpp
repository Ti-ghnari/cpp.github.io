#include<bits/stdc++.h>
#define N 300010
#define ll long long
using namespace std;
template<typename T>
inline void read(T &x){
	bool f=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	if(f) x=~x+1;
}
template<typename T,typename...Args>
void read(T &x,Args &...args){read(x);read(args...);}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,q,B,tot;
int bel[N],L[N],R[N];
struct Num{
	int id;
	ll val;
	bool operator < (const Num &a)const{
		return val==a.val ? id<a.id : val<a.val;
	}
}a[N];
struct node{
	int op,id,x;
};
vector<node> vec[N];
int ans[N];ll tag[N];
void init(){
	tot=(q-1)/B+1;
	for(int i=1;i<=q;i++){
		a[i]={i,0};
		bel[i]=(i-1)/B+1;
	}
	for(int i=1;i<=tot;i++){
		L[i]=B*(i-1)+1;
		R[i]=min(B*i,q);
	}
}
void modify(int x,int k){
	for(int i=L[bel[x]];i<=R[bel[x]];i++)
		if(a[i].id>=x)
			a[i].val+=k;
	sort(a+L[bel[x]],a+R[bel[x]]+1);
	for(int i=bel[x]+1;i<=tot;i++) tag[i]+=k;
}
int query(int x,int k){
	int res=0;
	for(int i=L[bel[x]];i<=R[bel[x]];i++)
		if(a[i].id<=x && a[i].val+tag[bel[x]]>=k)
			res++;
	for(int i=1;i<bel[x];i++){
		res+=R[i]-(lower_bound(a+L[i],a+R[i]+1,Num({0,k-tag[i]}))-a)+1;
	}
	return res;
}
int main(){
	memset(ans,-1,sizeof(ans));
	read(n,q);q++;
	B=pow(q,0.5); 
	for(int i=1,x;i<=n;i++){
		read(x);
		vec[i].push_back({1,1,x});
		vec[i+1].push_back({1,1,-x});
	}
	for(int i=2,op,l,r,x,p,y;i<=q;i++){
		read(op);
		if(op==1){
			read(l,r,x);
			vec[l].push_back({1,i,x});
			vec[r+1].push_back({1,i,-x});
		}else{
			read(p,y);
			vec[p].push_back({2,i,y});
		}
	}
	init();
	for(int i=1;i<=n;i++){
		for(node tmp:vec[i]){
			if(tmp.op==1){
				modify(tmp.id,tmp.x);
			}else{
				ans[tmp.id]=query(tmp.id-1,tmp.x);
			}
		}
	}
	for(int i=2;i<=q;i++){
		if(ans[i]==-1) continue;
		write(ans[i]);puts("");
	}
	return 0;
}
