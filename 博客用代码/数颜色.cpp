#include<bits/stdc++.h>
#define N 100010
#define ll long long
using namespace std;
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
int main(){
	
	
	return 0;
}
