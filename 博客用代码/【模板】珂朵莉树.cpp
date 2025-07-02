#include<bits/stdc++.h>
#define int long long
#define p 1000000007
using namespace std;
const int N=1e5+10;
int n,m,seed,V,a[N];
int rnd(){
	int res=seed;
	seed=(seed*7+13)%p;
	return res;
}
struct node{
	int l,r;//相同元素段的起终点
	mutable int v;//元素值
	node(int l,int r=0,int v=0):l(l),r(r),v(v){}
	bool operator < (const node &a)const {
		return l < a.l;
	}
};
set<node> s;
auto split(int pos){
	auto it=s.lower_bound(node(pos));
	if(it!=s.end() && it->l==pos) return it;//如果恰好是 l
	it--;
	if(it->r < pos) return s.end();//如果是最后一块
	int l=it->l,r=it->r,v=it->v;
	s.erase(it);
	s.insert(node(l,pos-1,v));
	return s.insert(node(pos,r,v)).first;//insert的返回值是pair，第一位是迭代器
}
//先计算 itr,不然会神秘 RE
//抽出左右，然后暴力
void add(int l,int r,int x){
	auto itr=split(r+1),itl=split(l);
	for(auto it=itl;it!=itr;++it){
		it->v+=x;
	}
}
//删除左右，然后重建
void assign(int l,int r,int x){
	auto itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,x));
}
int qpow(int a,int b,int mod){
	int res=1;a%=mod;
	while(b){
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
int calc(int l,int r,int x,int y){
	auto itr=split(r+1),itl=split(l);
	int ans=0;
	for(auto it=itl;it!=itr;++it){
		ans=(ans+qpow(it->v,x,y) * (it->r-it->l+1)%y)%y;
	}
	return ans;
}
struct Num{
	int v,cnt;
	bool operator < (const Num &a)const{
		return v<a.v;
	}
};
//抽出所有元素，然后暴力
int rnk(int l,int r,int x){
	vector<Num> vec;
	auto itr=split(r+1),itl=split(l);
	for(auto it=itl;it!=itr;++it){
		vec.push_back({it->v,it->r-it->l+1});
	}
	sort(vec.begin(),vec.end());
	int id;
	for(id=0;id<(int)vec.size();id++){
		if(vec[id].cnt<x) x-=vec[id].cnt;
		else break;
	}
	return vec[id].v;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>seed>>V;
	for(int i=1;i<=n;i++){
		a[i]=(rnd()%V)+1;
		s.insert(node(i,i,a[i]));
	}
	for(int i=1,op,l,r,x,y;i<=m;i++){
		op=rnd()%4+1;
		l=rnd()%n+1,r=rnd()%n+1;
		if(l>r) swap(l,r);
		if(op==3){
			x=(rnd()%(r-l+1))+1;
		}else{
			x=(rnd()%V)+1;
		}
		if(op==4){
			y=rnd()%V+1;
		}
		if(op==1){
			add(l,r,x);
		}else if(op==2){
			assign(l,r,x);
		}else if(op==3){
			cout << rnk(l,r,x) << '\n';
		}else{
			cout << calc(l,r,x,y) << '\n';
		}
	}
	return 0;
}
