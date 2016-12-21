#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <iostream>
#include <sstream>
#include <Records.h>
using namespace std;
// cheack all input whether correct

void readInput(int &choice, int a, int b){
  string str;
  getline(cin,str);
  if(str.size()!=1){
    cout<<"Invalid input, re-enter again ("<<a<<"-"<<b<<"): ";
    readInput(choice,a, b);
    return;
  }
  int number=(int) str[0];
  if(number >= 48+a && number <= 48+b){
    choice=number-48;
  }
  else{
    cout<<"Invalid input, re-enter again ("<<a<<"-"<<b<<"): ";
    readInput(choice,a, b);
    return;
  }
}

void readStudentID(string& studentID){
  string str;
  getline(cin,str);
  if(str.size()!=STUDENT_ID_LENGTH){
    cout<<"Invalid input, re-enter again [student ID]: ";
    readStudentID(studentID);
    return;
  }
  else{
    for (int i = 0; i < STUDENT_ID_LENGTH; i++){
      int number = (int)str[i];
      if (!(number >= 48 && number <= 57)){
	cout<<"Invalid input, re-enter again [student ID]: ";
        readStudentID(studentID);
	return;
      }
    }
  }
  studentID=str;
}

void readStudentName(string& studentName){
  string str;
  getline(cin,str);
  if(str.size() < STUDENT_NAME_MIN || str.size() > STUDENT_NAME_MAX) {
    cout<<"Invalid input, re-enter again [student name]: ";
    readStudentName(studentName);
    return;
  }
  else{
    studentName = str;
  }
}

void readStudentyear(int & year){
  string str;
  getline(cin,str);
  if(str.size()!=1){
    cout<<"Invalid input, re-enter again [student year]: ";
    readStudentyear(year);
    return;
  }
  int number=(int) str[0];
  if(number-48 >=  YEAR_MIN && number-48 <=YEAR_MAX ){
    year=number-48;
  }
  else{
    cout<<"Invalid input, re-enter again [student year]: ";
    readStudentyear(year);
    return;
  }
}

void readStudentGender(int & gender){
  string str;
  getline(cin,str);
  if(str.size()!=1){
    cout<<"Invalid input, re-enter again [M,F]: ";
    readStudentGender(gender);
    return;
  }
  char mf=str[0];
  if(mf=='M'||mf=='m' ){
    gender=0;
  }
  else if(mf=='F'||mf=='f'){
    gender=1;
  }
  else
  {
    cout<<"Invalid input, re-enter again [M,F]: ";
    readStudentGender(gender);
    return;
  }
}

void readCourseCode(string& courseCode){
  string str;
  getline(cin,str);
  if (str.length() < COURSECODE_MIN || str.length() > COURSECODE_MAX) {
    cout<<"Invalid input, re-enter again [course code]: ";
    readCourseCode(courseCode);
    return;
  }
  else if(!Course::isValidCode(str)){
    cout<<"Invalid input, re-enter again [course code]: ";
    readCourseCode(courseCode);
    return;
  }
  else{
  courseCode=str;
  }
}

void readCourseName(string& courseName){
  string str;
  getline(cin,str);
  if(str.size() < COURSENAME_MIN || str.size() > COURSENAME_MAX) {
    cout<<"Invalid input, re-enter again [course name]: ";
    readCourseName(courseName);
    return;
  }
  else{
    courseName = str;
  }
}

void readCourseCredit(int & Credit){
  string str;
  getline(cin,str);
  if(str.size()!=1){
    cout<<"Invalid input, re-enter again [course credit]: ";
    readCourseCredit(Credit);
    return;
  }
  int number=(int) str[0];
  if(number-48 >=  CREDIT_MIN && number-48 <=CREDIT_MAX ){
    Credit=number-48;
  }
  else{
    cout<<"Invalid input, re-enter again [course credit]: ";
    readCourseCredit(Credit);
    return;
  }
}

void readExamMark(int & exammark){
  string str;
  getline(cin,str);
  int sum=0;
  for (unsigned int i = 0; i < str.size(); i++){
      int number = (int)str[i];
      if (!(number >= 48 && number <= 57)){
	cout<<"Invalid input, re-enter again [exam mark]: ";
        readExamMark(exammark);
	return;
      }
      int num=number-48;
      for (unsigned int j = 0; j < str.size()-i-1; j++){
	num=num*10;
      }
      sum=sum+num;
  }
  if(sum >=  EXAMMARK_MIN && sum <=EXAMMARK_MAX ){
    exammark=sum;
  }
  else{
    cout<<"Invalid input, re-enter again [exam mark]: ";
    readExamMark(exammark);
    return;
  }
}

#endif
