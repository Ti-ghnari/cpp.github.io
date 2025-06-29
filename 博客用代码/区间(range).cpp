#include<bits/stdc++.h>
#define N 20000010
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
int n,A,B,C,D,P,k,a[N],arr[N],lst[N],ans;
int bel(int x){
	return (x-1)/k;
}
int main(){
	n=read();k=read();P=read();
	A=read();B=read();C=read();D=read();
	a[1]=A;
	for(int i=2;i<=n;i++){a[i]=(1ll*a[i-1]*B+C)%D;}
	arr[1]=a[1],lst[n]=a[n];
	for(int i=2;i<=n;i++){
		if(bel(i)!=bel(i-1)){
			arr[i]=a[i];
		}else{
			arr[i]=1ll*arr[i-1]*a[i]%P;
		}
	}
	for(int i=n-1;i>=1;i--){
		if(bel(i)!=bel(i+1)){
			lst[i]=a[i];
		}else{
			lst[i]=1ll*lst[i+1]*a[i]%P;
		}
	}
	for(int i=1,j=i+k-1;j<=n;i++,j++){
		if(bel(i)==bel(j)) ans^=arr[j];
		else ans^=(1ll*lst[i]*arr[j]%P);
	}
	write(ans);
	return 0;
}

