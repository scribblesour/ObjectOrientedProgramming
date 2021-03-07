// rec01-start.cpp
// 2124 21S
// David Chang


#include <iostream>    // Tasks 3, 4, 5 and 6
#include <fstream>     // Task 4, 5 and 6
#include <string>      // Task 5
using namespace std;

int main() {

    // Task 3
    cout << "Task 3\n========\n";
    cout << "This is my first line of C++!\n";
    cout << "Yay for C++!\n";
    // End Task 3
    cout << "\n------------\n" << endl;



    // Task 4
    cout << "Task 4\n========\n";
    ifstream ifs("integers.txt");
    if (!ifs){
      cerr << "Could not open the file! \n";
      exit(1);
    }
    int i;
    int sum = 0;
    //ifs >> i;
    //cout << i << "\n";
    while (ifs >> i) {
      sum = sum + i;
    }
    cout << sum << endl;
    ifs.close();
    // End Task 4
    cout << "\n------------\n" << endl;






    // Task 5
    cout << "Task 5\n========\n";
    ifstream stringstream("text.txt");
    if (!stringstream){
      cerr << "Could not open the file! \n";
      exit(1);
    }
    string in;
    while (stringstream >> in){
      cout << in << endl;
    }
    stringstream.close();
    // End Task 5
    cout << "\n------------\n" << endl;





    // Task 6
    cout << "Task 6\n========\n";
    ifstream mixedstream("mixed.txt");
    if (!mixedstream){
      cerr << "Could not open the file! \n";
      exit(1);
    }
    int x;
    int total = 0;
    while (mixedstream >> x){
      total = total + x;
    }
    cout << total << endl;
    mixedstream.close();
    cout << "\n------------\n" << endl;
}

