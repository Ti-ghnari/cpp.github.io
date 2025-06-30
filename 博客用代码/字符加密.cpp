#include<iostream>
#include<cstring>
using namespace std;
const int N=300010;
string s,a;
int n,m;
int x[N],y[N];
int sa[N],cnt[N],num;
int len;
void SA(){
	for(int i=0;i<n;i++){
		x[i]=s[i];
		cnt[x[i]]++;
	}
	for(int i=1;i<m;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=0;i<n;i++){
		sa[--cnt[x[i]]]=i;
	}
	for(int k=1;k<=n;k<<=1){
		int num=0;
		for(int i=n-k;i<n;i++){
			y[num++]=i;
		}
		for(int i=0;i<n;i++){
			if(sa[i]>=k) y[num++]=sa[i]-k;
		}
		for(int i=0;i<m;i++) cnt[i]=0;
		for(int i=0;i<n;i++) cnt[x[y[i]]]++;
		for(int i=1;i<m;i++) cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--){
			sa[--cnt[x[y[i]]]]=y[i];
			y[i]=0;
		}
		swap(x,y);
		x[sa[0]]=0,num=1;
		for(int i=1;i<n;i++){
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? num-1 : num++;
		}
		if(num==n) break;
		m=num;
	}
	return ;
}
int main(){
	cin>>s;
	len=s.length();
	n=2*len;
	m=300;
	for(int i=len;i<n;i++){
		s+=s[i-len];
	}
	SA();
	for(int i=0;i<n;i++){
		if(sa[i]<len){
			cout<<s[sa[i]+len-1];
		}
	}
	return 0;
}
