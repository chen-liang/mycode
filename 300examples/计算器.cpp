#include<iostream>
#include<vector>
#include<algorithm>

#include<stdexcept>
//#include<cmath>
using namespace std;
inline void keep_window_open()
{
    char ch;
    cin>>ch;
}
void error(string s)
{
    throw runtime_error(s);
}
class Token
{
    public:
        char kind;
        double value;
        Token(char ch)
            :kind(ch),value(0){};
        Token(char ch,double val)
            :kind(ch),value(val){};
};
class Token_stream
{
    public:
        Token_stream();
        Token get();
        void putback(Token t);
  private:
    bool  full;
    Token  buffer;
};
Token_stream::Token_stream()
  :full(false),buffer(0)
{
}
void  Token_stream::putback(Token  t)
{
  if(full)  error("putback()  into  a  full  buffer");
  buffer=t;
  full=true;
}
Token  Token_stream::get()  //返回值是Token类
{
  if(full)
  {
    full=false;
    return  buffer;
  }
  char  ch;
  cin  >>  ch;  //  note  that  >>  skips  whitespace  (space,  newline,  tab,  etc.)
  switch  (ch)  {
  case  ';':
  case  'q':
  case  '(':  case  ')':  case  '+':  case  '-':  case  '*':  case  '/':  
    return  Token(ch);    //  let  each  character  represent  itself
  case  '.':
  case  '0':  case  '1':  case  '2':  case  '3':  case  '4':
  case  '5':  case  '6':  case  '7':  case  '8':  case  '9':
    {  
      cin.putback(ch);      //  put  digit  back  into  the  input  stream
      double val;
      cin >> val;       //  read  a  floating-point  number
      return Token('8',val);   //  let  '8'  represent  "a  number"
    }
  default:
    error("Bad token");return  0;
  }
}
Token_stream ts;
double expression();
double primary()
{
  Token t=ts.get();
  switch(t.kind)
  {
    case '(':
      {
        double d=expression();
        t=ts.get();
        if(t.kind!=')') error("')'expected");
        return d;
      }
    case '8':return  t.value;
    default :error("primary  expected");return  0;
  }
}
double term()
{
  double left=primary();
  Token t=ts.get();
  while(true)
  {
    switch(t.kind)
    {
      case '*':left*=primary();t=ts.get();break;
      case '/':
      {   double d=primary();
        if(d==0) error("divided  by  zero");
        left/=d;
        t=ts.get();
        break;}
      default :ts.putback(t);return  left;
        
      }
  }
}
double expression()
{
  double left=term();
  Token t=ts.get();
  while(true)
  {
    switch(t.kind)
    {
      case '+':left+=term();t=ts.get();break;
      case '-':left-=term();t=ts.get();break;
      default :ts.putback(t);return left;
    }
  }
}
int  main()
{
  try
  {
    double val=0;
    while(cin)
    {
      Token  t=ts.get();
      if(t.kind=='q') break;
      if(t.kind==';') cout<<"="<<val<<endl;
      else
        ts.putback(t);
        val=expression();   
    }
       //  cout<<"="<<expression()<<endl;
     //  keep_window_open();
  }
  catch(exception&  e)
  {
    cerr <<"error:"<< e.what() << '\n';
    keep_window_open();
    return 1;
  }
  catch(...)
  {
    cerr<<"Opps:unknown exception!\n";
    keep_window_open();
    return 2;
  }
}