#include<cstdio>
#include<algorithm>
#include <iostream  >
#define MN 3100001
using namespace std;

int read_p,read_ca;
inline int read(){
    read_p=0;read_ca=getchar();
    while (read_ca<'0'||read_ca>'9') read_ca=getchar();
    while (read_ca>='0'&&read_ca<='9') read_p=read_p*10+read_ca-48,read_ca=getchar();
    return read_p;
}
struct na{int y,ne;}b[MN<<1],B[MN<<1];
int n,m,q,l[MN],num=0,fa[MN],lo[MN],df[MN],F[MN][20],de[MN],x,y,z,nm=0,st[MN],top=0,SSS=0,L[MN],NUM=0,ID=0;
inline int min(int a,int b){return a<b?a:b;}
inline void in(int x,int y){b[++num].y=y;b[num].ne=l[x];l[x]=num;}
inline void IN(int x,int y){B[++NUM].y=y;B[NUM].ne=L[x];L[x]=NUM; cout << x << " " << y << endl;}
void dfs(int x,int f){
    fa[x]=ID;
    df[x]=lo[x]=++nm;
    for (int i=l[x];i;i=b[i].ne)
    if (b[i].y!=f){
        if (!df[b[i].y]){
            st[++top]=b[i].y;
            dfs(b[i].y,x);
            lo[x]=min(lo[x],lo[b[i].y]);
            if (lo[b[i].y]==df[x]) for (++SSS,IN(x,SSS);top&&df[st[top]]>=df[b[i].y];top--) IN(SSS,st[top]);
            else if (lo[b[i].y]>df[x]) IN(x,b[i].y),top--;
        }else lo[x]=min(lo[x],df[b[i].y]);
    }
}
void work(int x){
    df[x]=0;
    for (int i=1;i<20;i++) F[x][i]=F[F[x][i-1]][i-1];
    for (int i=L[x];i;i=B[i].ne) de[B[i].y]=de[x]+1,F[B[i].y][0]=x,work(B[i].y);
}
inline int lca(int x,int y){
    if (de[x]>de[y]) swap(x,y);
    for (int i=19;i>=0;i--)
    if (de[F[y][i]]>=de[x]) y=F[y][i];
    if (x==y) return x;
    for (int i=19;i>=0;i--)
    if (F[x][i]!=F[y][i]) x=F[x][i],y=F[y][i];
    return F[x][0];
}
int main(){
    n=read();m=read();q=read();SSS=n;
    for (int i=1;i<=m;i++) x=read(),y=read(),in(x,y),in(y,x);
    for (int i=1;i<=n;i++) if (!df[i]) ++ID,dfs(i,0);
    for (int i=1;i<=n;i++) if (df[i]) de[i]=1,work(i);
    while(q--){
        x=read();y=read();z=read();
        if (fa[x]!=fa[z]||fa[y]!=fa[z])puts("NO");else
        m=lca(x,y)^lca(y,z)^lca(x,z),puts(((m>n&&(m==F[z][0]||F[m][0]==z))||m==z)?"YES":"NO");
    }
}
