#include<bits/stdc++.h>
#define N 200010
using namespace std;
int n,idx[N];
string t[N],s;
struct ACauto{
	struct node{
		int son[30];
		int in,ans,fail,idx;
		void init(){
			memset(son,0,sizeof(son));
			ans=fail=idx=0;
		}
	}tr[N];
	int tot=0,ans[N],cnt;
	void init(){
		tot=cnt=0;
		tr[0].init();
	}
	void insert(string s,int &idx){
		int u=0;
		for(char ch:s){
			int &son=tr[u].son[ch-'a'];
			if(!son) son=++tot,tr[son].init();
			u=son;
		}
		if(!tr[u].idx) tr[u].idx=++cnt;
		idx=tr[u].idx;
	}
	void build(){
		queue<int> que;
		for(int i=0;i<26;i++){
			if(tr[0].son[i]) que.push(tr[0].son[i]);
		}
		while(!que.empty()){
			int u=que.front();
			que.pop();
			for(int i=0;i<26;i++){
				if(tr[u].son[i]){
					tr[tr[u].son[i]].fail=tr[tr[u].fail].son[i];
					tr[tr[tr[u].fail].son[i]].in++;
					que.push(tr[u].son[i]);
				}else{
					tr[u].son[i]=tr[tr[u].fail].son[i];
				}
			}
		}
	}
	void query(string t){
		int u=0;
		for(char ch:t){
			u=tr[u].son[ch-'a'];
			tr[u].ans++;
		}
	}
	void topo(){
		queue<int> que;
		for(int i=0;i<=tot;i++){
			if(tr[i].in==0) que.push(i);
		}
		while(!que.empty()){
			int u=que.front();
			que.pop();
			ans[tr[u].idx]=tr[u].ans;
			int v=tr[u].fail;
			tr[v].ans+=tr[u].ans;
			if(!(--tr[v].in)) que.push(v);
		}
	}
}AC;
int main(){
	AC.init();
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i];
		AC.insert(t[i],idx[i]);
		AC.ans[i]=0;
	}
	AC.build();
	cin>>s;
	AC.query(s);
	AC.topo();
	for(int i=1;i<=n;i++){
		cout << AC.ans[idx[i]] << '\n';
	}
	return 0;
}
