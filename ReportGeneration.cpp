#include "RegistrationManager.h"
#include "ReportGeneration.h"
#include "html.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <sstream>
ReportGeneration::ReportGeneration():manager(0){}

ReportGeneration::ReportGeneration(RegistrationManager* m):manager(m){}

ReportGeneration::ReportGeneration(RegistrationManager* m,string str):
manager(m),search(str){}

int ReportGeneration::outputallstudents(){
    bool hasStu = true;
    DoublyLinkedList<Student> results=manager->getallstudents();
    typename DoublyLinkedList<Student>::Iterator itr=results.begin();
    try {
        HTMLFile file("Students.html", "All Students List");
        file.begin();
        file.openTag("H2");
        file.writeString("All Students List");
        file.closeTag();
        if(results.size()==0){
            hasStu = false;
            file.openTag("P");
            file.writeString("No student found");
            file.closeTag();
        }
        if(hasStu) {
	    file.openTag("P");
            HTMLTable table(&file);
            table.insertHead("Student ID");
            table.insertHead("Student Name");
            table.insertHead("Year");
            table.insertHead("Gender");
            table.begin();
            try {  
	      for(; itr != results.end()&&
		itr.getNoteptr()!=results.getsentinel(); ++itr) { 
                    table.beginRow();
                    table.insertCell((*itr).getStudentID());
                    table.insertCell((*itr).getStudentName());
		    std::stringstream ss;
		    ss<<(*itr).getYear();
		    string str=ss.str();
                    table.insertCell(str);
                    table.insertCell(((*itr).getGender() == 0)?("Male"):("Female"));
                    table.endRow();
              }
                    table.beginRow();
                    table.insertCell((*itr).getStudentID());
                    table.insertCell((*itr).getStudentName());
		    std::stringstream ss;
		    ss<<(*itr).getYear();
		    string str=ss.str();
                    table.insertCell(str);
                    table.insertCell(((*itr).getGender() == 0)?("Male"):("Female"));
                    table.endRow();
            }
            catch(runtime_error& e) {
                //Ignore
            }
            table.end();
	    file.closeTag();
        }
        file.end();
        cout << "Output Successful" << endl;
    }
    catch(...) {
        cout << "File error" << endl;
    }
    return 0;
}

int ReportGeneration::outputallcourses(){
    bool hasCou = true;
    DoublyLinkedList<Course> results=manager->getallcourses();
    typename DoublyLinkedList<Course>::Iterator itr=results.begin();
    try {
        HTMLFile file("Courses.html", "All Course List");
        file.begin();
        file.openTag("H2");
        file.writeString("All Course List");
        file.closeTag();
        if(results.size()==0){
            hasCou = false;
            file.openTag("P");
            file.writeString("No course found");
            file.closeTag();
        }
        if(hasCou) {
	    file.openTag("P");
            HTMLTable table(&file);
            table.insertHead("Course Code");
            table.insertHead("Course Name");
            table.insertHead("Credit");
            table.begin();
            try {  
	      for(; itr != results.end()&&
		itr.getNoteptr()!=results.getsentinel(); ++itr) { 
                    table.beginRow();
                    table.insertCell((*itr).getCourseCode());
                    table.insertCell((*itr).getCourseName());
		    std::stringstream ss;
		    ss<<(*itr).getCredit();
		    string str=ss.str();
                    table.insertCell(str);
                    table.endRow();
              }
                    table.beginRow();
                     table.insertCell((*itr).getCourseCode());
                    table.insertCell((*itr).getCourseName());
		    std::stringstream ss;
		    ss<<(*itr).getCredit();
		    string str=ss.str();
                    table.insertCell(str);
                    table.endRow();
            }
            catch(runtime_error& e) {
                //Ignore
            }
            table.end();
	    file.closeTag();
        }
        file.end();
        cout << "Output Successful" << endl;
    }
    catch(...) {
        cout << "File error" << endl;
    }
    return 0;
}

