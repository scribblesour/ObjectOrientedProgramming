//David Chang
//rec05.cpp
//Program does tasks to show use of pointers

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//class to demonstrate pointers
struct Complex {
   double real;
   double img;
};

//class to demonstrate pointers
class PlainOldClass {
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
   //void setX( int x )  { x = x; } //uh oh
   void setX( int x )  { this->x = x; } // No confusion!
private:
   int x;
};

//class for Task28
class Colour {  
public:       
    Colour(const string& name, unsigned r, unsigned g, unsigned b)       
        : name(name), r(r), g(g), b(b) {}       
    void display() const { 
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")"; 
    }   
private:       
    string name;      // what we call this colour       
    unsigned r, g, b; // red/green/blue values for displaying  
};  


//task 29 class
class SpeakerSystem {
    public:
    void vibrateSpeakerCones(unsigned signal) const {
      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
  }  
};

//task 29 class Amp class.
class Amplifier {
 public:
   void attachSpeakers(const SpeakerSystem& spkrs)
    {
      if(attachedSpeakers)
         cout << "already have speakers attached!\n";
      else
          attachedSpeakers = &spkrs;
    }
      
    void detachSpeakers() { // should there be an "error" message if no attached?
       attachedSpeakers = nullptr; 
    } 
      
    void playMusic( ) const {
       if (attachedSpeakers)
          attachedSpeakers -> vibrateSpeakerCones(440); 
       else
         cout << "No speakers attached\n"; 
   }
private:
    //types need to be consistant
    const SpeakerSystem* attachedSpeakers = nullptr;
};

//task 30 person class.
class Person {  
public:       
    Person(const string& name) : name(name), roomie(nullptr) {}
    void movesInWith(Person& newRoomate) {
      if(this == &newRoomate){
        cout << "Can not room with yourself." << endl;
      }
      else if(roomie){
        cout << "Already has a roomate!" << endl;
      }
      else if(newRoomate.roomie){
        cout << "That person already has a roommate!" << endl;
      }
      else{
      //test if myself
      //roommate has person already
      //myself and i have a roommate already.
        roomie = &newRoomate;        // now I have a new roomie            
        newRoomate.roomie = this;    // and now they do too      
      } 
    }       
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }  
private:
    Person* roomie;       
    string name;  
};           


