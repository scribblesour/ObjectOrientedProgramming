#include <iostream>
using namespace std;

int main2() {
  cout << "This is my first line of C++!\n";
  int x = 1;
  cout << "The variable x has the number " << x << "\n";

  string name;
  cout << "What is your name? \n";
  name = "David";
  cout << "This was written by " << name + "\n";
  cout << "\n\n";

  cout << "writing some loops\n";
  for (int i = 0; i < 10; ++i){
    cout << i;
  }
}
