#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define forinc(x,a,b) for(int x=a;x<=b;x++)
#define fordec(x,a,b) for(int x=a;x>=b;x--)

#define iii pair<ii,int>

#define fi first
#define se second
#define pb push_back
#define ll long long
#define ii pair<int,int>
#define mt make_tuple

#define getbit(x,i) ((x>>(i))&1)
#define batbit(x,i) (x|(1ll<<(i)))
#define tatbit(x,i) (x&~(1<<(i)))

#define endl '\n'
#define int long long

int n;
const int N=2e5;
vector<int>ke[N];
int d[N];
int f[N];
int P[N][29];
int lg;
void dfs(int u,int pa)
{
    forinc(i,1,lg)   P[u][i]=P[P[u][i-1]][i-1];
    for(auto v:ke[u])
    {
        if(v==pa)  continue;
        P[v][0]=u;
        d[v]=d[u]+1;
        dfs(v,u);
    }
}
int lca(int u,int v)
{
    if(d[u]<d[v])   swap(u,v);
    int del=d[u]-d[v];
    fordec(i,lg,0)  if(getbit(del,i))   u=P[u][i];
    if(u==v)  return u;
    fordec(i,lg,0)
    {
        if(P[u][i]!=P[v][i]&&P[u][i])
        {
            u=P[u][i];
            v=P[v][i];
        }
    }
    return P[u][0];
}
void dfs1(int u,int pa)
{
    for(auto v:ke[u])
    {
        if(v==pa)  continue;
        dfs1(v,u);
        f[u]+=f[v];
    }
}
ii e[N];
main()
{
    //freopen("task.inp","r",stdin);
    cin>>n;
    lg=log2(n)+1;
    forinc(i,1,n-1)
    {
        int u,v;
        cin>>u>>v;
        ke[u].pb(v);
        ke[v].pb(u);
        e[i]= {u,v};
    }
    dfs(1,-1);
    int q;
    cin>>q;
    forinc(i,1,q)
    {
        int u,v;
        cin>>u>>v;
        int lcaa=lca(u,v);
        f[u]+=1;f[v]+=1;f[lcaa]-=2;
    }
    dfs1(1,-1);
    forinc(i,1,n-1)
    {
        int u=e[i].fi;
        int v=e[i].se;
        if(P[u][0]!=v)   swap(u,v);
        cout<<f[u]<<"  ";
    }
}

