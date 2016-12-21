#include "RegistrationManager.h"
//use manager to save and load database. output is txt file
class FileManagement{
private:
  RegistrationManager* manager;
  string fileName;
public:
  FileManagement();
  FileManagement(RegistrationManager*,string);
  int saveData();
  int loadData();

};

