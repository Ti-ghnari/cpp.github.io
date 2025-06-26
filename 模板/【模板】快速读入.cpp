#include<bits/stdc++.h>

using namespace std;

inline int read(){
    char s;
    int k=0;
    bool f=false;
    while((s=getchar_unlocked())!='-'&&s!=EOF&&!isdigit(s));
    if(s==EOF)exit(0);
    if(s=='-') f=1,s=getchar_unlocked();
    while(isdigit(s)){
        k=k*10+(s-'0');
        s=getchar_unlocked();
    }
    return f ? -k : k;
}
int n,a,sum;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		sum+=read();
	}
	cout<<sum;
	return 0;
}