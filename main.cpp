#include <iostream>
#include <sstream>
#include "DoublyLinkedList.h"
#include <cstdlib>
#include <assert.h>
#include "Records.h"
#include "RegistrationManager.h"
#include <stdlib.h>
#include "utility.h"
#include "html.h"
#include "ReportGeneration.h"
#include "FileManagement.h"

//menu and main function. connect with manager
using namespace std;

void studentMenu(RegistrationManager & manager){
  string studentID;
  string studentName;
  int year;
  int gender;
  
  system("clear");
  cout<<"HKUST Course Registration System (Student Menu)"<<endl;
  cout<<"-----------------------------------------------"<<endl<<endl;
  cout<<"1. Insert Student Record"<<endl;
  cout<<"2. Modify Student Record"<<endl;
  cout<<"3. Delete Student Record"<<endl;
  cout<<"4. Query Student Record"<<endl;
  cout<<"5. Go back to main menu"<<endl;
  cout<<endl;
  cout<<"Enter your choice (1-5): ";
  int choice;
  readInput(choice,1,5);
  if(choice!=5){
    cout<<"Enter the student ID: ";
    readStudentID(studentID);
    bool alreadyExist=manager.isStudentExist(studentID);
    if(choice==1&&alreadyExist){
      cout<<"Student already exist"<<endl;
    }
    else if(choice!=1 && alreadyExist==false){
      cout<<"Student not exist"<<endl;
    }
    else{
      if(choice==1){
	cout<<"Enter the student name: ";
	readStudentName(studentName);
	cout<<"Enter the student year ["<<YEAR_MIN<<"-"<<YEAR_MAX<<"]: ";
	readStudentyear(year);
	cout<<"Enter the student gender [M,F]: ";
	readStudentGender(gender);
	Student student(studentID,studentName,year,gender);
	bool successful=manager.newStudent(student);
	assert(successful);
	cout<<"Creation of student record successful"<<endl;
      }
      else if(choice==2){
	Student& searchresult=manager.searchStudent(studentID);
	cout<<"Enter the student name ["<<searchresult.getStudentName()<<"]: ";
	readStudentName(studentName);
	cout<<"Enter the student year ["<<searchresult.getYear()<<"]: ";
	readStudentyear(year);
	if(searchresult.getGender()){
	  cout<<"Enter the student gender [F]: ";
	}
	else{
	  cout<<"Enter the student gender [M]: ";
	}
	readStudentGender(gender);
	bool successful=manager.modifyStudent(searchresult,studentName,year,gender);
	assert(successful);
	cout<<"Modification of student record successful"<<endl;
      }
      else if(choice==3){
	bool successful=manager.deleteStudent(studentID);
	assert(successful);
	cout<<"Deletion of student record successful"<<endl;
      }
      else if(choice==4){
	Student& searchresult=manager.searchStudent(studentID);
	cout<<endl;
	cout<<"ID:     "<<searchresult.getStudentID()<<endl;
	cout<<"Name:   "<<searchresult.getStudentName()<<endl;
	cout<<"Year:   "<<searchresult.getYear()<<endl;
	if(searchresult.getGender()==1){
	  cout<<"Gender: Female"<<endl;;
	}
	else{
	  cout<<"Gender: Male"<<endl;;
	}
      }
    } 
    cout<<endl;
    cout<<"Hit Enter to continue"<<endl;
    string str;
    getline(cin,str); 
  }
}


