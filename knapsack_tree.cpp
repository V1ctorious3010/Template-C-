#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
#define fasty ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define forinc(x,a,b) for(int x=a;x<=b;x++)
#define fordec(x,a,b) for(int x=a;x>=b;x--)
#define fi first
#define se second
#define pb push_back
#define ii pair<int,int>
#define getbit(x,i) ((x>>i)&1)
#define batbit(x,i) (x|(1<<i))
#define tatbit(x,i) (x&~(1<<i))
//#define int long long
#define endl '\n'

const int N=5005;
int f[N][N][3];
int n,b;
int c[N],d[N];
int inf;
vector<int>ke[N];
int dfs(int u,int pa)
{
    int szu=1;
    f[u][1][1]=c[u]-d[u];
    f[u][1][0]=c[u];
    f[u][0][0]=0;
    for(auto v:ke[u])
    {
        if(v==pa)  continue;
        int szv=dfs(v,u);
        szu+=szv;
        fordec(i,szu,0)
        {
            if(f[u][i][0]<=b)
            {
                for(int j=0; i+j<=szu&&j<=szv; j++)
                {
                    if(f[v][j][0]<=b)   f[u][i+j][0]=min(f[u][i+j][0],f[u][i][0]+f[v][j][0]);
                }
            }
        }
        fordec(i,szu,1)
        {
            if(f[u][i][1]<=b)
            {
                for(int j=0; i+j<=szu&&j<=szv; j++)
                {
                    if(f[v][j][1]<=b)   f[u][i+j][1]=min(f[u][i+j][1],f[u][i][1]+f[v][j][1]);
                    if(f[v][j][0]<=b)   f[u][i+j][1]=min(f[u][i+j][1],f[u][i][1]+f[v][j][0]);
                }
            }
        }
    }
    return szu;
}
main()
{
    fasty;
    //freopen("task.inp","r",stdin);
    cin>>n>>b;
    forinc(i,1,n)
    {
        cin>>c[i]>>d[i];
        if(i>=2)
        {
            int p;
            cin>>p;
            ke[i].pb(p);
            ke[p].pb(i);
        }
    }
    forinc(i,1,n)  forinc(j,0,n)  forinc(k,0,1)   f[i][j][k]=b+1;
    int tmp=dfs(1,0);
    int res=0;
    fordec(j,n,0)   forinc(i,1,n)
    {
        if(f[i][j][0]<=b)
        {
            res=max(res,j);
        }
        if(i==1)
        {
              if(f[i][j][1]<=b) res=max(res,j);
        }
    }
    cout<<res;
}
