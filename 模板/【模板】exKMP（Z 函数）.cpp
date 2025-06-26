#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int N=5e7+10;
string a,b;
int z[N];
long long ans1,ans2;
void Z(string s){
	int l=0;
    for(int i=1;i<(int)s.length();i++){
        if(l+z[l]>i) z[i]=min(z[i-l],l+z[l]-i);
        while(i+z[i]<(int)s.length() && s[z[i]]==s[i+z[i]]) z[i]++;
        if(i+z[i]>l+z[l]) l=i;
    }
//	for(int i=0;i<s.length();i++){
//		cout<<z[i]<<' ';
//	}
	return ;
}
int main(){
	cin>>a>>b;
	Z(b+a);
	ans1^=1ll*(b.length()+1)*1;
	for(int i=1;i<(int)b.length();i++) ans1^=1ll*(min(z[i],(int)b.length()-i)+1)*(i+1);
	for(int i=0;i<(int)a.length();i++) ans2^=1ll*(min(z[i+(int)b.length()],(int)b.length())+1)*(i+1);
	cout<<ans1<<'\n'<<ans2;
	return 0;
}