void courseMenu(RegistrationManager & manager){
  string courseCode;
  string courseName;
  int Credit;
  
  system("clear");
  cout<<"HKUST Course Registration System (Course Menu)"<<endl;
  cout<<"----------------------------------------------"<<endl<<endl;
  cout<<"1. Insert Course Record"<<endl;
  cout<<"2. Modify Course Record"<<endl;
  cout<<"3. Delete Course Record"<<endl;
  cout<<"4. Query Course Record"<<endl;
  cout<<"5. Go back to main menu"<<endl;
  cout<<endl;
  cout<<"Enter your choice (1-5): ";
  int choice;
  readInput(choice,1,5);
  if(choice!=5){
    cout<<"Enter the course code: ";
    readCourseCode(courseCode);
    bool alreadyExist=manager.isCourseExist(courseCode);
    if(choice==1&&alreadyExist){
      cout<<"Course already exist"<<endl;
    }
    else if(choice!=1 && alreadyExist==false){
      cout<<"Course not exist"<<endl;
    }
    else{
      if(choice==1){
	cout<<"Enter the course name: ";
	readCourseName(courseName);
	cout<<"Enter the course credit ["<<CREDIT_MIN<<"-"<<CREDIT_MAX<<"]: ";
	readCourseCredit(Credit);
	Course course(courseCode,courseName,Credit);
	bool successful=manager.newCourse(course);
	assert(successful);
	cout<<"Creation of course record successful"<<endl;
      }
      else if(choice==2){
	Course& searchresult=manager.searchCourse(courseCode);
	cout<<"Enter the course name ["<<searchresult.getCourseName()<<"]: ";
	readCourseName(courseName);
	cout<<"Enter the credit ["<<searchresult.getCredit()<<"]: ";
	readCourseCredit(Credit);
	bool successful=manager.modifyCourse(searchresult,courseName,Credit);
	assert(successful);
	cout<<"Modification of course record successful"<<endl;
      }
      else if(choice==3){
	if(!manager.isCourseEmpty(courseCode)){
	  cout<<"Some students already registered"<<
	  " in this course, deletion fail"<<endl;
	}
	else{
	  bool successful=manager.deleteCourse(courseCode);
	  assert(successful);
	  cout<<"Deletion of course record successful"<<endl;
	}
      }
      else if(choice==4){
	Course& searchresult=manager.searchCourse(courseCode);
	cout<<endl;
	cout<<"Code:   "<<searchresult.getCourseCode()<<endl;
	cout<<"Name:   "<<searchresult.getCourseName()<<endl;
	cout<<"Credit: "<<searchresult.getCredit()<<endl;
      }
    } 
    cout<<endl;
    cout<<"Hit Enter to continue"<<endl;
    string str;
    getline(cin,str);
  }
}


void registrarionMenu(RegistrationManager & manager){
  string studentID;
  string courseCode;
  int examMark;
  
  system("clear");
  cout<<"HKUST Course Registration System (Registration Menu)"<<endl;
  cout<<"----------------------------------------------------"<<endl<<endl;
  cout<<"1. Add Course"<<endl;
  cout<<"2. Drop Course"<<endl;
  cout<<"3. Modify Exam Mark"<<endl;
  cout<<"4. Query Registration"<<endl;
  cout<<"5. Go back to main menu"<<endl;
  cout<<endl;
  cout<<"Enter your choice (1-5): ";
  int choice;
  readInput(choice,1,5);
  if(choice!=5){
    cout<<"Enter the student ID: ";
    readStudentID(studentID);
    if(!manager.isStudentExist(studentID)){
      cout<<"Student not exist"<<endl;
    }
    else{
      cout<<"Enter the course code: ";
      readCourseCode(courseCode);
      if(!manager.isCourseExist(courseCode)){
        cout<<"Course not exist"<<endl;
      }
      else{
        if(choice==1){
	  bool alreadyExist=manager.isRegistExist(studentID,courseCode);
	  if(alreadyExist){
	    cout<<"The student already registered the course"<<endl;
	  }
	  else{
	    CourseSelection cs(studentID,courseCode);
	    bool successful=manager.newRegist(cs);
	    assert(successful);
	    cout<<"Add course successful"<<endl;
	  }
	}
        else if(choice==2){
	  bool alreadyExist=manager.isRegistExist(studentID,courseCode);
	  if(alreadyExist==false){
	      cout<<"The registration record not exist"<<endl;
	  }
	  else{
            bool successful=manager.deleteRegist(studentID,courseCode);
	    assert(successful);
	    cout<<"Drop course successful"<<endl;
	    
	  }
        }
        else if(choice==3){
          bool alreadyExist=manager.isRegistExist(studentID,courseCode);
	  if(alreadyExist==false){
	      cout<<"The registration record not exist"<<endl;
	  }
	  else{
	    CourseSelection& searchresult=manager.searchRegist(studentID,courseCode);
	    int oldmark=searchresult.getExamMark();
	    if(oldmark<0){
	      cout<<"Enter the exam mark [N/A]: ";
	    }
	    else{
	      cout<<"Enter the exam mark ["<<oldmark<<"]: ";
	    }
	    readExamMark(examMark);
	    searchresult.setExamMark(examMark);
	    cout<<"Modification of exam mark successful"<<endl;
	  }
	}
        else if(choice==4){
	  bool alreadyExist=manager.isRegistExist(studentID,courseCode);
	  if(alreadyExist==false){
	      cout<<"The registration record not exist"<<endl;
	  }
	  else{
	    CourseSelection& searchresult=manager.searchRegist(studentID,courseCode);
	    cout<<endl;
	    cout<<"StudentID:   "<<searchresult.getStudentID()<<endl;
	    cout<<"Course code: "<<searchresult.getCourseCode()<<endl;
	    if(searchresult.getExamMark()>-1){
	      cout<<"Exam Mark:   "<<searchresult.getExamMark()<<endl;
	    }
	    else{
	      cout<<"Exam Mark:   N/A"<<endl;
	    }
	  }
	}
      } 
    }
    cout<<endl;
    cout<<"Hit Enter to continue"<<endl;
    string str;
    getline(cin,str); 
  }
}


