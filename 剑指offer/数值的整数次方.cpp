#include<math.H>
using namespace std;
class Solution {
public:
    double Power(double base, int exponent) {
        return pow(base,exponent);
    }
};
/*
public double Power(double base, int n) {
    double res = 1,curr = base;
    int exponent;
    if(n>0){
        exponent = n;
    }else if(n<0){
        if(base==0)
            throw new RuntimeException("��ĸ����Ϊ0"); 
        exponent = -n;
    }else{// n==0
        return 1;// 0��0�η�
    }
    while(exponent!=0){
        if((exponent&1)==1)
            res*=curr;
        curr*=curr;// ����
        exponent>>=1;// ����һλ
    }
    return n>=0?res:(1/res);       
}
*/