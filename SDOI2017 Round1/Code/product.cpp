/*
  mail: mleautomaton@foxmail.com
  author: MLEAutoMaton
  This Code is made by MLEAutoMaton
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<set>
#include<map>
#include<iostream>
using namespace std;
#define ll long long
#define re register
#define int ll
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi(){
	int f=1,sum=0;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=1000010,Mx=1e6,Mod=1e9+7,G=1e9+6;
int mu[N],f[N],g[N],is_prime[N],s,prime[N],F[N];
int qpow(int a,int b){
	int ret=1;
	while(b){if(b&1)ret=1ll*ret*a%Mod;b>>=1;a=1ll*a*a%Mod;}
	return ret;
}
void init(){
	f[1]=g[1]=F[0]=F[1]=1;is_prime[1]=1;mu[1]=1;
	for(int i=2;i<=Mx;i++){
		f[i]=(f[i-1]+f[i-2])%Mod;g[i]=qpow(f[i],Mod-2);
		F[i]=1;
		if(!is_prime[i]){prime[++s]=i;mu[i]=-1;}
		for(int j=1;prime[j]*i<=Mx && j<=s;j++){
			is_prime[i*prime[j]]=1;
			if(i%prime[j])mu[i*prime[j]]=-mu[i];
			else {mu[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<=Mx;i++){
		for(int j=i;j<=Mx;j+=i)
			if(mu[j/i]==1)F[j]=1ll*F[j]*f[i]%Mod;
			else if(mu[j/i]==-1)F[j]=1ll*F[j]*g[i]%Mod;
	}
	for(int i=2;i<=Mx;i++)F[i]=1ll*F[i]*F[i-1]%Mod;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif
	int T=gi();init();
	while(T--){
		int n=gi(),m=gi();
		if(n>m)swap(n,m);
		int i=1,ans=1;
		while(i<=n){
			int j=min(n/(n/i),m/(m/i));
			int now=1ll*F[j]*qpow(F[i-1],Mod-2)%Mod;
			ans=1ll*ans*qpow(now,1ll*(n/i)*(m/i)%G)%Mod;
			i=j+1;
		}
		printf("%lld\n",(ans+Mod)%Mod);
	}
	return 0;
}
