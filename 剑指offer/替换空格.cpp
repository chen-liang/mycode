#include<iostream>
using namespace std;
int main()
{

int length=13;
char str1[length];
char *str="We Are Happy";

for(int i=0;i<length;++i)
{
    if(str[i]==' ')
    {
        str[i]='0';
    }
    length+=2;
}



return 0;
}