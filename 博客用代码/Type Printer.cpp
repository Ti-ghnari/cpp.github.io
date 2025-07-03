#include<bits/stdc++.h>

using namespace std;
const int N = 5e4+10; 
int n,tot;
string s,mx;
struct node{
	int son[26];
	int cnt,id;
	bool vis;
}tr[N<<5];
void insert(const string &s,bool op){
	if(op==1){
		int u=0;
		for(char ch:s){
			u=tr[u].son[ch-'a'];
			tr[u].vis=1;
		}
		return ;
	}
	int u=0;
	for(char ch : s){
		int &son=tr[u].son[ch-'a'];
		if(!son) son=++tot;
		u=son;
	}
	tr[u].cnt++;
}
int dep[N<<5];
char ans[N];
int cnt;
bool f=false;
void dfs(int u){
	int v=-1;
	if(tr[u].cnt){
		for(int i=1;i<=tr[u].cnt;i++) ans[++cnt]='P';
	}
	for(int i=0;i<26;i++){
		if(tr[tr[u].son[i]].vis) v=i;
		else if(tr[u].son[i]){
			ans[++cnt]=i+'a';
			dfs(tr[u].son[i]);
		}
	}
	if(v!=-1){
		ans[++cnt]=v+'a';
		dfs(tr[u].son[v]);
	}
	if(v==-1 && tr[u].vis){
		f=true;
	}
	if(!f){
		ans[++cnt]='-';
	}
}
int main(){
	cin>>n;
	mx=1;
	for(int i=1;i<=n;i++){
		cin>>s;
		insert(s,0);
		if(s.length()>mx.length()){
			mx=s;
		}
	}
	insert(mx,1);
	dfs(0);
	cout << cnt << '\n';
	for(int i=1;i<=cnt;i++){
		cout << ans[i] << '\n';
	}
	return 0;
}
