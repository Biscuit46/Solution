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
#define file(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
inline int gi(){
	int f=1,sum=0;char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return f*sum;
}
const int N=310;
int n,m;
char s[N];
typedef unsigned long long ull;
const ull base=19260817;
ull Hash[N][N],pw[N];
double a[N][N],ans[N],fac[N];
void init(){
	pw[0]=1;for(int i=1;i<=m;i++)pw[i]=pw[i-1]*base;
	fac[0]=1;for(int i=1;i<=m;i++)fac[i]=fac[i-1]*1./2;
}
void Gauss(int n){
	for(int i=1;i<=n;i++){
		int id=i;
		for(int j=i+1;j<=n;j++)
			if(fabs(a[id][i])<fabs(a[j][i]))id=j;
		if(id!=i)swap(a[id],a[i]);
		for(int j=i+1;j<=n;j++){
			double delta=a[j][i]/a[i][i];
			for(int k=i;k<=n+1;k++)
				a[j][k]-=delta*a[i][k];
		}
	}
	for(int i=n;i;i--){
		ans[i]=a[i][n+1]/a[i][i];
		for(int j=1;j<i;j++)
			a[j][n+1]-=a[j][i]*ans[i];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif
	n=gi();m=gi();init();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			Hash[i][j]=Hash[i][j-1]*base+s[j];
	}
	for(int i=1;i<=n;i++)a[i][n+1]=fac[m],a[i][i]=1;
	for(int i=1;i<=n;i++)a[n+1][i]=1;a[n+1][n+2]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=m-(i==j);k++)
				if(Hash[i][k]==Hash[j][m]-Hash[j][m-k]*pw[k])a[i][j]+=fac[m-k];
	Gauss(n+1);
	for(int i=1;i<=n;i++)printf("%.8lf\n",ans[i]);
	return 0;
}
