#ifndef RECORDS_H
#define RECORDS_H
#include <string>
#include <sstream>
#include <iostream>
using std::string;
//const 
const int STUDENT_ID_LENGTH = 8;
const int STUDENT_ID_M = 29;
const int STUDENT_ID_B = 10;

const int STUDENT_NAME_MAX = 32;
const int STUDENT_NAME_MIN = 1;

const int YEAR_MAX = 3;
const int YEAR_MIN = 1;

const int MALE = 0;
const int FEMALE = 1;

const int COURSECODE_MAX = 8;
const int COURSECODE_MIN = 7;
const int COURSECODE_M = 17;
const int COURSECODE_B = 36;

const int COURSENAME_MAX = 50;
const int COURSENAME_MIN = 1;

const int CREDIT_MAX = 5;
const int CREDIT_MIN = 0;

const int UNASSIGNED = -1;
const int EXAMMARK_MAX = 100;
const int EXAMMARK_MIN = 0;

class Student {
private:
  string StudentID;
  string StudentName;
  int Year;
  int Gender;
public:
  Student();
  Student(string,string,int,int);
  ~Student();
  Student(const Student&);
  Student& operator=(const Student&);
  
  string getStudentID() const;
  string getStudentName() const;
  int getYear() const;
  int getGender() const;
  
  int setStudentID(const string&);
  int setStudentName(const string&);
  int setYear(int);
  int setGender(int);
  
  bool operator<(const Student&);
  bool operator>(const Student&);
  bool operator==(const Student&);
  bool operator==(const string&);
  
  bool isValidID(const string&);
  void print();
  
  static int StudentIDHash(string);//calculate the key
  static int Hash(const Student& );//calculate the key
  static int Hash(const Student& , const string& );//calculate the key
  static void print(Student& );
};

class Course {
private:
  string CourseCode;
  string CourseName;
  int Credit;
public:
  Course();
  Course(string,string,int);
  ~Course();
  Course(const Course&);
  Course& operator=(const Course&);
  
  int getCredit() const;
  string getCourseCode() const;
  string getCourseName() const;
  
  int setCourseCode(const string&);
  int setCourseName(const string&);
  int setCredit(const int);
  
  bool operator<(const Course&);
  bool operator>(const Course&);
  bool operator==(const Course&);
  bool operator==(const string&);
  
  static bool isValidCode(const string&);
  void print();
  
  static int ChartoNumber(char);//change char to int
  static int CourseCodeHash(string); //calculate the key
  static int Hash(const Course& ) ;//calculate the key
  static int Hash(const Course&, const string&);//calculate the key
  static void print(Course& );
};

class CourseSelection {
private:
  string Stu;
  string Cou;
  int ExamMark;
public:
  CourseSelection();
  CourseSelection(string,string);
  ~CourseSelection();
  CourseSelection(string , string , int);
  CourseSelection& operator=(const CourseSelection&);
  
  string getStudentID() const;
  string getCourseCode() const;
  int getExamMark() const;

  int setCourse(string);
  int setStudent(string);
  int setExamMark(const int);

  bool operator<(const CourseSelection&);
  bool operator>(const CourseSelection&);
  bool operator==(const CourseSelection&);

  void print();
  static void print(CourseSelection& );
};

#endif


