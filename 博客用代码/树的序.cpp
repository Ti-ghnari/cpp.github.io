#include<bits/stdc++.h>

using namespace std;
const int N = 1e5+10;
int n,a[N],ls[N],rs[N],vis[N];
stack<int> sta;
void dfs(int x){
	cout << x << ' ';
	if(ls[x]) dfs(ls[x]);
	if(rs[x]) dfs(rs[x]);
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x;a[x]=i;
	}
	for(int i=1;i<=n;i++){
		int f=0;
		while(!sta.empty() && a[sta.top()]>a[i]) f=sta.top(),sta.pop();
		if(!sta.empty()) rs[sta.top()]=i;
		if(f) ls[i]=f;
		sta.push(i);
	}
	for(int i=1;i<=n;i++){
		vis[ls[i]]=1,vis[rs[i]]=1;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i);break;
		}
	}
	return 0;
}
