#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior{
  friend ostream& operator<<(ostream& os, const Warrior& warrior){
    os << warrior.name << ": " << warrior.strength << endl;
  }
  public:
    Warrior(const string& newName, double str) : name(newName), strength(str), alive(true), hired(false){}

    const bool getLife() const{
      return alive;
    }
    void die(){
      alive = !alive;
    }

    const bool getHired() const{
      return hired;
    }
    void flipHired(){
      hired = !hired;
    }

    const double getStrength() const{
      return strength;
    }
    void setStrength(double ratio){
      strength = strength*ratio;
    }

  private:
    string name;
    bool alive;
    double strength;
    bool hired;
};


class Noble{
  friend ostream& operator<<(ostream& os, const Noble& noble){
    os << noble.name << " has an army of " << noble.fighters.size() << endl;
    for(size_t index = 0; index < noble.fighters.size(); index++){
      os << "   " << *noble.fighters[index] << endl;
    }
  }
  public:
    Noble(const string& newName) :  name(newName), alive(true) {}
    const bool hire(Warrior& warrior){ //ask about const
      if(alive && warrior.getLife() && !warrior.getHired()){
        fighters.push_back(&warrior);
        warrior.flipHired();
        return true;
      }
      else{
        return false;
      }
    }
    const bool fire(Warrior& warrior){
      size_t indexOfWarrior = findWarrior(warrior);
      //fighters[indexOfWarrior]->flipHired();
      warrior.flipHired();
      return removeWarrior(indexOfWarrior);
    }

    const bool battle(Noble& secondNoble){
      cout << name << " battles " << secondNoble.name << endl;
      if(alive == false && secondNoble.alive == false){
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        return false;
      }
      double selfPower = getPower();
      double secondPower = secondNoble.getPower();
      if(selfPower == secondPower){
        cout << "Mutual Annihalation: " << name << " and " << secondNoble.name << " die at each other's hands." << endl;
        alive = false;
        secondNoble.alive = false;
        damageWarriors(0.0);
        secondNoble.damageWarriors(0.0);
        return true;
      }
      else if(!secondNoble.alive){
        cout << "He's dead, " << name;
      }
      else if(selfPower > secondPower){
        double ratio = secondPower/selfPower;
        secondNoble.alive = false;
        secondNoble.damageWarriors(0.0);
        damageWarriors(ratio);
        cout << name << " defeats " << secondNoble.name << endl;
        return true;
      }
      else if(secondPower > selfPower){
        double ratio = selfPower/secondPower;
        alive = false;
        damageWarriors(0.0);
        secondNoble.damageWarriors(ratio);
        cout << secondNoble.name << " defeats " << name << endl;
        return true;
      }

    }

  private:
    void damageWarriors(double ratio){
      for(size_t index = 0; index < fighters.size(); ++index){
        fighters[index]->setStrength(ratio);
        if(ratio == 0.0){
          fighters[index]->die();
        }
      }
    }

    const size_t findWarrior(Warrior& warrior){
      for(size_t index = 0; index < fighters.size(); ++index){
        if(fighters[index]==&warrior){
          return index;
        }
      }
      return fighters.size();
    }

    const bool removeWarrior(size_t indToRemove){
      if(indToRemove< fighters.size() && 0 <= indToRemove){
        for(size_t index = indToRemove; indToRemove<fighters.size(); index++){
          fighters[index] = fighters[index+1];
        }
        fighters.pop_back();
        return true;
      }
      return false;
    }

    const double getPower(){
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




