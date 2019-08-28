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
const int N=100010;
int n,m,front[N],cnt,son[N],siz[N],dep[N],fa[N],dfn[N],Time,top[N],val[N];
struct node{int to,nxt;}e[N<<1];
void Add(int u,int v){e[++cnt]=(node){v,front[u]};front[u]=cnt;}
void dfs1(int u,int ff){
	fa[u]=ff;siz[u]=1;dep[u]=dep[ff]+1;
	for(int i=front[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==ff)continue;
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void dfs2(int u,int tp){
	top[u]=tp;dfn[u]=++Time;val[Time]=u;
	if(!son[u])return;
	dfs2(son[u],tp);
	for(int i=front[u];i;i=e[i].nxt)
		if(e[i].to!=fa[u] && e[i].to!=son[u])dfs2(e[i].to,e[i].to);
}
struct tree{int val,l,r,tag;}t[N<<2];
void pushup(int o){t[o].val=max(t[o<<1].val,t[o<<1|1].val);}
void pushdown(int o){
	if(t[o].tag){
		t[o<<1].tag+=t[o].tag;t[o<<1|1].tag+=t[o].tag;
		t[o<<1].val+=t[o].tag;t[o<<1|1].val+=t[o].tag;
		t[o].tag=0;
	}
}
void build(int o,int l,int r){
	t[o].l=l;t[o].r=r;t[o].tag=0;
	if(l==r){t[o].val=dep[val[l]];return;}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);build(o<<1|1,mid+1,r);
	pushup(o);
}
void modify(int o,int l,int r,int posl,int posr,int k){
	if(posl<=l && r<=posr){t[o].tag+=k;t[o].val+=k;return;}
	int mid=(l+r)>>1;pushdown(o);
	if(posl<=mid)modify(o<<1,l,mid,posl,posr,k);
	if(mid<posr)modify(o<<1|1,mid+1,r,posl,posr,k);
	pushup(o);
}
int query_val(int o,int l,int r,int pos){
	if(l==r)return t[o].val;
	int mid=(l+r)>>1;pushdown(o);
	if(pos<=mid)return query_val(o<<1,l,mid,pos);
	return query_val(o<<1|1,mid+1,r,pos);
}
int query_mx(int o,int l,int r,int posl,int posr){
	if(posl<=l && r<=posr)return t[o].val;
	int mid=(l+r)>>1,ret=0;pushdown(o);
	if(posl<=mid)ret=max(ret,query_mx(o<<1,l,mid,posl,posr));
	if(mid<posr)ret=max(ret,query_mx(o<<1|1,mid+1,r,posl,posr));
	return ret;
}
int getlca(int x,int y){
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y])swap(x,y);
	return y;
}
struct Splay{int ch[2],ff;}s[N];
bool isroot(int x){return (s[s[x].ff].ch[0]!=x)&(s[s[x].ff].ch[1]!=x);}
void rotate(int x){
	int y=s[x].ff,z=s[y].ff,k=s[y].ch[1]==x;
	if(!isroot(y))s[z].ch[s[z].ch[1]==y]=x;s[x].ff=z;
	s[y].ch[k]=s[x].ch[k^1];s[s[x].ch[k^1]].ff=y;
	s[x].ch[k^1]=y;s[y].ff=x;
}
void splay(int x){
	while(!isroot(x)){
		int y=s[x].ff,z=s[y].ff;
		if(!isroot(y))
			(s[y].ch[1]==x)^(s[z].ch[1]==y)?rotate(x):rotate(y);
		rotate(x);
	}
}
int findroot(int x){
	while(s[x].ch[0])x=s[x].ch[0];
	return x;
}
void access(int x){
	for(int y=0;x;y=x,x=s[x].ff){
		splay(x);
		if(s[x].ch[1]){
			int z=findroot(s[x].ch[1]);
			modify(1,1,n,dfn[z],dfn[z]+siz[z]-1,1);
		}
		s[x].ch[1]=y;
		if(s[x].ch[1]){
			int z=findroot(s[x].ch[1]);
			modify(1,1,n,dfn[z],dfn[z]+siz[z]-1,-1);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif
	n=gi();m=gi();
	for(int i=1;i<n;i++){int u=gi(),v=gi();Add(u,v);Add(v,u);}
	dfs1(1,1);dfs2(1,1);build(1,1,n);
	for(int i=2;i<=n;i++)s[i].ff=fa[i];
	while(m--){
		int opt=gi(),x=gi();
		if(opt==1)access(x);
		else if(opt==2){
			int y=gi();
			int lca=getlca(x,y);
			printf("%d\n",query_val(1,1,n,dfn[x])+query_val(1,1,n,dfn[y])-2*query_val(1,1,n,dfn[lca])+1);
		}
		else printf("%d\n",query_mx(1,1,n,dfn[x],dfn[x]+siz[x]-1));
	}
	return 0;
}
