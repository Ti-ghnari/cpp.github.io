#include<iostream>
#include<cstring>
using namespace std;
const int N=1e6+10;
int sa[N],x[N],y[N];
int cnt[N],num;
int m,len;
string s;
void SA(){
	for(int i=1;i<=len;i++){
		x[i]=s[i];
		cnt[x[i]]++;
	}
	for(int i=2;i<=m;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=len;i>=1;i--){
		sa[cnt[x[i]]--]=i;
	}
	for(int k=1;k<=len;k<<=1){
		int num=0;
		for(int i=len-k+1;i<=len;i++){
			y[++num]=i;
		}
		for(int i=1;i<=len;i++){
			if(sa[i]>k){
				y[++num]=sa[i]-k;
			}
		}
		for(int i=1;i<=m;i++) cnt[i]=0;
		for(int i=1;i<=len;i++) cnt[x[i]]++;
		for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=len;i>=1;i--){
			sa[cnt[x[y[i]]]--]=y[i];
			y[i]=0;
		}
		swap(x,y);
		x[sa[1]]=1,num=1;
		for(int i=2;i<=len;i++)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? num : ++num;
		if(num==len) break;
		m=num;
	}
	for(int i=1;i<=len;i++) cout<<sa[i]<<' ';
}
int main(){
	cin>>s;
	len=s.length();
	s=' '+s;
	m=122;
	SA();


	return 0;
}