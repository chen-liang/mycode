/*
定义栈的数据结构，
请在该类型中实现一个能够得到栈中所含最小元素的min函数
（时间复杂度应为O（1））。
*/
#include<stack>
using namespace std;
class Solution {
public:
    void push(int value) {
        s.push(value);
        if(smin.empty()) smin.push(value);
        else if(value<=smin.top()) smin.push(value);
    }
    void pop() {
        if(s.empty()) return;
        if(s.top()==smin.top()) smin.pop();
        s.pop();
    }
    int top() {
        return s.top();
    }
    int min() {
        return smin.top();
    }
private:
    stack<int> s,smin;
};
