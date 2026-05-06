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
#define fi first
#define se second
#define pb push_back
#define ll long long
#define ii pair<int,int>
#define getbit(x,i) ((x>>(i-1))&1)
#define batbit(x,i) (x|(1ll<<(i-1)))
#define tatbit(x,i) (x&~(1<<(i-1)))
#define gg exit(0);
const int N=2e5+100;
#define int long long
int tot,n,m;
int Time=0;
int num[N],low[N],color[N],siz[N];
vector<int>ke2[N],ke[N];
void add_edge(int u,int v)
{
    ke[u].pb(v);
    ke[v].pb(u);
}
stack<int>sta;
void DFS(int u)
{
    num[u] = low[u] = ++Time;
    color[u] = 1;
    sta.push(u);
    siz[u] = 1;
    for(auto v : ke2[u])
    {
        if (color[v] == 0)
        {
            DFS(v);
            low[u] = min(low[u], low[v]);
            siz[u] += siz[v];
            if (low[v] >= num[u])
            {
                tot++;
                int w;
                do
                {
                    w = sta.top();
                    sta.pop();
                    add_edge(w,tot);
                }
                while (v != w);
                if (low[v] == num[u] || siz[v] == 1)
                {
                    add_edge(u,tot);
                }
            }
        }
        else low[u] = min(low[u], num[v]);
    }
}
int f[N],st[N], ed[N];
int P[N][23],d[N];
int it=0;
void dfs(int u, int pr)
{
    st[u] = ++it;
    forinc(i,1,20) P[u][i] = P[P[u][i-1]][i-1];

    for(auto v: ke[u])
    {
        if(v == pr) continue;
        P[v][0] = u;
        d[v]=d[u]+1;
        dfs(v,u);
    }
    ed[u] = it;
}
int anc(int u, int v)
{
    return ( (st[u] <= st[v] && ed[u] >= ed[v]) || (!u));
}

int lca(int u, int v)
{
    if(anc(u,v)) return u;
    if(anc(v,u)) return v;

    fordec(i,20,0)
    {
        if(!anc(P[u][i], v)) u = P[u][i];
    }
    return P[u][0];
}
int dist(int u,int v)
{
    return d[u]+d[v]-2*d[lca(u,v)];
}
main()
{
    fasty;
    //freopen("task.inp","r",stdin);
    cin>>n>>m;
    int Q;
    cin>>Q;
    forinc(i,1,m)
    {
        int u,v;
        cin>>u>>v;
        ke2[u].pb(v);
        ke2[v].pb(u);
    }
    tot=n;
    DFS(1);
    dfs(1,-1);
    forinc(i,1,Q)
    {
        int u,v;
        cin>>u>>v;
        cout<<dist(u,v)/2<<endl;
    }

}
