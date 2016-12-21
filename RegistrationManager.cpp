#include "RegistrationManager.h"
#include <iostream>
#include "HashTable.h"
#include <string>
#include "DoublyLinkedList.h"
#include "Records.h"
RegistrationManager::RegistrationManager(){
  studenttable= new HashTable<Student>(STUDENT_ID_M);
  studentselect= new HashTable<Studentindexnode>(STUDENT_ID_M);
  coursetable= new HashTable<Course>(COURSECODE_M);
  courseselect= new HashTable<Courseindexnode>(COURSECODE_M);
  registration= new DoublyLinkedList<CourseSelection>;
}

RegistrationManager::~RegistrationManager (){
  delete studenttable;
  delete coursetable;
  delete studentselect;
  delete courseselect;
  delete registration;
}

void RegistrationManager::clear(){
  delete studenttable;
  delete coursetable;
  delete studentselect;
  delete courseselect;
  delete registration;
  studenttable= new HashTable<Student>(STUDENT_ID_M);
  studentselect= new HashTable<Studentindexnode>(STUDENT_ID_M);
  coursetable= new HashTable<Course>(COURSECODE_M);
  courseselect= new HashTable<Courseindexnode>(COURSECODE_M);
  registration= new DoublyLinkedList<CourseSelection>;
}

bool RegistrationManager::isStudentExist(string str){
  Student* stuptr=studenttable->search(str);
  if(stuptr==NULL){
    return 0;
  }
  else
  {
    return 1;
  }
}

bool RegistrationManager::newStudent(Student& stu){
  studenttable->insert(stu);
  return 1;
}

bool RegistrationManager::modifyStudent
( Student& stu,string name,int year,int gender){
  stu.setStudentName(name);
  stu.setYear(year);
  stu.setGender(gender);
  return 1;
}

Student& RegistrationManager::searchStudent(string id){
  Student* stuptr=studenttable->search(id);
  return *stuptr;
}


bool RegistrationManager::deleteStudent(string id){
   DoublyLinkedList<Studentindexnode> result=studentselect->searchall(id);
   typename DoublyLinkedList<Studentindexnode>::Iterator itrs;
   itrs = result.begin();
   if((result.size()==1)){
     deleteRegistincou(id,(*itrs).getCourseCode());
   }
   else if((result.size()>1)){
     for(;itrs != result.end()&&itrs.getNoteptr()!=result.getsentinel(); ++itrs) {
       deleteRegistincou(id,(*itrs).getCourseCode());
     }
   deleteRegistincou(id,(*itrs).getCourseCode());
   }
   studentselect->deleteall(id);
   itrs = result.begin();
    if((result.size()==1)){
       CourseSelection cs(id,(*itrs).getCourseCode());
       registration->deletebyequal(cs);
   }
   else if((result.size()>1)){
     for(;itrs != result.end()&&itrs.getNoteptr()!=result.getsentinel(); ++itrs) {
       CourseSelection cs(id,(*itrs).getCourseCode());
       registration->deletebyequal(cs);
     }
     CourseSelection cs(id,(*itrs).getCourseCode());
     registration->deletebyequal(cs);
  }
  studenttable->deleteByKey(id);
  return 1;
}

bool RegistrationManager::isCourseExist(string str){
  Course* couptr=coursetable->search(str);
  if(couptr==NULL){
    return 0;
  }
  else
  {
    return 1;
  }
}

bool RegistrationManager::newCourse(Course& cou){
  coursetable->insert(cou);
  return 1;
}

Course& RegistrationManager::searchCourse(string code){
  Course* couptr=coursetable->search(code);
  return *couptr;
}

bool RegistrationManager::modifyCourse
( Course& cou,string name,int credit){
  cou.setCourseName(name);
  cou.setCredit(credit);
  return 1;
}

bool RegistrationManager::isCourseEmpty(string str){
  DoublyLinkedList<Courseindexnode> result=courseselect->searchall(str);
  if(result.size()==0){
    return 1;
  }
  else{
    return 0;
  }
}

bool RegistrationManager::deleteCourse(string code){
  coursetable->deleteByKey(code);
  return 1;
}

bool RegistrationManager::isRegistExist(string stuid,string coucode){
  CourseSelection cstemp(stuid,coucode);
  CourseSelection* tempptr=registration->search(cstemp);
  if(tempptr==NULL){
    return 0;
  }
  else
  {
    return 1;
  }
}

bool RegistrationManager::newRegist(CourseSelection& cs){
  registration->insertInorder(cs);
  CourseSelection* csptr=registration->search(cs);
  Studentindexnode stuindex(csptr->getStudentID(),csptr->getCourseCode(),csptr);
  Courseindexnode couindex(csptr->getStudentID(),csptr->getCourseCode(),csptr);
  studentselect->insertallowrepeat(stuindex);
  courseselect->insertallowrepeat(couindex);
  return 1;
}

