#include <iostream>
#include <string>
#include "my_print.cpp"

using namespace std;
using std::string;
class Computer{
protected:
  string CPU;
  string GPU;
  string memory;
  string type;
  public:
  Computer( 
  string CPU,
  string GPU,
  string memory,
  string type){
    this->CPU=CPU;
    this->GPU=GPU;
    this->memory=memory;
    this->type=type;
  }
  public:
  virtual string getCPU(){
    return CPU;
  };
  virtual string getGPU(){
    return GPU;
  };
  virtual string getmemory(){
    return memory;
  };
  virtual string getType(){
    return type;
  };
  public:
  virtual void setCPU(string CPU){
    this->CPU=CPU;
  }
  virtual void setGPU(string GPU){
    this->GPU=GPU;
  }
  virtual void setMemory(string memory){
    this->memory=memory;
  }
};

class ComputerBuilder{
  protected:
  string CPU;
  string GPU;
  string memory;
  string type;
  public:
  Computer createComputer(){
    return Computer(CPU,GPU,memory,type);
  }
  public:
  virtual ComputerBuilder& setCPU(string CPU){
    this->CPU=CPU;
    return *this;
  }
  virtual ComputerBuilder& setGPU(string GPU){
    this->GPU=GPU;
    return *this;
  }
  virtual ComputerBuilder& setMemory(string memory){
    this->memory=memory;
    return *this;
  }
  virtual ComputerBuilder& setType(){
    this->type="";
    return *this;
  }
};

class GamingComputerBuilder:public ComputerBuilder{
  public:
  ComputerBuilder& setType()override{
    this->type="GamingComputer";
    return *this;
  }
};
class OfficeComputerBuilder:public ComputerBuilder{
  public:
  ComputerBuilder&  setType()override{
    this->type="OfficeComputer";
    return *this;
  }
};
class GraphicDesignComputerBuilder:public ComputerBuilder{
  public:
  ComputerBuilder&  setType()override{
    this->type="GraphicDesignComputer";
    return *this;
  }
};
class ComputerDirector {
public:
    Computer generateComputer(string type) {
        if (type == "GamingComputer") {
            GamingComputerBuilder* generator = new GamingComputerBuilder();
            generator->setCPU("Intel i9")
                     .setGPU("NVIDIA RTX 3080")
                     .setMemory("32GB DDR4")
                     .setType();
            return generator->createComputer();
        }
        else if (type == "OfficeComputer") {
            OfficeComputerBuilder* generator = new OfficeComputerBuilder();
            generator->setCPU("Intel i5")
                     .setGPU("Integrated Graphics")
                     .setMemory("16GB DDR4")
                     .setType();
            return generator->createComputer();
        }
        else if (type == "GraphicDesignComputer") {
            GraphicDesignComputerBuilder* generator = new GraphicDesignComputerBuilder();
            generator->setCPU("AMD Ryzen 7")
                     .setGPU("NVIDIA RTX 3070")
                     .setMemory("64GB DDR4")
                     .setType();
            return generator->createComputer();
        }
        else {
            throw std::invalid_argument("Invalid computer type");
        }
    }
}; 
int main(){
  ComputerDirector* dc=new ComputerDirector();
  Computer myComputer=dc->generateComputer("OfficeComputer");
  print(myComputer.getCPU());
  print(myComputer.getGPU());
  print(myComputer.getmemory());
  print(myComputer.getType());
}
