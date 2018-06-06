#include<bits/stdc++.h>
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<string>
#include<stdio.h>
#include<map>
#include<fstream>
using namespace std;
int a[27];                  //存储每个字母出现的次数
char s[1000000];
//int n;
int m;      //一共多少个点
int num=0;    //叶子节点个数
int len;
map<char,int> v;  //对应的字母和出现的次数
typedef struct{
    char c;
    int weight;  //权重
    int parent,lchild,rchild;  //节点的双亲下标，左右孩子的下标
    char code;                   //结点编号
}htnode,*huffmantree;

//统计短文出现的字母种数和每个字母出现的次数
void f1(){
    FILE *fi=freopen("a.txt","r",stdin);
    gets(s);                //gets()读入时空格也读入，直到遇到回格键
     len=strlen(s);
    cout<<len<<endl;        //短文长度
    for(int i=0;i<len;i++){

        if(s[i]-'a'>=0&&s[i]-'a'<=25){
            a[s[i]-'a']++;
        }
        if(s[i]-'A'>=0&&s[i]-'A'<=25){
            a[s[i]-'A']++;
        }
    }
    //    int num=0;
    for(int i=0;i<26;i++){

        if(a[i]>0){
            num++;
        char cha;
        cha='a'+i;
        cout<<cha<<": "<<a[i]<<" ";     //每个字母出现的次数  作为权
        v.insert(pair<char,int>(cha,a[i]));
        }
    }
    cout<<endl;
    printf("字母出现的种数：");
    cout<<num<<endl;
    cout<<endl;
    fclose(fi);
}


//选择两个权值最小的点
void Selectmin(huffmantree ht,int num2,int &s1,int &s2){
    s1=s2=0;    //初始化两个最小节点的位置
    int i;
    for(i=1;i<=num2;i++){
        if(ht[i].parent==0){
            if(s1==0) s1=i;
            else{
                s2=i;
                break;
            }
        }
    }
    if(ht[s1].weight>ht[s2].weight){
        int t=s1;
        s1=s2;
        s2=t;
    }
/***
    //这个操作好骚  学不会学不会；这样就找到两个权值最小的点的位置了
    ***/
    for(i=i+1;i<num2;i++){
        if(ht[i].parent==0){
            if(ht[i].weight<ht[s1].weight){
                s2=s1;
                s1=i;
            }
            else if(ht[i].weight<ht[s2].weight){
                s2=i;
            }
        }
    }
}

//创建huffmantree

void creathuffmantree(huffmantree &ht,int num,map<char,int> v){
    m=2*num-1;  //num个叶子的huffman树共有2num-1个节点

    ht = new htnode[m+1];   //htnode[0]不存节点
    for(int i=1;i<=m;i++){   //初始化每个节点的值
        ht[i].parent=ht[i].lchild=ht[i].rchild=0;
        ht[i].code='9';       //初始化编码都为-1
    }
        map<char, int>::reverse_iterator iter;
    int j=1;
    for(iter = v.rbegin(); iter !=v.rend(); iter++){

        cout<<iter->first<<"  "<<iter->second<<endl;
        ht[j].c=iter->first;
        ht[j].weight=iter->second;
        j++;
    }


/***
//写了半个小时事故
    //cout<<n<<endl;
    int j=1;
    for(int i=1;i<=26;i++){
     //   for(int j=1;j<=num;j++){
        //所以这儿该怎么赋值？？？？  现在应该是对了
        if(a[i-1]>0){
        //   cout<<i-1<<":"<<a[i-1]<<endl;//i:0-25 a-z
       //     for(int j=1;j<=num;j++)    //地方放错
            ht[j].weight=a[i-1];        //j从1开始，表示的权依此为文本中存在的字母的字典序 a c d f
            if(j==num) break;
            else j++;
        }
      }

***/
    //test
    for(int i=1;i<=num;i++){
        cout<<ht[i].c<<": "<<ht[i].weight<<endl;
    }


    ht[0].weight=num;
    for(int i=num+1;i<=m;i++){//已有num个节点，从num+1开始添加节点  共添加num-1个，也就是到m
        int s1,s2;
        Selectmin(ht,i,s1,s2); //传入添加节点的位置  返回两个最小值s1<=s2
         //将两节点的双亲设置为新节点的位置
         ht[s1].parent=i;
         ht[s2].parent=i;
         ht[s1].code='0';     //编码
         ht[s2].code='1';
         //添加新节点，左右孩子
         ht[i].lchild=s1;
         ht[i].rchild=s2;
         ht[i].weight=ht[s1].weight+ht[s2].weight;//新节点权值
    }
}
//计算huffman树总路径长度
int huffmantreeWPL(huffmantree ht,int i,int d){ //传入huffman树，节点位置，节点深度
        if(ht[i].lchild==0&&ht[i].rchild==0){  //叶子节点；算出该节点路径
            return ht[i].weight*d;
        }
        else{  // 若该节点不是叶子节点，则该节点的路径等于左右孩子的路径和
            return huffmantreeWPL(ht,ht[i].lchild,d+1)+huffmantreeWPL(ht,ht[i].rchild,d+1);
        }
}
//输出huffman树各节点的信息
void printf(huffmantree ht){
    cout<<"你能看懂这个关系吗"<<endl;
//初始写法
/****  与答案不服啊 这不是最优的
 1   1  5  0  0
 2   2  5  0  0
 3   3  6  0  0
 4   5  6  0  0
 5   3  7  1  2
 6   8  7  3  4
 7   11  0  5  6
****/
//各种蜜汁bug  改了
/***正确结果
 1   1  5  0  0
 2   2  5  0  0
 3   3  6  0  0
 4   5  7  0  0
 5   3  6  1  2
 6   6  7  3  5
 7   11  0  4  6
 ***/
 //改进
 /***
叶子节点： f 节点的序号： 1 权值： 5 父亲节点序号: 7 左孩子节点序号： 0 右孩子节点序号： 0
叶子节点： d 节点的序号： 2 权值： 3 父亲节点序号: 6 左孩子节点序号： 0 右孩子节点序号： 0
叶子节点： c 节点的序号： 3 权值： 2 父亲节点序号: 5 左孩子节点序号： 0 右孩子节点序号： 0
叶子节点： a 节点的序号： 4 权值： 1 父亲节点序号: 5 左孩子节点序号： 0 右孩子节点序号： 0
叶子节点：   节点的序号： 5 权值： 3 父亲节点序号: 6 左孩子节点序号： 4 右孩子节点序号： 3
叶子节点：   节点的序号： 6 权值： 6 父亲节点序号: 7 左孩子节点序号： 2 右孩子节点序号： 5
叶子节点：   节点的序号： 7 权值： 11 父亲节点序号: 0 左孩子节点序号： 1 右孩子节点序号： 6
***/

    for(int i=1;i<=m;i++){

        cout<<"叶子节点： "<<ht[i].c<<" ";
       // cout<<"第 "<<i<<" 个点：";
       cout<<"节点的序号： "<<i<<" ";
        cout<<"权值： "<<ht[i].weight<<" ";
        cout<<"父亲节点序号: "<<ht[i].parent<<" ";
        cout<<"左孩子节点序号： "<<ht[i].lchild<<" ";
        cout<<"右孩子节点序号： "<<ht[i].rchild<<" "<<endl;
    }

}

