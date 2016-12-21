#include "FileManagement.h"
#include "RegistrationManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::string;

FileManagement::FileManagement():manager(0){}

FileManagement::FileManagement(RegistrationManager* m,string str)
:manager(m),fileName(str){}

int FileManagement::saveData(){
    int size;
    DoublyLinkedList<Student> students=manager->getallstudents();
    typename DoublyLinkedList<Student>::Iterator itrs=students.begin();
    DoublyLinkedList<Course> courses=manager->getallcourses();
    typename DoublyLinkedList<Course>::Iterator itrc=courses.begin();
    DoublyLinkedList<CourseSelection> regists=manager->getallcs();
    typename DoublyLinkedList<CourseSelection>::Iterator itrcs=regists.begin();
    string str= fileName;
    const char *FILE  = str.c_str();
    ofstream fout(FILE);
    if(fout.is_open ()){
    size=students.size();
    fout <<"STUDENT"<< endl;
    fout <<std::to_string(size)<< endl;
    for(int i = 0; i < size; i++, ++itrs) {
      string id=(*itrs).getStudentID();
      string name=(*itrs).getStudentName();
      int year=(*itrs).getYear();
      int gender=(*itrs).getGender();
         fout << id <<endl;
	 fout << name<<endl;
	 fout << std::to_string(year) <<endl;
	 fout << std::to_string(gender) <<endl;
        }
    size=courses.size();
    fout <<"COURSE"<< endl;
    fout <<std::to_string(size)<< endl;    
    for(int i = 0; i < size; i++, ++itrc) {
      string code=(*itrc).getCourseCode();
      string name=(*itrc).getCourseName();
      int credit=(*itrc).getCredit();
         fout << code <<endl;
	 fout << name<<endl;
	 fout << std::to_string(credit)<<endl;
        }
    size=regists.size();
    fout <<"CS"<< endl;
    fout <<std::to_string(size)<< endl;    
    for(int i = 0; i < size; i++, ++itrcs) {
      string id=(*itrcs).getStudentID();
      string code=(*itrcs).getCourseCode();
      int mark=(*itrcs).getExamMark();
         fout << id<<endl;
	 fout << code <<endl;
	 fout << std::to_string(mark) <<endl;
        }
    fout.close ();
    cout<<"Saving Successful"<<endl;
    }
    else{
      cout<<"Error: Write File Error"<<endl;
    }
    return 0;
}

int FileManagement::loadData(){
    manager->clear();
    string str= fileName;
    const char *FILE  = str.c_str();
    ifstream fin(FILE);
    if(fin.is_open ()){
      string student;
      fin>> student;
      int size1;
      fin>> size1;
      for(int i=0;i<size1;i++){
      string id;
      string name;
      int year;
      int gender;
      fin>> id;
      fin>> name;
      fin>> year;
      fin>> gender;
      Student stu(id,name,year,gender);
      manager->newStudent(stu);
      }
      string course;
      fin>> course;
      int size2;
      fin>> size2;
      for(int i=0;i<size2;i++){
      string code;
      string name;
      int credit;
      fin>> code;
      fin>> name;
      fin>> credit;
      Course cou(code,name,credit);
      manager->newCourse(cou);
      }
      string regist;
      fin>> regist;
      int size3;
      fin>> size3;
      for(int i=0;i<size3;i++){
      string id;
      string code;
      int mark;
      fin>> id;
      fin>> code;
      fin>> mark;
      CourseSelection cs(id,code,mark);
      manager->newRegist(cs);
      }
    fin.close ();
    cout<<"Loading Successful"<<endl;
    }
    else{
      cout<<"Error: Load File Error"<<endl;
    }
    return 0;
}