int ReportGeneration::outputcsbystu(){
    bool hasStu = true;
    Student& stu=manager->searchStudent(search);
    DoublyLinkedList<CourseSelection> results=manager->getcsbystu(search);
    typename DoublyLinkedList<CourseSelection>::Iterator itr=results.begin();
    try {
        HTMLFile file(stu.getStudentID()+".html", "Course Records for Student "+stu.getStudentID());
        file.begin();
        file.openTag("H2");
        file.writeString("Course Records for Student: as ("+stu.getStudentID()+")");
        file.closeTag();
        if(results.size()==0){
            hasStu = false;
            file.openTag("P");
            file.writeString("No course taken");
            file.closeTag();
        }
        if(hasStu) {
	    file.openTag("P");
            HTMLTable table(&file);
            table.insertHead("Course Code");
            table.insertHead("Course Name");
            table.insertHead("Credit");
            table.insertHead("Exam Mark");
            table.begin();
            try {  
	      for(; itr != results.end()&&
		itr.getNoteptr()!=results.getsentinel(); ++itr) { 
		    Course& cou=manager->searchCourse((*itr).getCourseCode());
                    table.beginRow();
                    table.insertCell(cou.getCourseCode());
                    table.insertCell(cou.getCourseName());
		    std::stringstream ss;
		    ss<<cou.getCredit();
		    string str=ss.str();
                    table.insertCell(str);
		    int mark=(*itr).getExamMark();
		    if (mark<0){
		      table.insertCell("N/A");
		    }
		    else{
		    std::stringstream ss1;
		    ss1<<mark;
		    string str1=ss1.str();
                    table.insertCell(str1);
		    }
                    table.endRow();
              }
		    Course& cou=manager->searchCourse((*itr).getCourseCode());
                    table.beginRow();
                    table.insertCell(cou.getCourseCode());
                    table.insertCell(cou.getCourseName());
		    std::stringstream ss;
		    ss<<cou.getCredit();
		    string str=ss.str();
                    table.insertCell(str);
		    int mark=(*itr).getExamMark();
		    if (mark<0){
		      table.insertCell("N/A");
		    }
		    else{
		    std::stringstream ss1;
		    ss1<<mark;
		    string str1=ss1.str();
                    table.insertCell(str1);
		    }
                    table.endRow();
            }
            catch(runtime_error& e) {
                //Ignore
            }
            table.end();
	    file.closeTag();
        }
        file.end();
        cout << "Output Successful" << endl;
    }
    catch(...) {
        cout << "File error" << endl;
    }
    return 0;
}

int ReportGeneration::outputcsbycou(){
    bool hasStu = true;
    Course& cou=manager->searchCourse(search);
    DoublyLinkedList<CourseSelection> results=manager->getcsbycou(search);
    typename DoublyLinkedList<CourseSelection>::Iterator itr=results.begin();
    try {
        HTMLFile file(cou.getCourseCode()+".html", "Student Records for Course  "+cou.getCourseCode());
        file.begin();
        file.openTag("H2");
        file.writeString("Student Records for Course: "+cou.getCourseName()+" ("+cou.getCourseCode()+")");
        file.closeTag();
        if(results.size()==0){
            hasStu = false;
            file.openTag("P");
            file.writeString("No student take");
            file.closeTag();
        }
        if(hasStu) {
	    file.openTag("P");
            HTMLTable table(&file);
            table.insertHead("Student ID");
            table.insertHead("Student Name");
            table.insertHead("Year");
	    table.insertHead("Gender");
            table.insertHead("Exam Mark");
            table.begin();
            try {  
	      for(; itr != results.end()&&
		itr.getNoteptr()!=results.getsentinel(); ++itr) { 
		    Student& stu=manager->searchStudent((*itr).getStudentID());
                    table.beginRow();
                    table.insertCell(stu.getStudentID());
                    table.insertCell(stu.getStudentName());
		    std::stringstream ss;
		    ss<<stu.getYear();
		    string str=ss.str();
                    table.insertCell(str);
		    table.insertCell((stu.getGender() == 0)?("Male"):("Female"));
		    int mark=(*itr).getExamMark();
		    if (mark<0){
		      table.insertCell("N/A");
		    }
		    else{
		    std::stringstream ss1;
		    ss1<<mark;
		    string str1=ss1.str();
                    table.insertCell(str1);
		    }
                    table.endRow();
              }
		    Student& stu=manager->searchStudent((*itr).getStudentID());
                    table.beginRow();
                    table.insertCell(stu.getStudentID());
                    table.insertCell(stu.getStudentName());
		    std::stringstream ss;
		    ss<<stu.getYear();
		    string str=ss.str();
                    table.insertCell(str);
		    table.insertCell((stu.getGender() == 0)?("Male"):("Female"));
		    int mark=(*itr).getExamMark();
		    if (mark<0){
		      table.insertCell("N/A");
		    }
		    else{
		    std::stringstream ss1;
		    ss1<<mark;
		    string str1=ss1.str();
                    table.insertCell(str1);
		    }
                    table.endRow();
            }
            catch(runtime_error& e) {
                //Ignore
            }
            table.end();
	    file.closeTag();
        }
        file.end();
        cout << "Output Successful" << endl;
    }
    catch(...) {
        cout << "File error" << endl;
    }
    return 0;
}

