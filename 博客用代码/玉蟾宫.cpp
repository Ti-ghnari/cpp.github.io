#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e3+10;
int pos[N][N];
int n,m,ans;
struct node{
	int len,hei;
}sta[N];
void solve(int x){
	int top=0,len=0;
	for(int i=1;i<=m;i++){
		len=0;
		while(sta[top].hei>=pos[x][i] && top>0){
			len+=sta[top].len;
			ans=max(ans,sta[top--].hei*len);
		}
		sta[++top].hei=pos[x][i];
		sta[top].len=len+1;
	}
	len=0;
	while(top>0){
		len+=sta[top].len;
		ans=max(ans,sta[top--].hei*len);
	}
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;cin>>ch;
			if(ch=='R'){
				pos[i][j]=0;
			}else{
				pos[i][j]=pos[i-1][j]+1;
			}
		}
	}
	for(int i=1;i<=n;i++) solve(i);
	cout << 3*ans;
	return 0;
}
