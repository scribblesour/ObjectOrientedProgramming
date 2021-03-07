//Homework 01 - Caesar Cipher
//written by David Chang
//Program written to decrypt a caesar cipher printed backwards
//given a shift distance.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

char decryptChar(char& x, int rot);
string decryptString(string& str,int rot);

//Function instantiates a file stream object and reads the lines into a vector of
//strings. Upon completion, the vector is traversed backwards to print out a 
//decrypted version.
int main() {
  ifstream reader("encrypted.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
    }
  int shift;
  string line;
  vector<string> lines;
  reader >> shift;
  while(getline(reader,line)){
    lines.push_back(line);
  }
  reader.close();
  for(size_t index= lines.size()-1;index > 0; --index){
    cout << decryptString(lines[index], shift) << endl;
  }
}

//Function takes string as input and calls decryptChar on each 
//character individually, and returns it.
string decryptString(string& str,int rot){
  for(int index = 0; index < str.length();++index){
    str[index] = decryptChar(str[index], rot);
  }
  return str;
}

//Function takes characters as input and shifts the character backwards by 'rot' amount.
//Function correctly takes account for the cases where the alphabet wraps around from 
//a to z (and vice versa).
char decryptChar(char& x, int rot){
  //Test if lowercase.
  if(x >= 'a' && x <= 'z'){
    x = x-(rot%26);
    if(x > 'z'){
      x = x-26;
    }
    else if(x < 'a'){
      x = x+26;
    }
  }
  return x;
}