//Main function to demonstrate pointers.
int main() {
  int x;  
  x = 10;  
  cout << "x = " << x << endl;


  int* p;  //pointer to an int is stored in p. oreferred syntax
  p = &x;  //p is assigned to an address
  cout << "p = " << p << endl;

  //p = 0x0012fed4; // using the value from my Watch window
  cout << "p points to where " << *p << " is stored\n";  //dereference
  cout << "*p contains " << *p << endl; //dereference: *p

  //we can use the dereferenced address to locate and change the variable
  *p = -2763;  
  cout << "p points to where " << *p << " is stored\n";  
  cout << "*p now contains " << *p << endl;  
  cout << "x now contains " << x << endl;

  //point p->y using the address of y. Then change it to 980.
  int y(13);      
  cout << "y contains " << y << endl;      
  p = &y;      
  cout << "p now points to where " << *p << " is stored\n";      
  cout << "*p now contains " << *p << endl;      
  *p = 980;      
  cout << "p points to where " << *p << " is stored\n";      
  cout << "*p now contains " << *p << endl;      
  cout << "y now contains " << y << endl;

  //q -> p -> y -> 980
  int* q;      
  q = p;      
  cout << "q points to where " << *q << " is stored\n";      
  cout << "*q contains " << *q << endl;

  double d(33.44);      
  double* pD(&d);  //stores address of d in pD    
  *pD = *p;      //contents of pD = contents of p -> y -> 980
  *pD = 73.2343;      //no error, reassigns value to double
  *p  = *pD;      //contents of p = contents of pD 
  *q  = *p;      //contents of q = contents of p
  //pD  = p; error here why? ??
  //p   = pD; error because a int* can not be set to double*

  int joe = 24;  
  const int sal = 19;    
  int*  pI;  
  pI = &joe;  //stores address of joe in pI. same type = works
  *pI = 234;  //works because same type
  //pI = &sal;  doesn't work because different type.
  *pI = 7623; //works because same type.

  const int* pcI;
  pcI = &joe;  //works? ??
  //*pcI = 234;  doesn't work because you can't change constants
  pcI = &sal;  // ??
  //*pcI = 7623;  doesn't work because you can't change constants

  //int* const cpI; ??
  int* const cpI(&joe);
  //int* const cpI(&sal); doesnt work because can not initialize int* const with const int ??
  //cpI = &joe;  ??
  *cpI = 234;  //dereferenced variable cpI changed to 234 sets joe
  //cpI = &sal;  ??
  *cpI = 7623;   //dereferenced variable cpI changed to 234 sets joe

  //const int* const cpcI; requires an initialization address.
  //const int* const cpcI(&joe);
  const int* const cpcI(&sal);
  //cpcI = &joe;  can not reassign constant int*
  //*cpcI = 234;  can not reassign constant dereferenced variable
  //cpcI = &sal;  &sal isnt an address
  //*cpcI = 7623;  can not reassign constant dereferenced variable

  Complex c = {11.23,45.67};      
  Complex* pC(&c); // stores pointer to c

  //doesn't work because the dereference operator has a lower
  //precedence than the * so it does the '.' before the '*'. breaks
  //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;

  //correct
  cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
  //also correct but better.
  cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

  PlainOldClass poc;
  PlainOldClass* ppoc( &poc );
  cout << ppoc->getX() << endl;
  ppoc->setX( 2837 );
  cout << ppoc->getX() << endl;

  int* pDyn = new int(3); // p points to an int initialized to 3 on the heap      
  *pDyn = 17;
  cout << "The " << *pDyn
     << " is stored at address " << pDyn
     << " which is in the heap\n";
  cout << pDyn << endl;  
  delete pDyn;  
  pDyn = nullptr; //normally done to make pDyn not point at anything.
  cout << pDyn << endl;
  cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";  
  //cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

  double* pDouble = nullptr;

  //cout << "Can we dereference nullptr?  " << *pDyn << endl;    
  //crashes because you can not dereference nullptr  
  //cout << "Can we dereference nullptr?  " << *pDouble << endl;

  double* pTest = new double(12);      
  delete pTest;      
  pTest = nullptr;      
  delete pTest; // safe

  short* pShrt = new short(5);      
  delete pShrt;      
  //delete pShrt; free(): double free detected in tcache 2

  long jumper = 12238743;      
  //delete jumper; 
  long* ptrTolong = &jumper;      
  //delete ptrTolong;        
  Complex cmplx;      
  //delete cmplx;

  //delete only works with the heap
  vector<Complex*> complV; // can hold pointers to Complex objects
  Complex* tmpPCmplx;      // space for a Complex pointer
  for (size_t ndx = 0; ndx < 3; ++ndx) {
    tmpPCmplx = new Complex; // create a new Complex object on the heap
    tmpPCmplx->real = ndx;   // set real and img to be the
    tmpPCmplx->img  = ndx;   // value of the current ndx
    complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
  }      
  // display the objects using the pointers stored in the vector
  for (size_t ndx = 0; ndx < 3; ++ndx) {         
      cout << complV[ ndx ]->real << endl;         
      cout << complV[ ndx ]->img  << endl;      
  }      
  // release the heap space pointed at by the pointers in the vector      
  for (size_t ndx = 0; ndx < 3; ++ndx) {         
      delete complV[ndx];
  }      
  // clear the vector does not delete the contents of the vector.
  complV.clear();

  //task 28 colors
  vector<Colour*> colours;         
  string inputName;       
  unsigned inputR, inputG, inputB;
  while (cin >> inputName >> inputR >> inputG >> inputB) {
      colours.push_back(new Colour(inputName, inputR, inputG, inputB));       
  } 
  // display all the Colours in the vector:       
  for (size_t ndx = 0; ndx < colours.size(); ++ndx) {            
      colours[ndx]->display();            
      cout << endl;      
      delete colours[ndx];
      colours[ndx]=nullptr;
  }

  SpeakerSystem spkr;
  Amplifier amp;
  amp.attachSpeakers(spkr);
  amp.playMusic();

  // write code to model two people in this world       
  Person joeBob("Joe Bob"), billyJane("Billy Jane");         

  // now model these two becoming roommates       
  joeBob.movesInWith(billyJane);         

  // did this work out?       
  cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
  cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;



}

