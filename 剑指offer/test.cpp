#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> // 用于读写存储在内存中的string对象
using namespace std;
int main(void)
{
    // 制作CSV文件
    /* Name,age,height
     * Tom,21,172.8
     * John,25,189.5
     */
     //ofstream outFile;
     //outFile.open("./input1.csv", ios::out);
     //outFile << "Name" << "," << "age" << "," << "height" << endl;
     //outFile << "Tom" << "," << 21 << "," << 172.8 << endl;
     //outFile << "John" << "," << 25 << "," << 189.5 << endl;
    // outFile.close();

     // 读取CSV文件
     struct CSVDATA {
      int id1;
      int id2;
      int id3;
     };
     ifstream inFile("./input1.csv", ios::in);
     string lineStr;
     vector<struct CSVDATA> csvData;
     getline(inFile, lineStr); // 跳过第一行(非数据区域)
     while (getline(inFile, lineStr)) {
          stringstream ss(lineStr); // string数据流化
          string str;
          struct CSVDATA csvdata;
          getline(ss, str, ','); // 获取 Name
          csvdata.id1 = stod(str);
          getline(ss, str, ','); // 获取 age
          csvdata.id2 = stoi(str);
          getline(ss, str, ','); // 获取 height
          csvdata.id3 = stod(str);

          csvData.push_back(csvdata);
     }
     // 显示读取的数据
     for (int i = 0; i < csvData.size(); i++ ) {
        cout << csvData[i].id1 << "," << csvData[i].id2 << "," << csvData[i].id3 << endl;
     }
     return 0;    
}