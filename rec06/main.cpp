/**
David Chang
rec06.cpp
5 March 2021
Lab to demonstrate copy control, pointers.
**/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Section class holds vector of student records.
class Section{
  //operator << override to print class.
  friend ostream& operator<<(ostream& os, const Section& sec){
    os << "Section: " << sec.name << ", ";
    os << "Time slot: " << sec.time;
    for(size_t index = 0; index < sec.records.size();index++){
      os << *sec.records[index] << endl;
    }
    return os;
  }
  public:
    Section(const string& secname, const string& dow, const int twenty_four_time): time(twenty_four_time,dow), name(secname){}
    //Student Record class to hold grades.
    class Student_Record{
        friend ostream& operator<<(ostream& os, const Student_Record& stu){
          os << "Name: " << stu.studentname;
          os << ", Grades: ";
          for(size_t index = 0; index < 14; ++index){
            os << stu.grades[index] << " ";
          }
          return os;
        }
        public:
          Student_Record(const string& name): studentname(name){
            for(size_t ind = 0;ind < 14; ++ind){
              grades.push_back(-1);
            }
          }
          //Get method for name of student.
          const string& getName() const{
            return studentname;
          }
          //Change grades method to change grade at specific week.
          void changeGrades(int week, int grade){
            grades[week] = grade;
          }
        private:
          string studentname;
          vector<int> grades;
    };
    //Add student method creates a new student on the heap and pushes
    //onto vector of other student pointers.
    void addStudent(const string& stuname){
      Student_Record* rec = new Student_Record(stuname);
      records.push_back(rec);
    }
    //organizing function for changing grades of a specific student.
    void editGrade(const string& name,const int score, const int week){
      size_t index = searchName(name);
      records[index]->changeGrades(week, score);
    }
  //Copy constructor to make sure enough space is allocated.
  //Constructor instantiates primatives.
  Section(const Section& section): name(section.name), time(section.time){
    //this section makes sure theres new pointers pointing to different
    //places on the heap.
    for(Student_Record* i : section.records){
      records.push_back(new Student_Record(*i));
    }
  }
  //deconstructor for section.
  ~Section(){
    cout << "Section " << name << " is being deleted." << endl;
    for(size_t index = 0; index < records.size(); index++){
      //clears the heap using the vector.
      cout << "Deleting " << records[index]->getName() << endl;
      delete records[index];
    }
  }
  private:
    //Timeslot method keeps track of the time for each section.
    class Timeslot{
      //overload << function to print class.
      friend ostream& operator<<(ostream& os, const Timeslot& timeslot){
        os << "[Day: " << timeslot.dayofweek << ", ";
        os << "Start time: " << timeslot.time << timeslot.timeofday << "]" << endl;
        return os;
      }
      public:
        Timeslot(const size_t milTime, const string& dow): time(milTime), dayofweek(dow){
          if(time > 12){
            timeofday = "pm";
            time = time%12;
          }
          else{
            timeofday = "am";
          }
        }

      private:
        size_t time;
        string dayofweek;
        string timeofday;
    };
    //search name function to return the index of the student in the
    //vector.
    size_t searchName(const string& name){
      for(size_t index = 0; index < records.size(); ++index){
        if(records[index]->getName() == name){
          return index;
        }
      }
      return records.size();
    }
    
    Timeslot time;
    const string name;
    vector<Student_Record*> records;
};

//Labworker class calls methods to get specific section data.
class LabWorker{
  //overloads << operator to print class.
  friend ostream& operator<<(ostream& os, const LabWorker& person){
    if(person.teachingsection){
      os << person.name << " has " << *person.teachingsection;
    }
    else{
      os << person.name << " does not have a section.";
    }
    return os;
  }
  public:
    LabWorker(const string& workerName): name(workerName), teachingsection(nullptr) {}
    //sets the section variable of the labworker to sec.
    void addSection(Section& sec){
      teachingsection = &sec;
    }
    //resets the section variable to null.
    void removeSection(){
      teachingsection = nullptr;
    }
    //calls operation in the section.
    void addGrade(const string& name,const int score, const int week){
      teachingsection->editGrade(name,score,week);
    }
  private:
    string name;
    Section* teachingsection;
};

// Test code
void doNothing(Section sec) { 
    cout << sec << endl;;
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works properly, i.e. no memory leaks\n";
    //doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
