//https://blog.csdn.net/song_4/article/details/53063327

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>

using namespace std;

int main(){
    int n;
    while(~scanf("%d",&n)&&n)
   {
    n=n+1;
    if(n%2==1){
        cout<<"1"<<endl;
    }
    else{
        cout<<"0"<<endl;
    }
   }
return 0;
}
