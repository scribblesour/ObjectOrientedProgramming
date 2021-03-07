//hw04.cpp
//David Chang
//File simulates the Warrior class and showcases the use of nested
//classes, encapsulation, and data hiding.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Warrior Class stores one instance of Weapon and a name.
class Warrior{
  //ostream redefinition prints out Warrior class.
  friend ostream& operator<<(ostream& os, const Warrior& warrior){
  os << "Warrior: ";
  os << warrior.name << ", ";
  os << "weapon: ";
  os << warrior.sword;
  return os;
  }
public:
  Warrior(int power, const string& weapon_name, const string& warrior_name) : sword(weapon_name,power), name(warrior_name) {}

  //Get method for name of Warrior
  const string& getName(){
    return name;
  }
  //Get method for strength of Weapon.
  int getStrength(){
    return sword.getStrength();
  }
  //Set method for strength of Weapon.
  void setStrength(int x){
    sword.setStrength(x);
  }
  //status command prints the status and strength of the warrior.
  void status(){
    //cout << *this; //learned it this week in lab so not allowed.
    cout << "Warrior: " << name << ", ";
    cout << "weapon: " << sword;
  }
  //battle method initiates combat between two Warriors and changes their
  //strengths in relation to each other.
  void battle(Warrior& warrior2){
    cout << name << " battles " << warrior2.getName() << endl;
  //checks if they have the same strength
    if (getStrength() == 0 && warrior2.getStrength() == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (getStrength() == 0){
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if (warrior2.getStrength() == 0){
        cout << "He's dead, " << name << endl;
    }
    else if (getStrength() == warrior2.getStrength()){
      setStrength(0);
      warrior2.setStrength(0);
      cout << "Mutual Annihilation: " << name << " and " 
      << warrior2.getName() << " die at each other's hands" << endl;
    }
    else if (getStrength() > warrior2.getStrength()){
      int final = getStrength()-warrior2.getStrength();
      setStrength(final);
      warrior2.setStrength(0);
      cout << name << " defeats " << warrior2.getName() << endl;
    }
    else if (getStrength() < warrior2.getStrength()){
      int final = warrior2.getStrength() - getStrength();
      warrior2.setStrength(final);
      setStrength(0);
      cout << warrior2.getName() << " defeats " << name << endl;
    }
    
  }
private:
  //Weapon class holds the strength of the Warrior.
  class Weapon{
    //Weapon >> operator overload to print class.
    friend ostream& operator<<(ostream& os, const Weapon& weapon){
      os << weapon.name;
      os << " ";
      os << weapon.strength << endl;
      return os;
    }
  public:
    Weapon(const string& weapon_name, int power) : name(weapon_name),strength(power){}
    //Get method for strength.
    int getStrength(){
      return strength;
    }
    //Set method for strength.
    void setStrength(int x){
      strength = x;
    }

  private:
    int strength;
    string name;
  };
  string name;
  Weapon sword;
};

////////
//Main//
////////

//Main function reads warriors.txt and does the subsequent commands.
int main(){
  ifstream reader("warriors.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  vector<Warrior> warriors;
  string command;
  while(reader >> command){
    if(command == "Warrior"){
      string name;
      string weapon_name;
      int str;
      reader >> name >> weapon_name >> str;
      warriors.emplace_back(str,weapon_name,name);
    }
    else if(command == "Status"){
      cout << "There are " << warriors.size() << " warriors." << endl;
      for(size_t index = 0; index < warriors.size();index++){
        warriors[index].status();
      }
    }
    else if(command == "Battle"){
      string name_one, name_two;
      reader >> name_one;
      reader >> name_two;
      size_t index_one,index_two;
      for(size_t index = 0; index < warriors.size(); index++){
        if(warriors[index].getName() == name_one){
          index_one = index;
        }
        else if(warriors[index].getName() == name_two){
          index_two = index;
        }
      }
      warriors[index_one].battle(warriors[index_two]);
    }
  }
  reader.close();
}