void reportMenu(RegistrationManager & manager){
  string studentID;
  string courseCode;
  system("clear");
  cout<<"HKUST Course Registration System (Report Generation Menu)"<<endl;
  cout<<"---------------------------------------------------------"<<endl<<endl;
  cout<<"1. List all student information"<<endl;
  cout<<"2. List all course information"<<endl;
  cout<<"3. List all courses of a studnet"<<endl;
  cout<<"4. List all students of a course"<<endl;
  cout<<"5. Go back to main menu"<<endl;
  cout<<endl;
  cout<<"Enter your choice (1-5): ";
  int choice;
  readInput(choice,1,5);
  if(choice!=5){
    if(choice==1){
      ReportGeneration report(&manager);
      report.outputallstudents();
    }
    if(choice==2){
      ReportGeneration report(&manager);
      report.outputallcourses();
    }
    if(choice==3){
      cout<<"Enter the student ID: ";
      readStudentID(studentID);
      if(!manager.isStudentExist(studentID)){
        cout<<"Student not exist"<<endl;
      }
      else{
        ReportGeneration report(&manager,studentID);
        report.outputcsbystu();
      }
    }
    if(choice==4){
      cout<<"Enter the course code: ";
      readCourseCode(courseCode);
      if(!manager.isCourseExist(courseCode)){
        cout<<"Course not exist"<<endl;
      }
      else{
        ReportGeneration report(&manager,courseCode);
        report.outputcsbycou();
      }
    }
    cout<<endl;
    cout<<"Hit Enter to continue"<<endl;
    string str;
    getline(cin,str);
  }  
}


void fileMenu(RegistrationManager & manager){
  string fileName;
  system("clear");
  cout<<"HKUST Course Registration System (File Menu)"<<endl;
  cout<<"----------------------------------------------"<<endl<<endl;
  cout<<"1. Save Database"<<endl;
  cout<<"2. Load Database"<<endl;
  cout<<"3. Go back to main menu"<<endl;
  cout<<endl;
  cout<<"Enter your choice (1-3): ";
  int choice;
  readInput(choice,1,3);
  if(choice!=3){
    cout<<"Enter the filename: ";
    getline(cin,fileName);
    if(choice==1){
      FileManagement File(&manager,fileName);
      File.saveData();
    }
    if(choice==2){
      FileManagement File(&manager,fileName);
      File.loadData();
    }
    cout<<endl;
    cout<<"Hit Enter to continue"<<endl;
    string str;
    getline(cin,str);
  }
}


int main(){
RegistrationManager manager;
int choice;
do
{
  system("clear");
  cout<<"HKUST Course Registration System"<<endl;
  cout<<"---------------------------------"<<endl<<endl;
  cout<<"1. Student Management"<<endl;
  cout<<"2. Course Management"<<endl;
  cout<<"3. CourseRegistration"<<endl;
  cout<<"4. Report Management"<<endl;
  cout<<"5. File Management"<<endl;
  cout<<"6. Exit"<<endl;
  cout<<endl;
  cout<<"Enter your choice (1-6): ";
  readInput(choice,1,6);
  switch(choice){
    case 1:studentMenu(manager);break;
    case 2:courseMenu(manager);break;
    case 3:registrarionMenu(manager);break;
    case 4:reportMenu(manager);break;
    case 5:fileMenu(manager);break;
  };
}
while(choice!=6);

return 0;
}

