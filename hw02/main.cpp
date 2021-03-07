//David Chang
//02/17/2021
//CS-2124
//Program simulates battle between Warriors defined in the structure.
//Series of commands is submitted through a file to create new Warriors
//and have them fight.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Warrior structure holds strength of Warrior and its name.
struct Warrior{
  string name;
  int strength;
};

void status(const vector<Warrior>&);
void battle(Warrior&, Warrior&, vector<Warrior>&);
void createWarrior(string, int, vector<Warrior>&);
size_t findWarrior(vector<Warrior>&, string);

//Main function reads through the input file for commands and
//calls the respective functions in each scenario.
int main() {
  //reader checks if file is valid
  ifstream reader("warriors.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
    }
  vector<Warrior> fighters;
  string command;
  //reads commands on each line.
  while(reader >> command){
    if(command == "Warrior"){
      string name;
      int strength;
      //reads associated name and strength
      reader >> name;
      reader >> strength;
      createWarrior(name, strength, fighters);
    }
    else if(command == "Battle"){
      string name_one,name_two;
      //reads first and second Warriors.
      reader >> name_one;
      reader >> name_two;
      size_t index_one = findWarrior(fighters, name_one);
      size_t index_two = findWarrior(fighters, name_two);
      battle(fighters[index_one], fighters[index_two], fighters);
    }
    else if(command == "Status"){
      status(fighters);
    }
  }
  reader.close();
}

//createWarrior function initializes a new structure and pushes it to
//the fighters vector which holds every Warrior created.
void createWarrior(string new_name, int new_strength, vector<Warrior>& fighters){
  Warrior newWarrior;
  newWarrior.name = new_name;
  newWarrior.strength = new_strength;
  fighters.push_back(newWarrior);
}

//status command prints the status of all Warriors into console.
void status(const vector<Warrior>& fighters){
  cout << "There are " << fighters.size() << " warriors." << endl;
  for(size_t index = 0; index < fighters.size(); ++index){
    cout << "Warrior: " << fighters[index].name 
    << ", strength: " << fighters[index].strength << endl;
  }
}

//Battle betwen two Warrior structures compares their strengths to each
//other. The one with the lowest strength loses and the winner loses
//the other's amount in strength.
void battle(Warrior& first, Warrior& second, vector<Warrior>& fighters){
  cout << first.name << " battles " << second.name << endl;
  //checks if they have the same strength
    if (first.strength == 0 && second.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (first.strength == 0){
        cout << "He's dead, " << second.name << endl;
    }
    else if (second.strength == 0){
        cout << "He's dead, " << first.name << endl;
    }
    else if (first.strength == second.strength){
        first.strength = 0;
        second.strength = 0;
        cout << "Mutual Annihilation: " << first.name << " and " 
        << second.name << " die at each other's hands" << endl;
    }
    else if (first.strength > second.strength){
        first.strength -= second.strength;
        second.strength = 0;
        cout << first.name << " defeats " << second.name << endl;
    }
    else if (first.strength < second.strength){
        second.strength -= first.strength;
        first.strength = 0;
        cout << second.name << " defeats " << first.name << endl;
    }
}
//Find Warrior function helps to return the index of the Warrior in the
//fighters array to look up certain Warriors for actions on them.
size_t findWarrior(vector<Warrior>& fighters, string findName){
  for(size_t index = 0; index < fighters.size();++index){
    if(fighters[index].name == findName){
      return index;
    }
  }
  return fighters.size();
}
