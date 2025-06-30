#include<iostream>

using namespace std;
const int N=6e5+10;
int n,a[N];
int sa[N],num,m;
int cnt[N],x[N],y[N];
int mid=0;
void SA(){
	for(int i=1;i<=n;i++){
		x[i]=a[i];
		cnt[x[i]]++;
	}
	for(int i=2;i<=m;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=n;i>=1;i--){
		sa[cnt[x[i]]--]=i;
	}
	for(int k=1;k<=n;k<<=1){
		int num=0;
		for(int i=n-k+1;i<=n;i++){
			y[++num]=i;
		}
		for(int i=1;i<=n;i++)
			if(sa[i]>k)
				y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) cnt[i]=0;
		for(int i=1;i<=n;i++) cnt[x[i]]++;
		for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--){
			sa[cnt[x[y[i]]]--]=y[i];
			y[i]=0;
		}
		swap(x,y);
		x[sa[1]]=1,num=1;
		for(int i=2;i<=n;i++){
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? num : ++num;
		}
		if(num==n) break;
		m=num;
	}
}
int main(){
//	freopen("5000.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]++;
		a[i+n]=a[i];
	}
	n*=2;
	m=30;
	SA();
	n/=2;
	int mid=1;
	for(int i=1;i<=n;i++){
		if(sa[i]<=n){
			mid=sa[i];
			break;
		}
	}
	for(int i=mid;i<=mid+n-1;i++){
		cout<<a[i]-1<<' ';
	}
	return 0;
}
