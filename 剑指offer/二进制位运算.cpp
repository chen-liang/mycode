class Solution {
public:
     int  NumberOf1(int n)
     {
         int count=0;
         while(n!=0)
         {
             ++count;
             n=n&(n-1);
         }
        /**
        for(int i=0;n!=0;++i)
        {
            n=n&(n-1);
        }
        return i;
        **/
        
     }    
};
