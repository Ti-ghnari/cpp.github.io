#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+10;
const int B = 333;
int n,m,k,a[N],arr[N];
struct Q{
	int l,r,id;
}que[N];
bool cmp(Q a,Q b){
	if(a.l/B==b.l/B) return (a.l/B)&1 ? a.r<b.r : a.r>b.r;
	return a.l<b.l;
}
int l,r,res,tot[N],ans[N];
void add(int x){
	res+=tot[arr[x]^k];tot[arr[x]]++;
}
void del(int x){
	tot[arr[x]]--;res-=tot[arr[x]^k];
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		arr[i]=arr[i-1]^a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>que[i].l>>que[i].r;
		que[i].id=i;
	}
	sort(que+1,que+1+m,cmp);
	tot[0]=1;
	for(int i=1;i<=m;i++){
		while(l>que[i].l-1) add(--l);
		while(r<que[i].r) add(++r);
		while(l<que[i].l-1) del(l++);
		while(r>que[i].r) del(r--);
		ans[que[i].id]=res;
	}
	for(int i=1;i<=m;i++){
		cout << ans[i] << '\n';
	}
	return 0;
}
