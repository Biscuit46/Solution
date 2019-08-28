// luogu-judger-enable-o2
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
typedef pair<double,double> pii;
#define mp make_pair
struct node{
	double xymul,sumx,sumy,xsqr;
	int l,r;
	pii tag1,tag2;
	bool flag1,flag2;
}t[N<<2];
int n,m,x[N],y[N];
double sum[N],sumsqr[N];
pii operator+(pii a,pii b){return mp(a.first+b.first,a.second+b.second);}
double sumid(int l,int r){return sum[r]-sum[l-1];}
double sumidsqr(int l,int r){return sumsqr[r]-sumsqr[l-1];}
void pushup(int o){
	t[o].sumx=t[o<<1].sumx+t[o<<1|1].sumx;
	t[o].sumy=t[o<<1].sumy+t[o<<1|1].sumy;
	t[o].xsqr=t[o<<1].xsqr+t[o<<1|1].xsqr;
	t[o].xymul=t[o<<1].xymul+t[o<<1|1].xymul;
}
void puttag1(int o,double S,double T){
	int l=t[o].l,r=t[o].r;t[o].flag1=1;
	t[o].tag1.first+=S;t[o].tag1.second+=T;
	t[o].xsqr+=2*t[o].sumx*S+S*S*(r-l+1);
	t[o].xymul+=S*T*(r-l+1)+t[o].sumy*S+t[o].sumx*T;
	t[o].sumx+=(r-l+1)*S;t[o].sumy+=(r-l+1)*T;
}
void puttag2(int o,double S,double T){
	int l=t[o].l,r=t[o].r;
	t[o].tag2=mp(S,T);t[o].flag2=1;t[o].tag1=mp(0,0);
	t[o].xsqr=(r-l+1)*S*S+sumidsqr(l,r)+2*S*sumid(l,r);
	t[o].xymul=S*T*(r-l+1)+sumid(l,r)*(S+T)+sumidsqr(l,r);
	t[o].sumx=S*(r-l+1)+sumid(l,r);t[o].sumy=T*(r-l+1)+sumid(l,r);
}
void pushdown(int o){
	if(t[o].flag2){
		puttag2(o<<1,t[o].tag2.first,t[o].tag2.second);
		puttag2(o<<1|1,t[o].tag2.first,t[o].tag2.second);
		t[o].flag2=0;t[o].tag2=mp(0,0);
	}
	if(t[o].flag1){
		puttag1(o<<1,t[o].tag1.first,t[o].tag1.second);
		puttag1(o<<1|1,t[o].tag1.first,t[o].tag1.second);
		t[o].flag1=0;t[o].tag1=mp(0,0);
	}
}
void build(int o,int l,int r){
	t[o].l=l;t[o].r=r;t[o].tag1=mp(0,0);t[o].tag2=mp(0,0);
	t[o].flag1=false;t[o].flag2=false;
	if(l==r){
		t[o].sumx=x[l];t[o].sumy=y[l];
		t[o].xymul=1ll*x[l]*y[l];t[o].xsqr=1ll*x[l]*x[l];
		return;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);build(o<<1|1,mid+1,r);
	pushup(o);
}
//	int xymul,sumx,sumy,xsqr;
double query_sumx(int o,int l,int r,int posl,int posr){
	if(posl<=l && r<=posr)return t[o].sumx;
	int mid=(l+r)>>1;double ret=0;pushdown(o);
	if(posl<=mid)ret+=query_sumx(o<<1,l,mid,posl,posr);
	if(mid<posr)ret+=query_sumx(o<<1|1,mid+1,r,posl,posr);
	return ret;
}
double query_sumy(int o,int l,int r,int posl,int posr){
	if(posl<=l && r<=posr)return t[o].sumy;
	int mid=(l+r)>>1;double ret=0;pushdown(o);
	if(posl<=mid)ret+=query_sumy(o<<1,l,mid,posl,posr);
	if(mid<posr)ret+=query_sumy(o<<1|1,mid+1,r,posl,posr);
	return ret;
}
double query_xsqr(int o,int l,int r,int posl,int posr){
	if(posl<=l && r<=posr)return t[o].xsqr;
	int mid=(l+r)>>1;double ret=0;pushdown(o);
	if(posl<=mid)ret+=query_xsqr(o<<1,l,mid,posl,posr);
	if(mid<posr)ret+=query_xsqr(o<<1|1,mid+1,r,posl,posr);
	return ret;
}
double query_xymul(int o,int l,int r,int posl,int posr){
	if(posl<=l && r<=posr)return t[o].xymul;
	int mid=(l+r)>>1;double ret=0;pushdown(o);
	if(posl<=mid)ret+=query_xymul(o<<1,l,mid,posl,posr);
	if(mid<posr)ret+=query_xymul(o<<1|1,mid+1,r,posl,posr);
	return ret;
}
void modify_sum(int o,int l,int r,int posl,int posr,double S,double T){
	if(posl<=l && r<=posr){puttag1(o,S,T);return;}
	int mid=(l+r)>>1;pushdown(o);
	if(posl<=mid)modify_sum(o<<1,l,mid,posl,posr,S,T);
	if(mid<posr)modify_sum(o<<1|1,mid+1,r,posl,posr,S,T);
	pushup(o);
}
void modify_ins(int o,int l,int r,int posl,int posr,double S,double T){
	if(posl<=l && r<=posr){puttag2(o,S,T);return;}
	int mid=(l+r)>>1;pushdown(o);
	if(posl<=mid)modify_ins(o<<1,l,mid,posl,posr,S,T);
	if(mid<posr)modify_ins(o<<1|1,mid+1,r,posl,posr,S,T);
	pushup(o);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif
	n=gi();m=gi();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+i;
	for(int i=1;i<=n;i++)sumsqr[i]=sumsqr[i-1]+1ll*i*i;
	for(int i=1;i<=n;i++)x[i]=gi();
	for(int i=1;i<=n;i++)y[i]=gi();
	build(1,1,n);
	while(m--){
		int opt=gi(),L=gi(),R=gi();
		if(opt==1){
			int len=R-L+1;
			double sumx=query_sumx(1,1,n,L,R),sumy=query_sumy(1,1,n,L,R),xymul=query_xymul(1,1,n,L,R);
			double xba=sumx*1./len,yba=sumy*1./len;
			double up=xymul-yba*sumx-xba*sumy+len*xba*yba;
		    double xsqr=query_xsqr(1,1,n,L,R);
			double down=xsqr+len*xba*xba-2*xba*sumx;
			printf("%.10lf\n",up/down);
		}
		else{
			int S=gi(),T=gi();
			if(opt==2)modify_sum(1,1,n,L,R,S,T);
			if(opt==3)modify_ins(1,1,n,L,R,S,T);
		}
	}
	return 0;
}
#undef mp
