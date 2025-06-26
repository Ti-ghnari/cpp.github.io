#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
const int N=1e5+50;
const int inf=2e9+7;
int n,m;
int a[N],tag[N],rnk[N];
int len,tot;
int belong[N],L[N],R[N];
void build(){
	len=120;
	tot=n/len;
	if(n%len) tot++;
	for(int i=1;i<=n;i++){
		belong[i]=(i-1)/len+1;
	}
	for(int i=1;i<=tot;i++){
		L[i]=(i-1)*len+1;
		R[i]=min(i*len,n);
		sort(rnk+L[i],rnk+R[i]+1);
	}
	return ;
}
void Sort(int k){
	for(int i=L[k];i<=R[k];i++) rnk[i]=a[i];
	sort(rnk+L[k],rnk+R[k]+1);
	return ;
}
void modify(int l,int r,int c){
	int x=belong[l],y=belong[r];
	if(x==y){
		for(int i=l;i<=r;i++){
			a[i]+=c;
		}
		Sort(x);
		return ;
	}
	for(int i=l;i<=R[x];i++){
		a[i]+=c;
	}
	Sort(x);
	for(int i=L[y];i<=r;i++){
		a[i]+=c;
	}
	Sort(y);
	for(int i=x+1;i<y;i++){
		tag[i]+=c;
	}
	return ;
}
int check(int l,int r,int w){
	int x=belong[l],y=belong[r];
	int cnt=0;
	if(x==y){
		for(int i=l;i<=r;i++){
			if(a[i]+tag[x]<=w) cnt++;
		}
		return cnt;
	}
	for(int i=l;i<=R[x];i++){
		if(a[i]+tag[x]<=w) cnt++;
	}
	for(int i=L[y];i<=r;i++){
		if(a[i]+tag[y]<=w) cnt++;
	}
	for(int i=x+1;i<y;i++){
		if(rnk[L[i]]+tag[i]>w) continue;
		if(rnk[R[i]]+tag[i]<=w){
			cnt+=R[i]-L[i]+1;
			continue;
		}
		int ll=L[i],rr=R[i];
		while(ll<rr){
			int mid=((ll+rr)>>1)+1;
			if(rnk[mid]+tag[i]<=w) ll=mid;
			else rr=mid-1;
		}
		if(rnk[ll]+tag[i]<=w) cnt+=ll-L[i]+1;
	}
	return cnt;
}
int qmax(int l,int r){
	int x=belong[l],y=belong[r];
	int ans=-inf;
	if(x==y){
		for(int i=l;i<=r;i++){
			ans=max(ans,a[i]+tag[x]);
		}
		return ans;
	}
	for(int i=l;i<=R[x];i++) ans=max(ans,a[i]+tag[x]);
	for(int i=L[y];i<=r;i++) ans=max(ans,a[i]+tag[y]);
	for(int i=x+1;i<y;i++){
		ans=max(ans,rnk[R[i]]+tag[i]);
	}
	return ans;
}
int qmin(int l,int r){
	int x=belong[l],y=belong[r];
	int ans=inf;
	if(x==y){
		for(int i=l;i<=r;i++){
			ans=min(ans,a[i]+tag[x]);
		}
		return ans;
	}
	for(int i=l;i<=R[x];i++) ans=min(ans,a[i]+tag[x]);
	for(int i=L[y];i<=r;i++) ans=min(ans,a[i]+tag[y]);
	for(int i=x+1;i<y;i++){
		ans=min(ans,rnk[L[i]]+tag[i]);
	}
	return ans;
}
void query(int l,int r,int k){
	if(k<1 || k>r-l+1){
		cout<<-1<<'\n';
		return ;
	}
	int ll=qmin(l,r),rr=qmax(l,r);
	while(ll<=rr){
		int mid=(ll+rr)>>1;
		if(check(l,r,mid)<k){
			ll=mid+1;
		}else{
			rr=mid-1;
		}
	}
	cout<<ll<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		rnk[i]=a[i];
	}
	build();
	for(int i=1;i<=m;i++){
		int op,l,r,k;
		cin>>op>>l>>r>>k;
		if(op==1){
			query(l,r,k);
		}else{
			modify(l,r,k);
		}
	}
	return 0;
}
