#include<bits/stdc++.h>

using namespace std;
const int N = 2e3+10;
int T,P,W;
int ap[N],bp[N],as[N],bs[N];
int f[N][N],ans,l,r,que[N];
int main(){
	cin>>T>>P>>W;
	for(int i=1;i<=T;i++){
		cin>>ap[i]>>bp[i]>>as[i]>>bs[i];
	}
	memset(f,128,sizeof(f));
	for(int i=1;i<=T;i++){
		for(int j=0;j<=as[i];j++){
			f[i][j]=-j*ap[i];
		}
		for(int j=0;j<=P;j++){
			f[i][j]=max(f[i][j],f[i-1][j]);
		}
		if(i-W-1<1) continue;
		l=1,r=0;
		for(int j=0;j<=P;j++){
			while(l<=r && que[l]<j-as[i]) l++;
			while(l<=r && f[i-W-1][que[r]]+que[r]*ap[i]<=f[i-W-1][j]+j*ap[i]) r--;
			que[++r]=j;
			if(l<=r)
				f[i][j]=max(f[i][j],f[i-W-1][que[l]]+(que[l]-j)*ap[i]);
		}
		l=1,r=0;
		for(int j=P;j>=0;j--){
			while(l<=r && que[l]>j+bs[i]) l++;
			while(l<=r && f[i-W-1][que[r]]+que[r]*bp[i]<=f[i-W-1][j]+j*bp[i]) r--;
			que[++r]=j;
			if(l<=r)
				f[i][j]=max(f[i][j],f[i-W-1][que[l]]+(que[l]-j)*bp[i]);
			
		}
	}
	for(int i=0;i<=P;i++){
		ans=max(ans,f[T][i]);
	}
	cout << ans;
	return 0;
}
