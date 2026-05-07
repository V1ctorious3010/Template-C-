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
#define inf 1e15
#define endl '\n'
#define int long long
const int N=1e6+100;
int hashh[N];
int rhashh[N];
int pw[N];
const int mod=1e9+7;
long long gethash(int i,int j)
{
    return ((hashh[j]-hashh[i-1]*pw[j-i+1])%mod+mod)%mod;
}
int n;
int st=1;
int ed=n;
bool check(int v)
{
        int stt=1;
        int edd=n;
        forinc(i,2,n-v)
         {
            if(gethash(i,i+v-1)==gethash(1,v))
            {
                stt=i;
                edd=i+v-1;
            }
        }
        if(stt==1||edd==n)   return 0;
        st=stt;
        ed=edd;
        return 1;

}
int lengh[N];
main()
{
    //freopen("task.inp","r",stdin);
    string s;
    cin>>s;
    n=s.size();
    s=" "+s;

    int save=0;
    pw[0]=1;
    forinc(i,1,n) pw[i] = (pw[i-1]*29)%mod;
    forinc(i,1,n) hashh[i] = (hashh[i-1]*29 + s[i])%mod;
    int spt=0;
    forinc(len,1,n-2)
    {
        if(gethash(1,len)==gethash(n-len+1,n))
        {
           lengh[++spt]=len;
        }
    }
    sort(lengh+1,lengh+spt+1);
    //forinc(i,1,spt)  cout<<lengh[i]<<endl;
    int l=1;
    int r=spt;
    int ans;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(check(lengh[mid]))
        {
            ans=lengh[mid];
           l=mid+1;
        }
        else r=mid-1;
     }
    if(st==1||ed==n||spt==0)
    {
        cout<<"Just a legend"<<endl;
        return 0;
    }
    //cout<<ans<<" " ;
   cout<<s.substr(st,ans);

    cout<<endl;
}


/*
Cấu trúc: Đồ thị cây, gốc là đỉnh 1.
Trạng thái ban đầu: Tất cả đỉnh rỗng (0).
Các thao tác (N <= 500,000; Q <= 50,000):
1 v: Gán trạng thái đầy (1) cho đỉnh v và toàn bộ cây con của v.
2 v: Gán trạng thái rỗng (0) cho đỉnh v và toàn bộ tổ tiên của v.
3 v: Truy vấn trạng thái đỉnh v (1: đầy, 0: rỗng).
*/
