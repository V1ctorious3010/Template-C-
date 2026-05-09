
#include <bits/stdc++.h>
using namespace std;
#define in ({int x=0;int c=getchar(),n=0;for(;!isdigit(c);c=getchar()) n=(c=='-');for(;isdigit(c);c=getchar()) x=x*10+c-'0';n?-x:x;})
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define forinc(x,a,b) for(int x=a;x<=b;x++)
#define fordec(x,a,b) for(int x=a;x>=b;x--)
#define forv(a,b) for(auto&a:b)
#define fi first
#define se second
#define pb push_back
#define ll long long
#define ii pair<int,int>
#define mt make_tuple
#define all(a) a.begin(),a.end()
#define reset(f,x) memset(f,x,sizeof(f))
#define getbit(x,i) ((x>>(i))&1)
#define batbit(x,i) (x|(1ll<<(i)))
#define tatbit(x,i) (x&~(1<<(i)))
#define gg exit(0);
#define debug(x) cerr << #x << " is " << x << "\n";

#define int long long
const int N=2e5+100;
int pa[N];
vector<ii>ke[N];
struct edgeeeeee
{
    int u,v,w,id;
}edge[N];
int n,m;
int root(int u)
{
    if(pa[u]==-1)   return u;
    return pa[u]=root(pa[u]);
}
bool join(int u, int v) {
        u = root(u); v = root(v);
        if (u == v) return false;
        pa[v] = u;
        return true;
    }
struct data
{
    int par;
    int maxc=-1e18;
}up[N][25];
int l[N];
bool cmp(edgeeeeee u, edgeeeeee v) {
	return u.w<v.w;
}
void dfs(int u,int par)
{
    forinc(i,1,(int)log2(n))
    {
       up[u][i].par=up[up[u][i-1].par][i-1].par;
       up[u][i].maxc=max(up[u][i-1].maxc,up[up[u][i-1].par][i-1].maxc);
    }
    for(auto v:ke[u])
    {
        if(v.fi==par)  continue;
        l[v.fi]=l[u]+1;
        up[v.fi][0].par=u;
        up[v.fi][0].maxc=v.se;
        dfs(v.fi,u);

    }

}
int malca(int u,int v)
{
    int ret=-1e15;
    if(l[u]<l[v])   swap(u,v);
    int del=l[u]-l[v];
   fordec(i,20,0)
    {
        if(getbit(del,i))
        {

            ret=max(ret,up[u][i].maxc);
            u=up[u][i].par;
        }
    }
    if(u==v)
    {
        return ret;
    }
    fordec(i,20,0)
    {
        if(up[u][i].par!=up[v][i].par)
        {
            ret=max({ret,up[u][i].maxc,up[v][i].maxc});
            u=up[u][i].par;
            v=up[v][i].par;


        }
    }
    return ret=max({ret,up[u][0].maxc,up[v][0].maxc});
}
int res[N];
int mst=0;
main()
{

   // freopen("task.inp","r",stdin);
    cin>>n>>m;
    memset(pa,-1,sizeof pa);
    forinc(i,1,m)
    {
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
        edge[i].id=i;
    }
    sort(edge+1,edge+m+1,cmp);
   // forinc(i,1,m)  cout<<edge[i].w<<endl;

    forinc(i,1,m)
    {
        if(!join(edge[i].u,edge[i].v))  continue;
        ke[edge[i].u].pb({edge[i].v,edge[i].w});
        ke[edge[i].v].pb({edge[i].u,edge[i].w});
        res[edge[i].id]=-1;
        mst+=edge[i].w;
    }
   dfs(1,-1);
   forinc(i,1,m)
   {
       if(res[edge[i].id]==-1)   res[edge[i].id]=mst;
       else res[edge[i].id]=mst-malca(edge[i].u,edge[i].v)+edge[i].w;
   }
   forinc(i,1,m)
   {
       cout<<res[i]<< endl;
   }
  //cout<<endl<<mst<<endl;

}
