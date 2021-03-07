// rec01-start.cpp
// 2124 21S
// David Chang
// Function written to simulate Conway's Game of life

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


int checklive(size_t i,size_t j, const vector<string>& lines);
void printgrid(const vector<string>& lines);
vector<string> computeNext(const vector<string>& lines,int lineLen);
void initialize(ifstream& strm,vector<string>& inivector);

int main() {
  //main function initializes file. Reads lines, formats, and passes vector to
  //computeNext().

  //checks for errors when opening the file. Initalizes vector.
  ifstream reader("life.txt");
  vector<string> lines;
  if(!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  initialize(reader, lines);
  reader.close();

  //initializes the first generation in the sequence as 'newvec' and computes it.
  //passes by constant reference to computeNext() which calculates sequential gens.
  vector<string> newvec;
  newvec = computeNext(lines, lines[0].length());
  for(int i = 0; i < 9; ++i){
    cout << "generation" << i+1 << endl;
    newvec = computeNext(newvec, lines[0].length());
    
  }
  cout << "generation" << "10" << endl;

  //code segment prints out final generation (10th)
  cout << "final output below" << endl;
  for(size_t i = 1; i < newvec.size()-1; ++i){
    for(size_t j = 1; j < newvec[i].size()-1; ++j){
      cout << newvec[i][j] << ' ';
    }
    cout << endl;
  }
}

void initialize(ifstream& strm,vector<string>& lines){
  //this block of code puts in the top border and reads the length of the lines.
  string line;
  getline(strm,line);
  int length = line.length();
  string border;
  for(int i = 0; i < length+2; ++i){
    border = border + "0";
  }
  lines.push_back(border);
  lines.push_back("0"+line+"0");
  //this block of code reads the rest of the file
  while(getline(strm,line)){
    lines.push_back("0"+line+"0");
  }
  lines.push_back(border);
}

int checklive(size_t i,size_t j,const vector<string>& lines){
  //boolean function tests any given point (i,j) in vector of strings 'lines' if
  //it is eligible to survive to the next generation.
  int peoplect = 0;
  if (lines[i-1][j-1] == '*'){
    ++peoplect;
  }
  if (lines[i-1][j] == '*'){
    ++peoplect;
  }
  if (lines[i-1][j+1] == '*'){
    ++peoplect;
  }


  if (lines[i][j-1] == '*'){
    ++peoplect;
  }
  if (lines[i][j+1] == '*'){
    ++peoplect;
  }



  if (lines[i+1][j-1] == '*'){
    ++peoplect;
  }
  if (lines[i+1][j] == '*'){
    ++peoplect;
  }
  if (lines[i+1][j+1] == '*'){
    ++peoplect;
  }
  return peoplect;
}
void printgrid(const vector<string>& vec){
  //function serves to print out the entire vector including borders
  for(size_t i = 0; i < vec.size(); ++i){
    for(size_t j = 0; j < vec[i].size(); ++j){
      cout << vec[i][j] << ' ';
    }
    cout << endl;
  }
}
vector<string> computeNext(const vector<string>& formattedvec,int lineLen){
  //given input of formatted string vector. It computes, formats, and returns
  //the next generation.
  vector<string> returnvec;
  string border;
  for(int i = 0; i < lineLen; ++i){
    border = border + "0";
  }
  returnvec.push_back(border);
  for (size_t a = 1; a<formattedvec.size()-1;++a){
    string newLine = "";
    for (size_t b = 1;b<formattedvec[a].size()-1;++b){
        int people = checklive(a, b, formattedvec);
        if (formattedvec[a][b] == '*'&& people >= 2 && people <= 3){
          newLine = newLine + '*';
        }
        else if(formattedvec[a][b] == '-' && people == 3){
          newLine = newLine + "*";
        }
        else{
          newLine = newLine + '-';
        }
    }
    returnvec.push_back("0"+newLine+"0");
  }
  returnvec.push_back(border);
  printgrid(returnvec);
  return returnvec;
}
