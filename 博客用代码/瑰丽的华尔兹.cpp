#include<bits/stdc++.h>

using namespace std;
const int N = 210;
int n,m,x,y,k;
int mp[N][N],f[N][N];
struct node{
	int val,pos;
}que[N];
int l,r,ans;
int dx[5]={0,-1,1,0,0},dy[5]={0,0,0,-1,1};
void solve(int x,int y,int len,int d){
	int l=1,r=0;
	for(int i=1;x>=1 && x<=n && y>=1 && y<=m;i++,x+=dx[d],y+=dy[d]){
		if(mp[x][y]) l=1,r=0;
		else{
			while(l<=r && que[r].val+i-que[r].pos<f[x][y]) r--;
			que[++r]={f[x][y],i};
			while(que[r].pos-que[l].pos>len) l++;
			f[x][y]=que[l].val+i-que[l].pos;
			ans=max(ans,f[x][y]);
		}
	}
}
int main(){
	cin>>n>>m>>x>>y>>k;
	memset(f,128,sizeof(f));
	f[x][y]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;cin>>ch;
			if(ch=='x'){
				mp[i][j]=1;
			}
		}
	}
	for(int i=1,l,r,d;i<=k;i++){
		cin>>l>>r>>d;
		int len=r-l+1;
		if(d==1) for(int j=1;j<=m;j++) solve(n,j,len,d);
		if(d==2) for(int j=1;j<=m;j++) solve(1,j,len,d);
		if(d==3) for(int j=1;j<=n;j++) solve(j,m,len,d);
		if(d==4) for(int j=1;j<=n;j++) solve(j,1,len,d);
	}
	cout << ans;
	return 0;
}
