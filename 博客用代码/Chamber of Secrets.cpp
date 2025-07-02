#include<bits/stdc++.h>

using namespace std;
const int N = 1e3+10;
int n,m;
struct node{
	int x,y,step;
	bool to;
};
deque<node> que;
int dis[N][N],mp[N][N];
int bfs(){
	que.push_back({1,1,0,1});
	while(!que.empty()){
		node u=que.front();que.pop_front();
		if(u.x==m+1 && u.y==n){
			return u.step;
		}
		if(u.x<=0 || u.x>m || u.y<=0 || u.y>n) continue;//越界
		if(dis[u.x][u.y]==3) continue;//横竖都已经经过了
		if(dis[u.x][u.y]-1==u.to) continue;//已经被横/竖经过了
		if(dis[u.x][u.y]!=u.to && dis[u.x][u.y]){
			dis[u.x][u.y]=3;
		}else{
			dis[u.x][u.y]=u.to+1;
		}
		node v=u;
		v.x=u.x+(u.to?1:0);
		v.y=u.y+(u.to?0:1);
		que.push_front(v);
		v.x=u.x+(u.to?-1:0);
		v.y=u.y+(u.to?0:-1);
		que.push_front(v);
		if(mp[u.x][u.y]==1){
			v.step=u.step+1;
			v.to=!v.to;
			v.x=u.x+(u.to?0:1);
			v.y=u.y+(u.to?1:0);
			que.push_back(v);
			v.x=u.x+(u.to?0:-1);
			v.y=u.y+(u.to?-1:0);
			que.push_back(v);
		}
	}
	return -1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch;cin>>ch;
			if(ch=='#'){
				mp[j][i]=1;
			}
		}
	}
	cout << bfs();
	return 0;
}
