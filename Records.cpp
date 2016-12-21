#include "Records.h"
#include <iostream>
using std::cout;
using std::endl;

Student::Student() {};

Student::Student(string id,string name, int year,int mf) {
  setStudentID(id);
  setStudentName(name);
  setYear(year);
  setGender(mf);
};

Student::~Student() {};

Student::Student(const Student& stu) {
  setStudentID(stu.getStudentID());
  setStudentName(stu.getStudentName());
  setYear(stu.getYear());
  setGender(stu.getGender());
}

Student& Student::operator=(const Student& stu) {
  setStudentID(stu.getStudentID());
  setStudentName(stu.getStudentName());
  setYear(stu.getYear());
  setGender(stu.getGender());
  return *this;
}

string Student::getStudentID() const{
  return StudentID;
}

string Student::getStudentName() const{
  return StudentName;
}

int Student::getYear() const {
  return Year;
}

int Student::getGender() const {
  return Gender;
}

int Student::setStudentID(const string& id) {
  if(id.size() != STUDENT_ID_LENGTH) {
    return 0;
  }
  else if(!isValidID(id)) {
    return 0;
  }
  else {
    StudentID = id;
    return 1;
  }
}

int Student::setStudentName(const string& name) {
  if(name.size() < STUDENT_NAME_MIN || name.size() > STUDENT_NAME_MAX) {
    return 0;
  }
  else{
    StudentName = name;
    return 1;
  }
}

int Student::setYear(int year) {
  if (year < YEAR_MIN || year > YEAR_MAX) {
    return 0;
  }
  else {
    Year = year;
    return 1;
  }
}

int Student::setGender(int gender) {
  if (gender != MALE && gender != FEMALE) {
    return 0;
  }
  else {
    Gender = gender;
    return 1;
  }
}

bool Student::operator<(const Student& stu) {
  return StudentID < stu.getStudentID();
}

bool Student::operator>(const Student& stu) {
  return StudentID > stu.getStudentID();
}

bool Student::operator==(const Student& stu) {
  return StudentID == stu.getStudentID();
}

bool Student::operator==(const string& id) {
  return StudentID == id;
}

bool Student::isValidID(const string& id) {
  for (int i = 0; i < STUDENT_ID_LENGTH; i++){
    int number = (int)id[i];
    if (!(number >= 48 && number <= 57)){
      return 0;
    }
  }
  return 1;
}

void Student::print() {
  cout<<"Student ID: "<<StudentID<<endl;
  cout<<"Student Name: "<<StudentName<<endl;
  cout<<"Student Year: " <<Year<<endl;
  cout<<"Student Gender: ";
  if(!Gender) {
    cout<<"Male"<<endl;
  }
  else {
    cout<<"Female"<<endl;
  }
}

int Student::Hash(const Student& stu){
  return StudentIDHash(stu.getStudentID());
}

int Student::Hash(const Student& stu, const string& ID) {
  return StudentIDHash(ID);
}

int Student::StudentIDHash(string ID) {
  int sum = 0;
  std::stringstream ss;
  for (int i = 0; i < STUDENT_ID_LENGTH; i++){
    ss << ID[i];
    int number;
    ss >> number;
    ss.clear();
    for (int j = 0; j < i; j++) {
      number = (number * STUDENT_ID_B)% STUDENT_ID_M;
    }
    sum =(sum+number)% STUDENT_ID_M;
  }
  return sum % STUDENT_ID_M;
}

void Student::print(Student& stu) {
  stu.print();
}


Course::Course() {};

Course::Course(string code,string name,int credit) {
  setCourseCode(code);
  setCourseName(name);
  setCredit(credit);
};

Course::~Course() {};

Course::Course(const Course& course) {
  setCourseCode(course.getCourseCode());
  setCourseName(course.getCourseName());
  setCredit(course.getCredit());
}

Course& Course::operator=(const Course& course) {
  setCourseCode(course.getCourseCode());
  setCourseName(course.getCourseName());
  setCredit(course.getCredit());
  return *this;
}

string Course::getCourseCode() const {
  return CourseCode;
}

string Course::getCourseName() const {
  return CourseName;
}

int Course::getCredit() const {
  return Credit;
}

int Course::setCourseCode(const string& code) {
  if (code.length() < COURSECODE_MIN || code.length() > COURSECODE_MAX) {
    return 0;
  }
  else if(!isValidCode(code)) {
    return 0;
  }
  else {
    CourseCode = code;
    return 1;
  }
}

