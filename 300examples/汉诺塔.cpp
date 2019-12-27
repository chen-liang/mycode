#include<iostream>
using namespace std;
void hanoi(int n,char X,char Y,char Z)
{
    if(n==1) cout<<X<<"->"<<Z<<endl;
    else if(n>=2)
    {
        hanoi(n-1,X,Z,Y);
        cout<<X<<"->"<<Z<<endl;;
        hanoi(n-1,Y,X,Z);
    }
}
int main()
{
    int n=3;
    hanoi(n,'x','y','z');
    return 0;
}