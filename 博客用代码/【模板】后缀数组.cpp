#include<iostream>
#include<cstring>
using namespace std;
const int N=1e6+10;
int sa[N],x[N],y[N];
//sa 数组同上，x 数组表示 i 位置的字母大小，y 表示 i+2^k 位置的字母大小
int cnt[N],num;
//如果使用快排，复杂度是双log 的，但是因为我们每次排序两个值，所以使用基数排序，复杂度变为 单log。
int m,len;
string s;
void SA(){
	for(int i=1;i<=len;i++){
		x[i]=s[i];
		cnt[x[i]]++;
	}
//  准备第一次基数排序，将 i 位置的字符入桶
	for(int i=2;i<=m;i++){
		cnt[i]+=cnt[i-1];
	}
//  做前缀和可知相同字符最大可排在多少
	for(int i=len;i>=1;i--){
		sa[cnt[x[i]]--]=i;
	}
//  基数排序
//  下面是合并 i 与 i+2^k 的过程
	for(int k=1;k<=len;k<<=1){
		int num=0;
		for(int i=len-k+1;i<=len;i++){
			y[++num]=i;
		}
//    因为此时会出现位数不够的情况，所以提前处理。
		for(int i=1;i<=len;i++){
			if(sa[i]>k){
				y[++num]=sa[i]-k;
			}
		}
//    i+2^k 位置的字符入桶
		for(int i=1;i<=m;i++) cnt[i]=0;
		for(int i=1;i<=len;i++) cnt[x[i]]++;
		for(int i=2;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=len;i>=1;i--){
			sa[cnt[x[y[i]]]--]=y[i];
			y[i]=0;
		}
//    基数排序
		swap(x,y);
		x[sa[1]]=1,num=1;
		for(int i=2;i<=len;i++)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) ? num : ++num;
		if(num==len) break;
		m=num;
//    更新 i 位置的子串情况
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
