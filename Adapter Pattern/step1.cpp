#include <iostream>
#include <string>
#include "my_print.cpp"
using namespace std;

class OldLogger {
public:
    void logMessage(const std::string& message) {
        std::cout << "Old Log: " << message << std::endl;
    }
};

class NewLogger {
public:
    virtual void logInfo(const std::string& info) = 0;
    virtual void logError(const std::string& error) = 0;
};

class AdapterLogger :public NewLogger{
  protected:
  OldLogger* oldLogger;
  public:
  AdapterLogger(OldLogger* oldLogger){this->oldLogger=oldLogger;}
  void logInfo(const std::string& info){
    oldLogger->logMessage(info);
  }
  void logError(const std::string& error){
    oldLogger->logMessage(error);
  }
};
int main(){
  OldLogger* oldLogger=new OldLogger();
  AdapterLogger* adapterLogger=new AdapterLogger(oldLogger);
  adapterLogger->logError("this is error message");
  adapterLogger->logInfo("this is Info message");

}
