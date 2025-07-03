#include<bits/stdc++.h>

using namespace std;
const int N=1e4+10;
struct node{
	int son[26];
	int cnt;
}tr[20*N];
bool vis[20*N];
int n,m,tot,ans,vx[N],len;
string s;
void insert(const string &s){
	int u=0;
	for(char ch:s){
		int &son=tr[u].son[ch-'a'];
		if(!son) son=++tot;
		u=son;
	}
	tr[u].cnt++;
}
bool flag=0;
void dfs(int u,int l,bool f){
	if(tr[u].cnt && l==len && !f){
		flag=1;return;
	}
	if(tr[u].cnt && l==len && f){
		if(!vis[u]){
			vx[++ans]=u;
			vis[u]=1;
		}
		return;
	}
	int ch=s[l]-'a';
	if(!f){
		if(l<len) dfs(u,l+1,1);
		for(int i=0;i<26;i++){
			if(tr[u].son[i]){
				dfs(tr[u].son[i],l,1);
				if(i!=ch) dfs(tr[u].son[i],l+1,1);
			}
		}
	}
	if(l>=len) return;
	if(tr[u].son[ch]) dfs(tr[u].son[ch],l+1,f);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s;
		insert(s);
	}
	for(int i=1;i<=m;i++){
		cin>>s;len=s.length();
		dfs(0,0,0);
		if(flag) cout << "-1\n";
		else cout << ans << '\n';
		while(ans) vis[vx[ans--]]=0;
		flag=0;
	}
	
	return 0;
}
