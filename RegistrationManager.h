#ifndef REGISTRATIONMANAGER_H
#define REGISTRATIONMANAGER_H
#include <string>
#include "Records.h"
#include "DoublyLinkedList.h"
#include "HashTable.h"
using namespace std;
//the main algorithm 
class Studentindexnode//node used in hash table .use studentID as key to find CourseSelection
{
private:
  string studentID;
  string courseCode;
  CourseSelection* csptr;
public:
  Studentindexnode():csptr(0){}
  Studentindexnode(string id,string code,CourseSelection* cs)
  :studentID(id), courseCode(code),csptr(cs){}
  Studentindexnode(string id,string code)
  :studentID(id), courseCode(code),csptr(0){}
  
  string getStudentID()const{return studentID;}
  CourseSelection* getptr()const{return csptr;}
  string getCourseCode()const{return courseCode;}
  
  void setptr(CourseSelection* cs){csptr=cs;}
  void setStudentID(string id){studentID=id;}
  void setCourseCode(string code){courseCode=code;}
  
  bool operator<(const Studentindexnode& stu){
    return this->studentID < stu.getStudentID();
  }
  bool operator>(const Studentindexnode& stu){
    return this->studentID > stu.getStudentID();
  }
  bool operator==(const Studentindexnode& stu) {
  return this->studentID == stu.getStudentID();
}
  bool operator==(const string str) {
  return this->studentID == str;
}

static int StudentIDHash(string ID){//calculate the key
  int sum = 0;
  std::stringstream ss;
  for (int i = 0; i < STUDENT_ID_LENGTH; i++){
    ss << ID[i];
    int number;
    ss >> number;
    ss.clear();
    for (int j = 0; j < i; j++) {
      number = (number % STUDENT_ID_M) * (STUDENT_ID_B % STUDENT_ID_M);
    }
    sum += number;
  }
  return sum % STUDENT_ID_M;
}
static int Hash(const Studentindexnode& stu){//calculate the key
  return StudentIDHash(stu.getStudentID());
}
static int Hash(const Studentindexnode& stu, const string& ID) {//calculate the key
  return StudentIDHash(ID);
}
};


class Courseindexnode//node used in hash table. use CourseCode as key to find CourseSelection
{
private:
  string studentID;
  string courseCode;
  CourseSelection* csptr;
public:
  Courseindexnode():csptr(0){}
  Courseindexnode(string id,string code,CourseSelection* cs)
  :studentID(id), courseCode(code),csptr(cs){}
  Courseindexnode(string id,string code)
  :studentID(id), courseCode(code),csptr(0){}
  string getStudentID()const{return studentID;}
  CourseSelection* getptr()const{return csptr;}
  string getCourseCode()const{return courseCode;}
  
  void setptr(CourseSelection* cs){csptr=cs;}
  void setStudentID(string id){studentID=id;}
  void setCourseCode(string code){courseCode=code;}
  
  bool operator<(const  Courseindexnode& cou){
    return this->courseCode < cou.getCourseCode();
  }
  bool operator>(const  Courseindexnode& cou){
    return this->courseCode > cou.getCourseCode();
  }
  bool operator==(const  Courseindexnode& cou) {
  return this->courseCode == cou.getCourseCode();
}
  bool operator==(const  string str) {
  return this->courseCode == str;
}
static int ChartoNumber(char a) {//change char to int
  int number = (int) a;
  if (number >= 48 && number <= 57) {
    return (number - 48);
  }
  else if(number >= 65 && number <= 90) {
    return (number - 65 + 11);
  }
  else {
    return -1;
  }
}
static int CourseCodeHash(string code) {//calculate the key
  int length = code.length();
  int sum = 0;
  for (int i = 0; i < length; i++) {
    int number = ChartoNumber(code[i]);
    for(int j = 0; j < i; j++) {
      number = (number% COURSECODE_M) * (COURSECODE_B% COURSECODE_M);
    }
    sum += number;
  }
  return sum % COURSECODE_M;
}
static int Hash(const Courseindexnode& course) {//calculate the key
  return CourseCodeHash(course.getCourseCode());
}
static int Hash(const Courseindexnode& course,const string& code) {//calculate the key
  return CourseCodeHash(code);
}
};

class RegistrationManager 
{
public:
  RegistrationManager();
  ~RegistrationManager ();
  void clear();
  
   bool isStudentExist(string);//use key check whether student exist
   bool newStudent(Student&);//insert new student
   bool modifyStudent(Student&,string,int,int);//use key to modify
   Student& searchStudent(string);//search by key and return reference
   bool deleteStudent(string);//use key to delete
   
   bool isCourseExist(string);//use key check whether course exist
   bool newCourse(Course&);//insert new course
   Course& searchCourse(string);//search by key and return reference
   bool modifyCourse(Course&,string,int);//use key to modify
   bool isCourseEmpty(string);
   bool deleteCourse(string);//use key to delete
   
   bool isRegistExist(string,string);//use key check whether regist exist
   bool newRegist(CourseSelection&);//insert new regist
   bool deleteRegist(string,string);//use key to delete
   CourseSelection& searchRegist(string,string);//search by key and return reference
   
   bool deleteRegistinstu(string,string);
   //delete regist in hashtable whose key is student 
   bool deleteRegistincou(string,string);
   //delete regist in hashtable whose key is course
  
   DoublyLinkedList<Student> getallstudents();
   DoublyLinkedList<Course> getallcourses();
   DoublyLinkedList<CourseSelection> getcsbystu(string);
   //return one student all regist 
   DoublyLinkedList<CourseSelection> getcsbycou(string);
   //return one course all regist 
   DoublyLinkedList<CourseSelection> getallcs();
   //return all regist 
   
private:
  HashTable<Student>*  studenttable;
  HashTable<Course>*  coursetable;
  HashTable<Studentindexnode>*  studentselect;
  //use studentID as key to find CourseSelection
  HashTable<Courseindexnode>*  courseselect;
  //use CourseCode as key to find CourseSelection
  DoublyLinkedList<CourseSelection>* registration;
  //store all regists
};


#endif