//输出各叶子节点的编码
void Encoding(huffmantree ht,int i){
    if(ht[i].parent==0){
        return;
    }
    else{
        Encoding(ht,ht[i].parent);
    }
    cout<<ht[i].code;


}
//输出叶子节点的编码
void huffmantreeEncoding(huffmantree ht){
  //  freopen("b.txt","w",stdout);
    for(int i=1;i<=num;i++){  //只输出前num,即叶子节点的编码
        if(ht[i].lchild==0&&ht[i].rchild==0) //如果该节点为叶子节点
        {
           // char ch;

            cout<<ht[i].c<<" 权值:";
            printf("%d：",ht[i].weight);
            cout<<"编码：";
            Encoding(ht,i);    //用递归输出该节点的编码
            printf("\n");
        }
    }
}
//对原文进行编码，存入b中
void  trans(huffmantree ht){
    FILE *fi=freopen("a.txt","r",stdin);
    FILE *fo=freopen("b.txt","w",stdout);
   gets(s);                //gets()读入时空格也读入，直到遇到回格键
     len=strlen(s);
    for(int i=0;i<len;i++){
        for(int j=1;j<=num;j++){
            if(s[i]==ht[j].c){

                Encoding(ht,j);
            }
        }
        if(s[i]<'a'||s[i]>'z'){
            cout<<s[i];
        }
    }
    fclose(fo);
    fclose(fi);
   // cout<<s<<endl;

}

//用Haffman树对b中码文进行译码，结果存入文件c中，
//比较a,c是否一致，以检验编码、译码的正确性。
void yima(huffmantree ht){
    FILE *fi1=freopen("a.txt","r",stdin);
    gets(s);
    //int len1=strlen(s);
    fclose(fi1);
    FILE *fi2=freopen("b.txt","r",stdin);
    char b[1010];
    gets(b);
    //int len2=strlen(b);
    fclose(fi2);
    freopen("c.txt","w",stdout);
    int i=m;
    int j=0;
     while(b[j]!='\0'){    //遍历字符数组/编码串
      if(b[j]=='0')
        i=ht[i].lchild;   //走向左孩子
      else if(b[j]=='1')
        i=ht[i].rchild;    //走向右孩子
      //if(b[j]<'a'||b[j]>'z'){
      else{
        printf("%c",b[j]);    //为什么不能用cout
        //cout<<b[j];
      }
      if(ht[i].lchild==0){   //看是否该节点为叶子节点
        printf("%c",ht[i].c);//是的话输出，并返回根节点
        i=m;
      }
      j++;   //无论是否找到叶子节点都读取下一个编码串字符
   }
  //  cout<<len1<<len2;
}

int main()
{
    huffmantree ht;
    f1();
    cout<<num<<endl;
    cout<<endl;
    creathuffmantree(ht,num,v);
    /***
    //wpl：树的所有叶结点的带权路径长度之和，称为树的带权路径长度表示为WPL。
    //WPL=(W1*L1+W2*L2+W3*L3+...+Wn*Ln)
    //N个权值Wi(i=1,2,...n)构成一棵有N个叶结点的二叉树，相应的叶结点的路径长度为Li(i=1,2,...n)。可以证明哈夫曼树的WPL是最小的。
    //WPL是衡量一个带权二叉树优劣的关键。
    //无论如何，对于n个带权节点，总可以用他们作为叶节点构造出一颗最小WPL值得树，并称满足这个条件的二叉树为哈夫曼树。
   ***/
    cout<<"WPL = "<<huffmantreeWPL(ht,m,0)<<endl;
    printf(ht);
    huffmantreeEncoding(ht);
    /***
   // cout<<s<<endl;
   //cout<<m<<endl;
    //cout<<num<<endl;
    //int m1=m;
    //int num1=num;
     // cout<<m1<<endl;
    //cout<<num1<<endl;
    ***/
    trans(ht);
/**
    //cout<<endl;
    //cout<<len<<endl;
    //cout<<m1<<endl;
    //cout<<num1<<endl;
    ***/
    yima(ht);
    return 0;
}
