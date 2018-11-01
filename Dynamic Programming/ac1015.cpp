#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m;
int dp[21][801];
int path[21][801];
/*回溯，确认dp[j][k]方案是否曾选择过候选人i*/
bool select(int j,int k,int i,int* v)
{
	while(j>0 && path[j][k]!=i)
	{
		k-=v[ path[j][k] ];
		j--;
	}
	return j?false:true;
}
int main(void)
{
	int time=1;
	while(cin>>n>>m&&(n||m))
	{
		int i,j,k;
		int p[n+1],d[n+1],s[n+1],v[n+1];
		memset(dp,-1,sizeof(dp));
		memset(path,0,sizeof(path));
		for(i=1;i<=n;i++)
		{
			cin>>p[i]>>d[i];
			s[i]=p[i]+d[i];
			v[i]=p[i]-d[i];
		}
		int fix=m*20;  //总修正值，修正极限为从[-400,400]映射到[0,800]
		dp[0][fix]=0;   //由于修正了数值，因此dp[0][fix]才是真正的dp[0][0]
		for(j=1;j<=m;j++)
			for(k=0;k<=2*fix;k++)
			{
				if(dp[j-1][k]>=0)
				{
					for(i=1;i<=n;i++)
						if(dp[j][ k+v[i] ] < dp[j-1][k]+s[i])
						{
							if(select(j-1,k,i,v))
							{
								dp[j][ k+v[i] ] = dp[j-1][k]+s[i];
								path[j][ k+v[i] ] = i;
							}
						}
				}
			}
		for(k=0;k<=fix;k++)
			if(dp[m][fix-k]>=0 || dp[m][fix+k]>=0)    //从中间向两边搜索最小辨控差的位置k
				break;
		int div=dp[m][fix-k] > dp[m][fix+k] ? (fix-k):(fix+k);  //最小辨控差
		cout<<"Jury #"<<time++<<endl;
		cout<<"Best jury has value ";
		//辩方总值 = （辨控和+辨控差+修正值）/2
		cout<<(dp[m][div]+div-fix)/2<<" for prosecution and value ";
		//控方总值 = （辨控和-辨控差+修正值）/2
		cout<<(dp[m][div]-div+fix)/2<<" for defence:"<<endl;
		int* id=new int[m];
		for(i=0,j=m,k=div;i<m;i++)
		{
			id[i]=path[j][k];
			k-=v[id[i]];
			j--;
		}
		sort(id,id+m);   //升序输出候选人编号
		for(i=0;i<m;i++)
			cout<<' '<<id[i];
		cout<<endl<<endl;
		// int pout = (dp[m][div]+div-fix)/2;
		// int dout = (dp[m][div]-div+fix)/2;
		// cout << abs(pout-dout) << " " << pout+dout << endl;
	}
	return 0;
}
