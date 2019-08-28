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
const double eps=1e-8;
const int N=110,Mx=50010;
int a[N][N],b[N][N],n,front[Mx],cnt,vis[Mx],s,t,fa[Mx],from[Mx];
struct node{int to,nxt,w;double f;}e[Mx<<1];
double dis[Mx];
queue<int>Q;
bool spfa(){
	Q.push(s);memset(dis,-63,sizeof(dis));dis[s]=0;
	while(!Q.empty()){
		int u=Q.front();Q.pop();vis[u]=0;
		for(int i=front[u];~i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w && dis[v]<dis[u]+e[i].f){
				dis[v]=dis[u]+e[i].f;fa[v]=u;from[v]=i;
				if(!vis[v]){vis[v]=1;Q.push(v);}
			}
		}
	}
	return dis[t]!=dis[t+1];
}
void Add(int u,int v,int w,double f){
	e[cnt]=(node){v,front[u],w,f};front[u]=cnt++;
	e[cnt]=(node){u,front[v],0,-f};front[v]=cnt++;
}
bool check(double mid){
	memset(front,-1,sizeof(front));cnt=0;
	s=2*n+1;t=s+1;
	for(int i=1;i<=n;i++)Add(s,i,1,0),Add(i+n,t,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			Add(i,j+n,1,(double)(a[i][j]*1.-mid*b[i][j]));
	double Cost=0;
	while(spfa()){
		Cost+=dis[t];
		for(int i=t;i!=s;i=fa[i])e[from[i]].w--,e[from[i]^1].w++;
	}
	return Cost>=0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif
	n=gi();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)a[i][j]=gi();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)b[i][j]=gi();
	double l=1.0/10000,r=10000;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.6lf\n",l);
	return 0;
}
