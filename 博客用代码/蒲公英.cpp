#include<bits/stdc++.h>

using namespace std;
const int N=4e4+10;
int n,m;
int a[N],b[N];
int ans;
int len,tot;
int f[210][210],s[210][N];
int t[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	len=int(sqrt(n));
	tot=(n-1)/len+1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	int sum=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+1+sum,a[i])-b;
	}
	for(int i=1;i<=tot;i++){
		for(int j=(i-1)*len+1;j<=min(i*len,n);j++){
			s[i][a[j]]++;
		}
		for(int j=1;j<=sum;j++){
			s[i][j]+=s[i-1][j];
		}
	}
	for(int i=1;i<=tot;i++){
		for(int j=i;j<=tot;j++){
			int mx=f[i][j-1];
			for(int k=(j-1)*len+1;k<=min(len*j,n);k++){
				if((s[j][a[k]]-s[i-1][a[k]]>s[j][mx]-s[i-1][mx]) || (s[j][a[k]]-s[i-1][a[k]]==s[j][mx]-s[i-1][mx] && a[k]<mx))
					mx=a[k];
			}
			f[i][j]=mx;
		}
	}
	while(m--){
		int l,r;
		cin>>l>>r;
		l=(l+ans-1)%n+1;
		r=(r+ans-1)%n+1;
		if(l>r) l^=r^=l^=r;
		int bl=(l-1)/len+1,br=(r-1)/len+1,mx=0;
		if(br-bl<=1){
			for(int i=l;i<=r;i++) t[a[i]]++;
			for(int i=l;i<=r;i++){
				if(t[a[i]]>t[mx] || (t[a[i]]==t[mx] && a[i]<mx)) mx=a[i];
			}
			for(int i=l;i<=r;i++) t[a[i]]=0;
		}else{
			for(int i=l;i<=len*bl;i++){
				t[a[i]]++;
			}
			for(int i=(br-1)*len+1;i<=r;i++){
				t[a[i]]++;
			}
			mx=f[bl+1][br-1];
			for(int i=l;i<=len*bl;i++){
				int old=t[mx]+s[br-1][mx]-s[bl][mx];
				int now=t[a[i]]+s[br-1][a[i]]-s[bl][a[i]];
				if(now>old || (now==old && a[i]<mx)) mx=a[i];    
			}
			for(int i=(br-1)*len+1;i<=r;i++){
				int old=t[mx]+s[br-1][mx]-s[bl][mx];
				int now=t[a[i]]+s[br-1][a[i]]-s[bl][a[i]];
				if(now>old || (now==old && a[i]<mx)) mx=a[i];
			}
			for(int i=l;i<=len*bl;i++){
				t[a[i]]=0;
			}
			for(int i=(br-1)*len+1;i<=r;i++){
				t[a[i]]=0;
			}
		}
		ans=b[mx];
		cout<<ans<<'\n';
	}
	
	return 0;
}
