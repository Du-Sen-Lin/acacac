#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<math.h>
#include<cmath>
using namespace std;

int main(){
    int n;
    cin>>n;
    int m;
    int k;
    int j;
    for(int i=1;i<=1000;i++){
         m=n*i+1;
         k=sqrt(m),
         j=2;
         for(;j<=k;j++){
            if(m%j==0) break;
         }
         if(j<=k){
            printf("%d\n",i);
            break;
         }

    }


return 0;
}
