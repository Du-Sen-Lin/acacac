#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
//是否存在X+Y==a 且LCM(最小公倍数)(X,Y)=b;
//X+Y=a
//X*Y=gcd(X,Y)*lcm(X,Y)
using namespace std;
//最大公约数
long long gcd(long long a,long long b){
    if(a%b){
        return gcd(b,a%b);
    }
    return b;
}

int main(){
long long  a,b;
long long gcdd;
long long cnt;
long long X,Y;
    while(~scanf("%lld %lld",&a,&b)){
        gcdd=gcd(a,b);
        cnt=a*a-4*gcdd*b;
        if(cnt<0){
            cout<<"No Solution"<<endl;
            continue;
        }
        long long ss=sqrt(1.0*cnt);
        if(ss*ss!=cnt||(ss+a)%2){
            cout<<"No Solution"<<endl;
            continue;
        }
        X=(ss+a)/2;
        Y=a-X;
        if(X>Y){
            swap(X,Y);
        }
        printf("%lld %lld\n",X,Y);
    }


return 0;
}
