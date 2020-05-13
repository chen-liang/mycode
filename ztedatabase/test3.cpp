#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>


using namespace std;


int main() {
    string raw_data("3, 4, 5, 76"), tmp;
    vector<int> data;
    stringstream input(raw_data);

    while (getline(input, tmp, ',')) 
        {
            data.push_back(stoi(tmp));
        }
    return 0;
}