int Course::setCourseName(const string& name) {
  if(name .size() < COURSENAME_MIN || name.size() > COURSENAME_MAX) {
    return 0;
  }
  else {
    CourseName = name;
    return 1;
  }
}

int Course::setCredit(const int credit) {
  if(credit < CREDIT_MIN || credit > CREDIT_MAX) {
    return 0;
  }
  else {
    Credit = credit;
    return 1;
  }
}

bool Course::operator<(const Course& course) {
  return CourseCode < course.getCourseCode();
}

bool Course::operator>(const Course& course) {
  return CourseCode > course.getCourseCode();
}

bool Course::operator==(const Course& course) {
  return CourseCode == course.getCourseCode();
}

bool Course::operator==(const string& code) {
  return CourseCode == code;
}

bool Course::isValidCode(const string& code) {
  int l=code.length();
  for (int i = 0; i < 4; i++){
    if (!(code[i] >= 'A' && code[i] <= 'Z')){
      return 0;
    }
  }
  for (int i = 4; i < 7; i++){
    if (!((code[i] >= '0' && code[i]<= '9')||(code[i] >= 'A' && code[i] <= 'Z'))){
      return 0;
    }
  } 
  if(l==8){
    if (!((code[7] >= '0' && code[7] <= '9')||(code[7] >= 'A' && code[7] <= 'Z'))){
      return 0;
    }
  }
  else if(l>8){
    return 0;
  }
  return 1;
}

void Course::print() {
  cout<<"Course Code: "<< CourseCode << endl;
  cout<<"Course Name: "<< CourseName << endl;
  cout<<"Course Credit: "<< Credit << endl;
}

 int Course::ChartoNumber(char a) {
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

int Course::CourseCodeHash(string code) {
  int length = code.length();
  int sum = 0;
  for (int i = 0; i < length; i++) {
    int number = ChartoNumber(code[i]);
    for(int j = 0; j < i; j++) {
      number = (number% COURSECODE_M) * (COURSECODE_B % COURSECODE_M);
    }
    sum =(sum+number)% COURSECODE_M;
  }
  return sum % COURSECODE_M;
}

int Course::Hash(const Course& course) {
  return CourseCodeHash(course.getCourseCode());
}

int Course::Hash(const Course& course, const string& code) {
  return CourseCodeHash(code);
}

void Course::print(Course& course) {
  course.print();
}


CourseSelection::CourseSelection()
:ExamMark(UNASSIGNED) {}

CourseSelection::CourseSelection(string stu,string cou)
:Stu(stu), Cou(cou), ExamMark(UNASSIGNED) {}

CourseSelection::~CourseSelection() {}

CourseSelection::CourseSelection(string student, string course, int mark)
:Stu(student), Cou(course), ExamMark(mark) {}

CourseSelection& CourseSelection::operator=(const CourseSelection& cs) {
  setCourse(cs.getCourseCode());
  setStudent(cs.getStudentID());
  setExamMark(cs.getExamMark());
  return *this;
}

string CourseSelection::getStudentID() const {
  return Stu;
}

string CourseSelection::getCourseCode() const {
  return Cou;
}

int CourseSelection::getExamMark() const {
  return ExamMark;
}

int CourseSelection::setCourse(string course) {
  Cou = course;
  return 1;
}

int CourseSelection::setStudent(string student) {
  Stu = student;
  return 1;
}

int CourseSelection::setExamMark(const int mark) {
  if(mark < EXAMMARK_MIN || mark > EXAMMARK_MAX) {
    return 0;
  }
  else {
    ExamMark = mark;
    return 1;
  }
}

bool CourseSelection::operator<(const CourseSelection& cs) {
  if(Stu == cs.getStudentID()) {
    return Cou < cs.getCourseCode();
  }
  else {
    return Stu < cs.getStudentID();
  }
}

bool CourseSelection::operator>(const CourseSelection& cs) {
  if(Stu == cs.getStudentID()) {
    return Cou > cs.getCourseCode();
  }
  else {
    return Stu > cs.getStudentID();
  }
}

bool CourseSelection::operator==(const CourseSelection& cs) {
  return (Cou == cs.getCourseCode()) && (Stu == cs.getStudentID());
}

void CourseSelection::print() {
  cout<<"Student ID: " <<getStudentID()<<endl;
  cout<<"CourseCode: " <<getCourseCode() <<endl;
  cout<<"Exam Mark: " <<ExamMark <<endl;
}

void CourseSelection::print(CourseSelection& cs) {
  cs.print();
} 