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
int a[27];                  //�洢ÿ����ĸ���ֵĴ���
char s[1000000];
//int n;
int m;      //һ�����ٸ���
int num=0;    //Ҷ�ӽڵ����
int len;
map<char,int> v;  //��Ӧ����ĸ�ͳ��ֵĴ���
typedef struct{
    char c;
    int weight;  //Ȩ��
    int parent,lchild,rchild;  //�ڵ��˫���±꣬���Һ��ӵ��±�
    char code;                   //�����
}htnode,*huffmantree;

//ͳ�ƶ��ĳ��ֵ���ĸ������ÿ����ĸ���ֵĴ���
void f1(){
    FILE *fi=freopen("a.txt","r",stdin);
    gets(s);                //gets()����ʱ�ո�Ҳ���룬ֱ�������ظ��
     len=strlen(s);
    cout<<len<<endl;        //���ĳ���
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
        cout<<cha<<": "<<a[i]<<" ";     //ÿ����ĸ���ֵĴ���  ��ΪȨ
        v.insert(pair<char,int>(cha,a[i]));
        }
    }
    cout<<endl;
    printf("��ĸ���ֵ�������");
    cout<<num<<endl;
    cout<<endl;
    fclose(fi);
}


//ѡ������Ȩֵ��С�ĵ�
void Selectmin(huffmantree ht,int num2,int &s1,int &s2){
    s1=s2=0;    //��ʼ��������С�ڵ��λ��
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
    //���������ɧ  ѧ����ѧ���᣻�������ҵ�����Ȩֵ��С�ĵ��λ����
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

//����huffmantree

void creathuffmantree(huffmantree &ht,int num,map<char,int> v){
    m=2*num-1;  //num��Ҷ�ӵ�huffman������2num-1���ڵ�

    ht = new htnode[m+1];   //htnode[0]����ڵ�
    for(int i=1;i<=m;i++){   //��ʼ��ÿ���ڵ��ֵ
        ht[i].parent=ht[i].lchild=ht[i].rchild=0;
        ht[i].code='9';       //��ʼ�����붼Ϊ-1
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
//д�˰��Сʱ�¹�
    //cout<<n<<endl;
    int j=1;
    for(int i=1;i<=26;i++){
     //   for(int j=1;j<=num;j++){
        //�����������ô��ֵ��������  ����Ӧ���Ƕ���
        if(a[i-1]>0){
        //   cout<<i-1<<":"<<a[i-1]<<endl;//i:0-25 a-z
       //     for(int j=1;j<=num;j++)    //�ط��Ŵ�
            ht[j].weight=a[i-1];        //j��1��ʼ����ʾ��Ȩ����Ϊ�ı��д��ڵ���ĸ���ֵ��� a c d f
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
    for(int i=num+1;i<=m;i++){//����num���ڵ㣬��num+1��ʼ��ӽڵ�  �����num-1����Ҳ���ǵ�m
        int s1,s2;
        Selectmin(ht,i,s1,s2); //������ӽڵ��λ��  ����������Сֵs1<=s2
         //�����ڵ��˫������Ϊ�½ڵ��λ��
         ht[s1].parent=i;
         ht[s2].parent=i;
         ht[s1].code='0';     //����
         ht[s2].code='1';
         //����½ڵ㣬���Һ���
         ht[i].lchild=s1;
         ht[i].rchild=s2;
         ht[i].weight=ht[s1].weight+ht[s2].weight;//�½ڵ�Ȩֵ
    }
}
//����huffman����·������
int huffmantreeWPL(huffmantree ht,int i,int d){ //����huffman�����ڵ�λ�ã��ڵ����
        if(ht[i].lchild==0&&ht[i].rchild==0){  //Ҷ�ӽڵ㣻����ýڵ�·��
            return ht[i].weight*d;
        }
        else{  // ���ýڵ㲻��Ҷ�ӽڵ㣬��ýڵ��·���������Һ��ӵ�·����
            return huffmantreeWPL(ht,ht[i].lchild,d+1)+huffmantreeWPL(ht,ht[i].rchild,d+1);
        }
}
//���huffman�����ڵ����Ϣ
void printf(huffmantree ht){
    cout<<"���ܿ��������ϵ��"<<endl;
//��ʼд��
/****  ��𰸲����� �ⲻ�����ŵ�
 1   1  5  0  0
 2   2  5  0  0
 3   3  6  0  0
 4   5  6  0  0
 5   3  7  1  2
 6   8  7  3  4
 7   11  0  5  6
****/
//������֭bug  ����
/***��ȷ���
 1   1  5  0  0
 2   2  5  0  0
 3   3  6  0  0
 4   5  7  0  0
 5   3  6  1  2
 6   6  7  3  5
 7   11  0  4  6
 ***/
 //�Ľ�
 /***
Ҷ�ӽڵ㣺 f �ڵ����ţ� 1 Ȩֵ�� 5 ���׽ڵ����: 7 ���ӽڵ���ţ� 0 �Һ��ӽڵ���ţ� 0
Ҷ�ӽڵ㣺 d �ڵ����ţ� 2 Ȩֵ�� 3 ���׽ڵ����: 6 ���ӽڵ���ţ� 0 �Һ��ӽڵ���ţ� 0
Ҷ�ӽڵ㣺 c �ڵ����ţ� 3 Ȩֵ�� 2 ���׽ڵ����: 5 ���ӽڵ���ţ� 0 �Һ��ӽڵ���ţ� 0
Ҷ�ӽڵ㣺 a �ڵ����ţ� 4 Ȩֵ�� 1 ���׽ڵ����: 5 ���ӽڵ���ţ� 0 �Һ��ӽڵ���ţ� 0
Ҷ�ӽڵ㣺   �ڵ����ţ� 5 Ȩֵ�� 3 ���׽ڵ����: 6 ���ӽڵ���ţ� 4 �Һ��ӽڵ���ţ� 3
Ҷ�ӽڵ㣺   �ڵ����ţ� 6 Ȩֵ�� 6 ���׽ڵ����: 7 ���ӽڵ���ţ� 2 �Һ��ӽڵ���ţ� 5
Ҷ�ӽڵ㣺   �ڵ����ţ� 7 Ȩֵ�� 11 ���׽ڵ����: 0 ���ӽڵ���ţ� 1 �Һ��ӽڵ���ţ� 6
***/

    for(int i=1;i<=m;i++){

        cout<<"Ҷ�ӽڵ㣺 "<<ht[i].c<<" ";
       // cout<<"�� "<<i<<" ���㣺";
       cout<<"�ڵ����ţ� "<<i<<" ";
        cout<<"Ȩֵ�� "<<ht[i].weight<<" ";
        cout<<"���׽ڵ����: "<<ht[i].parent<<" ";
        cout<<"���ӽڵ���ţ� "<<ht[i].lchild<<" ";
        cout<<"�Һ��ӽڵ���ţ� "<<ht[i].rchild<<" "<<endl;
    }

}

//�����Ҷ�ӽڵ�ı���
void Encoding(huffmantree ht,int i){
    if(ht[i].parent==0){
        return;
    }
    else{
        Encoding(ht,ht[i].parent);
    }
    cout<<ht[i].code;


}
//���Ҷ�ӽڵ�ı���
void huffmantreeEncoding(huffmantree ht){
  //  freopen("b.txt","w",stdout);
    for(int i=1;i<=num;i++){  //ֻ���ǰnum,��Ҷ�ӽڵ�ı���
        if(ht[i].lchild==0&&ht[i].rchild==0) //����ýڵ�ΪҶ�ӽڵ�
        {
           // char ch;

            cout<<ht[i].c<<" Ȩֵ:";
            printf("%d��",ht[i].weight);
            cout<<"���룺";
            Encoding(ht,i);    //�õݹ�����ýڵ�ı���
            printf("\n");
        }
    }
}
//��ԭ�Ľ��б��룬����b��
void  trans(huffmantree ht){
    FILE *fi=freopen("a.txt","r",stdin);
    FILE *fo=freopen("b.txt","w",stdout);
   gets(s);                //gets()����ʱ�ո�Ҳ���룬ֱ�������ظ��
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

//��Haffman����b�����Ľ������룬��������ļ�c�У�
//�Ƚ�a,c�Ƿ�һ�£��Լ�����롢�������ȷ�ԡ�
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
     while(b[j]!='\0'){    //�����ַ�����/���봮
      if(b[j]=='0')
        i=ht[i].lchild;   //��������
      else if(b[j]=='1')
        i=ht[i].rchild;    //�����Һ���
      //if(b[j]<'a'||b[j]>'z'){
      else{
        printf("%c",b[j]);    //Ϊʲô������cout
        //cout<<b[j];
      }
      if(ht[i].lchild==0){   //���Ƿ�ýڵ�ΪҶ�ӽڵ�
        printf("%c",ht[i].c);//�ǵĻ�����������ظ��ڵ�
        i=m;
      }
      j++;   //�����Ƿ��ҵ�Ҷ�ӽڵ㶼��ȡ��һ�����봮�ַ�
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
    //wpl����������Ҷ���Ĵ�Ȩ·������֮�ͣ���Ϊ���Ĵ�Ȩ·�����ȱ�ʾΪWPL��
    //WPL=(W1*L1+W2*L2+W3*L3+...+Wn*Ln)
    //N��ȨֵWi(i=1,2,...n)����һ����N��Ҷ���Ķ���������Ӧ��Ҷ����·������ΪLi(i=1,2,...n)������֤������������WPL����С�ġ�
    //WPL�Ǻ���һ����Ȩ���������ӵĹؼ���
    //������Σ�����n����Ȩ�ڵ㣬�ܿ�����������ΪҶ�ڵ㹹���һ����СWPLֵ����������������������Ķ�����Ϊ����������
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
