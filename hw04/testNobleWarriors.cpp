/*
  hw04.cpp
  David Chang
  Warrior and Noble classes defined to comply with programming prompt.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Warrior Class holds strength and occupation status.
class Warrior{
  // << operator overload to return stream with Warrior data.
  friend ostream& operator<<(ostream& os, const Warrior& warrior){
    os << warrior.name << ": " << warrior.strength << endl;
    return os;
  }
  public:
    //Warrior Constructor takes name and strength.
    Warrior(const string& newName, double str) : name(newName), strength(str), alive(true), hired(false){}

    //Get method for status of Warrior
    bool getLife() const{
      return alive;
    }

    //Changes the status of Warrior.
    void die(){
      alive = !alive;
    }

    //Get method for the occupation status of Warrior.
    bool getHired() const{
      return hired;
    }

    //Changes the occupation status of Warrior.
    void flipHired(){
      hired = !hired;
    }

    //Get method for strength of Warrior
    const double getStrength() const{
      return strength;
    }

    //Changes the strength of the Warrior based on a ratio passed in.
    void setStrength(double ratio){
      if(ratio == 0.0){
        strength = 0.0;
      }
      else{
        strength = strength-strength*ratio;
      }
    }

  private:
    string name;
    bool alive;
    double strength;
    bool hired;
};

//Noble class holds vector of pointers to hired Warriors.
class Noble {
  // << overload to print values of Noble class.
  friend ostream& operator<<(ostream& os, const Noble& noble){
    os << noble.name << " has an army of " << noble.fighters.size() << endl;
    for(size_t index = 0; index < noble.fighters.size(); index++){
      os << "   " << *noble.fighters[index];
    }
    return os;
  }
  public:
    Noble(const string& newName) :  name(newName), alive(true) {}
    //Hire method for Noble class adds address of Warrior to vector.
    const bool hire(Warrior& warrior) {
      if(alive && warrior.getLife() && !warrior.getHired()){
        fighters.push_back(&warrior);
        warrior.flipHired();
        return true;
      }
      return false;
    }
    //Fire method removes Warrior from vector of pointers and changes
    //Warrior occupation status.
    const bool fire(Warrior& warrior){
      size_t indexOfWarrior = findWarrior(warrior);
      //fighters[indexOfWarrior]->flipHired();
      warrior.flipHired();
      return removeWarrior(indexOfWarrior);
    }

    //Battle method puts Nobles against each other and calculates the
    //comparative strengths between them.
    const bool battle(Noble& secondNoble){
      cout << name << " battles " << secondNoble.name << endl;
      //Easiest case tests if both are already dead.
      if(alive == false && secondNoble.alive == false){
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        return false;
      }
      double selfPower = getPower();
      double secondPower = secondNoble.getPower();
      //check if powers are the same. If true, both die.
      if(selfPower == secondPower){
        cout << "Mutual Annihalation: " << name << " and " << secondNoble.name << " die at each other's hands." << endl;
        alive = false;
        secondNoble.alive = false;
        damageWarriors(0.0);
        secondNoble.damageWarriors(0.0);
        return true;
      }
      //check if the second noble is already dead.
      else if(!secondNoble.alive){
        cout << "He's dead, " << name << endl;
      }
      //check if first noble's power is greater than the second.
      else if(selfPower > secondPower){
        double ratio = secondPower/selfPower;
        secondNoble.alive = false;
        secondNoble.damageWarriors(0.0);
        damageWarriors(ratio);
        cout << name << " defeats " << secondNoble.name << endl;
        return true;
      }
      //check if the second noble's power is greater the first.
      else if(secondPower > selfPower){
        double ratio = selfPower/secondPower;
        alive = false;
        damageWarriors(0.0);
        secondNoble.damageWarriors(ratio);
        cout << secondNoble.name << " defeats " << name << endl;
        return true;
      }
      return false;
    }

  private:
    //Reduces the strength of the warriors in the vector by a ratio.
    void damageWarriors(double ratio) const{
      for(size_t index = 0; index < fighters.size(); ++index){
        fighters[index]->setStrength(ratio);
        if(ratio == 0.0){
          fighters[index]->die();
        }
      }
    }
    //Returns the index of the warrior in vector.
    size_t findWarrior(const Warrior& warrior) const{
      for(size_t index = 0; index < fighters.size(); ++index){
        if(fighters[index]==&warrior){
          return index;
        }
      }
      return fighters.size();
    }
    //removes the warrior pointer from the vector. Shifts all remaining
    //Warriors down..
    bool removeWarrior(size_t indToRemove){
      if(indToRemove< fighters.size() && 0 <= indToRemove){
        for(size_t index = indToRemove; indToRemove<fighters.size()-1; 
        index++){
          fighters[index] = fighters[index+1];
        }
        fighters.pop_back();
        return true;
      }
      return false;
    }
    //Get method for combined power of the Warriors in the vector.
    double getPower() const{
      double power = 0;
      for(size_t index = 0; index < fighters.size(); ++index){
        power += fighters[index]->getStrength();
      }
      return power;
    }

    vector<Warrior*> fighters;
    string name;
    bool alive;
};

int main() {
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
	
    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
    art.fire(cheetah);
    cout << art << endl;
	
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
}

