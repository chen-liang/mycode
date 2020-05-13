/*        .与->
1、A.B则A为对象或者结构体；

2、A->B则A为指针，->是成员提取，A->B是提取A中的成员B，A只能是指向类、结构、联合的指针；
*/
#include<iostream>
using namespace std;
class STUDENT
{
    public:
    string name[20];    
};
/*
第一种情况 采用指针访问
STUDENT* xy;
*xy.name="chen"与xy->name="chen"等价

第二种情况 采用普通成员访问
STUDENT xy;
xy.name="chen";
*/