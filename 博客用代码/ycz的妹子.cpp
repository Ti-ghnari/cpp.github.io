#include<bits/stdc++.h>
#define N 500010
#define ll long long
using namespace std;
int n,m,L[N],R[N],bel[N],cnt[750],tot,B;
ll a[N],arr[750];
int vis[N];
void init(){
	B=sqrt(N);
	tot=(N-11)/B+1;
	for(int i=1;i<=N-10;i++){
		bel[i]=(i-1)/B+1;
	}
	for(int i=1;i<=tot;i++){
		L[i]=R[i-1]+1;
		R[i]=min(L[i]+B-1,N-10);
	}
	for(int i=1;i<=tot;i++){
		for(int j=L[i];j<=R[i];j++){
			arr[i]+=a[j];
			cnt[i]+=vis[j];
		}
	}
}
void low(int x,int k){
	if(!vis[x]) return ;
	arr[bel[x]]-=a[x];
	a[x]-=k;
	arr[bel[x]]+=a[x];
}
void modify(int x,int k){
	if(!vis[x]) cnt[bel[x]]+=1,vis[x]=1;	
	arr[bel[x]]-=a[x];
	a[x]=k;
	arr[bel[x]]+=a[x];
}
void del(int x){
	for(int i=1;i<=tot;i++){
		if(x>cnt[i]) x-=cnt[i];
		else{
			for(int j=L[i];j<=R[i];j++){
				if(x-vis[j]==0){
					cnt[i]--;
					arr[i]-=a[j];
					a[j]=vis[j]=0;
					return;
				}else{
					x-=vis[j];
				}
			}
		}
	}
}
ll query(){
	ll res=0;
	for(int i=1;i<=tot;i++){
		res+=arr[i];
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		vis[i]=1;
	}
	init();
	for(int i=1,x,y;i<=m;i++){
		char op;cin>>op;
		if(op=='Q'){
			cout << query() << '\n';
		}else if(op=='C'){
			cin>>x>>y;
			low(x,y);
		}else if(op=='I'){
			cin>>x>>y;
			modify(x,y);
		}else{
			cin>>x;
			del(x);
		}
	}
	return 0;
}