bool RegistrationManager::deleteRegist(string id, string code){
  deleteRegistinstu(id,code);
  deleteRegistincou(id,code);
  CourseSelection cs(id,code);
  registration->deletebyequal(cs);
  return 1;
}

CourseSelection& RegistrationManager::searchRegist(string stuid,string coucode){
  CourseSelection cstemp=CourseSelection(stuid,coucode);
  CourseSelection* tempptr=registration->search(cstemp);
  return *tempptr;
}

bool RegistrationManager::deleteRegistinstu(string id, string code){
  int index = Studentindexnode::Hash(studentselect->gettype(), id);
  typename DoublyLinkedList<Studentindexnode>::Iterator itrs;
  DoublyLinkedList<Studentindexnode>* buckets;
  buckets=studentselect->getbuckets(index);
  itrs = buckets->begin();
  if((buckets->size()==1)){
    if(((*itrs).getStudentID() == id)&&((*itrs).getCourseCode() == code)) {
        itrs.deletecurrent();
        studentselect->setsize(studentselect->size()-1);
      }
  }
  else if((buckets->size()>1)){
    for(;itrs != buckets->end()&&itrs.getNoteptr()!=buckets->getsentinel(); ++itrs) {
      if(((*itrs).getStudentID() == id)&&((*itrs).getCourseCode() == code)) {
        itrs.deletecurrent();
        studentselect->setsize(studentselect->size()-1);
      }
    }
    if(((*itrs).getStudentID() == id)&&((*itrs).getCourseCode() == code)) {
      itrs.deletecurrent();
      studentselect->setsize(studentselect->size()-1);
    }
  }
  return 1;
}

bool RegistrationManager::deleteRegistincou(string id, string code){
  int index = Courseindexnode::Hash(courseselect->gettype(), code);
  typename DoublyLinkedList<Courseindexnode>::Iterator itrc;
  DoublyLinkedList<Courseindexnode>* bucketc;
  bucketc=courseselect->getbuckets(index);
  itrc = bucketc->begin();
  if((bucketc->size()==1)){
     if(((*itrc).getStudentID() == id)&&((*itrc).getCourseCode() == code)) {
        itrc.deletecurrent();
        courseselect->setsize(courseselect->size()-1);
      }
  }
  if((bucketc->size()>1)){
    for(;itrc != bucketc->end()&&itrc.getNoteptr()!=bucketc->getsentinel(); ++itrc) {
      if(((*itrc).getStudentID() == id)&&((*itrc).getCourseCode() == code)) {
        itrc.deletecurrent();
        courseselect->setsize(courseselect->size()-1);
      }
    }
    if(((*itrc).getStudentID() == id)&&((*itrc).getCourseCode()== code)) {
      itrc.deletecurrent();
      courseselect->setsize(courseselect->size()-1);
    }
  }
  return 1;
}

DoublyLinkedList<Student> RegistrationManager::getallstudents(){
  DoublyLinkedList<Student> results=studenttable->returnAll();
  return results;
}

DoublyLinkedList<Course> RegistrationManager::getallcourses(){
  DoublyLinkedList<Course> results=coursetable->returnAll();
  return results;
}

DoublyLinkedList<CourseSelection> RegistrationManager::getallcs(){
  DoublyLinkedList<CourseSelection> results=*registration;
  return results;
}

DoublyLinkedList<CourseSelection> RegistrationManager::getcsbystu(string id){
  DoublyLinkedList<Studentindexnode> results=studentselect->searchall(id);
  DoublyLinkedList<CourseSelection> output;
  typename DoublyLinkedList<Studentindexnode>::Iterator itr;
    if(( results.size()>0)){
    itr = results.begin();
  for(; itr != results.end()&&
    itr.getNoteptr()!=results.getsentinel(); ++itr) { 
  output.insertInorderallowrepeat(*((*itr).getptr()));
  }
  output.insertInorderallowrepeat(*((*itr).getptr()));
  }
  return output; 
}

DoublyLinkedList<CourseSelection> RegistrationManager::getcsbycou(string code){
  DoublyLinkedList<Courseindexnode> results=courseselect->searchall(code);
  DoublyLinkedList<CourseSelection> output;
  typename DoublyLinkedList<Courseindexnode>::Iterator itr;
    if(( results.size()>0)){
    itr = results.begin();
  for(; itr != results.end()&&
    itr.getNoteptr()!=results.getsentinel(); ++itr) { 
  output.insertInorderallowrepeat(*((*itr).getptr()));
  }
  output.insertInorderallowrepeat(*((*itr).getptr()));
  }
  return output; 
}
