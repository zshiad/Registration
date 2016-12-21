#include "RegistrationManager.h"
//use html and manager to out put.
class ReportGeneration{
private:
  RegistrationManager* manager;
  string search;
public:
  ReportGeneration();
  ReportGeneration(RegistrationManager*);
  ReportGeneration(RegistrationManager*,string);
  int outputcsbycou();
  int outputcsbystu();
  int outputallcourses();
  int outputallstudents();
};
