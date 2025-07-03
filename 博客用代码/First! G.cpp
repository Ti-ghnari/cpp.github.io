#include<bits/stdc++.h>

using namespace std;
const int N=3e4+10;
int n,ans[N],cnt;
string s[N];
struct Trie{
	struct node{
		int son[26];
		int cnt;
	}tr[10*N];
	int tot,in[26],mp[26][26];
	void insert(const string &s){
		int u=0;
		for(char ch:s){
			int &son=tr[u].son[ch-'a'];
			if(!son) son=++tot;
			u=son;
		}
		tr[u].cnt+=1;
	}
	void topo(){
		queue<int> que;
		for(int i=0;i<26;i++){
			if(in[i]==0) que.push(i);
		}
		while(!que.empty()){
			int u=que.front();que.pop();
			for(int i=0;i<26;i++){
				if(mp[u][i]){
					in[i]--;
					if(!in[i]) que.push(i);
				}
			}
		}
	}
	bool check(const string &s){
		memset(in,0,sizeof(in));
		memset(mp,0,sizeof(mp));
		int u=0;
		for(char ch:s){
			if(tr[u].cnt) return 0;
			for(int i=0;i<26;i++){
				if(tr[u].son[i] && i!=ch-'a' && !mp[ch-'a'][i]){
					mp[ch-'a'][i]=1;
					in[i]++;
				}
			}
			u=tr[u].son[ch-'a'];
		}
		topo();
		for(int i=0;i<26;i++){
			if(in[i]) return 0;
		}
		return 1;
	}
	
}T;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		T.insert(s[i]);
	}
	for(int i=1;i<=n;i++){
		if(T.check(s[i])){
			ans[++cnt]=i;
		}
	}
	cout << cnt << '\n';
	for(int i=1;i<=cnt;i++){
		cout << s[ans[i]] << '\n';
	}
	return 0;
}
