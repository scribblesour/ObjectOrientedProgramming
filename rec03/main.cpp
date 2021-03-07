// rec02.cpp
// 2124 21S
// David Chang
// Function reads a file of hydrocarbons and sorts the amount of molecules
// and attaches names to each of them.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Hydrocarbon Structure stores amount of hydrogens and carbons in compound along
//with the names associated with it.
struct HydroCarbon{
  int hydrogens,carbons;
  vector<string> names;
};

void askReader(ifstream& reader);
void printHydroCarbon(const HydroCarbon& hydcbn);
void readFile(ifstream& reader, vector<HydroCarbon>& allCompounds);
size_t containsCompound(int carbs,int hydros,  vector<HydroCarbon>& all);
void sortCompounds(vector<HydroCarbon>& all);
void printCompounds(const vector<HydroCarbon>& all);
void addToVector(string currName,int currCarbon,int currHydrogen,
          vector<HydroCarbon>& allCompounds);


//Main function organizes function calls.
int main() {
  ifstream reader;
  askReader(reader);
  vector<HydroCarbon> allCompounds;
  readFile(reader,allCompounds);
  reader.close();
  sortCompounds(allCompounds);
  printCompounds(allCompounds);
}

//AskReader function will persistantly ask the user to input a local filename 
//containing the compounds and their names.
void askReader(ifstream& reader){
  string filename;
  do{
    cout << "What is the file of the hydrocarbons called?" << endl;
    cin >> filename;
    reader.open(filename);
  }
  while(!reader);
  cout << "File successfully opened!" << endl << endl << endl;
}
//printHydroCarbon formats a HydroCarbon structure and outputs string with associated
//names.
void printHydroCarbon(const HydroCarbon& hydcbn){
  cout << "C" << hydcbn.carbons << "H" << hydcbn.hydrogens << " ";
  for (size_t index = 0; index < hydcbn.names.size();++index){
    cout << hydcbn.names[index] << " ";
  }
  cout << endl;
}

//printCompounds calls printHydroCarbon() on all structures in the allCompounds 
//vector.
void printCompounds(const vector<HydroCarbon>& all){
  for(size_t index = 0; index < all.size();++index){
    printHydroCarbon(all[index]);
  }
}

//readFile() takes input from the filestream and inputs it into the allCompounds
//vector.
void readFile(ifstream& reader, vector<HydroCarbon>& allCompounds){
  string currName;
  int currCarbon,currHydrogen;
  char blank;
  while(reader >> currName >> blank >> currCarbon >> blank >> currHydrogen){
    addToVector(currName, currCarbon, currHydrogen, allCompounds);
  }
}

//addToVector() function adds values given from readFile() to add to the 
//allCompounds vector.
void addToVector(string currName,int currCarbon,int currHydrogen,
          vector<HydroCarbon>& allCompounds){
    int found = containsCompound(currCarbon, currHydrogen, allCompounds);

    if(found == -1){
      HydroCarbon newHC;
      newHC.carbons = currCarbon;
      newHC.hydrogens = currHydrogen;
      newHC.names.push_back(currName);
      allCompounds.push_back(newHC);
    }
    else{
      allCompounds[found].names.push_back(currName);
    }
}

//containsCompound() checks if a compound is already in the vector. In this case,
//the name is appended to the associated compound instead of creating a new one.
size_t containsCompound(int carbs,int hydros,  vector<HydroCarbon>& all){
  for(size_t index = 0; index < all.size();++index){
    if(all[index].carbons == carbs && all[index].hydrogens == hydros){
      return index;
    }
  }
  return all.size();
}

//sortCompounds utilizes seleciton sort algorithm to sort the compounds in 
//allCompounds using the # of Carbons in ascending order. If two have the same,
//the # of Hydrogens is used.
void sortCompounds(vector<HydroCarbon>& all){
  size_t curr = 0;
  while(curr != all.size()){
    int indSmallest = curr;
    for(size_t index = curr+1; index < all.size(); ++index){
      if ((all[index].carbons < all[indSmallest].carbons) || 
        (all[index].carbons == all[indSmallest].carbons &&
          all[index].hydrogens < all[indSmallest].hydrogens)){
        indSmallest = index;
      }
    }
    HydroCarbon temp = all[curr];
    all[curr] = all[indSmallest];
    all[indSmallest] = temp;
    ++curr;
  }
}
