#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<stdlib.h>
using namespace std;
#define N 200005

char str1[N],str2[N];
int a[N];
bool flag[N];

int main()
{
    scanf("%s%s",str1+1,str2+1);
    int len1=strlen(str1+1),len2=strlen(str2+1);
    for(int i=1;i<=len1;i++)
        scanf("%d",&a[i]);
    int l=1,r=len1,res=0;
    while(l<=r)
    {
        int mid=(l+r)/2;
        memset(flag,0,sizeof(flag));
        for(int i=1;i<=mid;i++)
            flag[a[i]]=1;
        int pos=1;
        for(int i=1;i<=len1;i++)
        {
            if(flag[i]==1)
                continue;
            if(pos>len2)
                break;
            if(str1[i]==str2[pos])
                pos++;
        }
        if(pos>len2)
        {
            res=mid;
            l=mid+1;
        }
        else
            r=mid-1;
    }
    printf("%d\n",res);
    return 0;
}
