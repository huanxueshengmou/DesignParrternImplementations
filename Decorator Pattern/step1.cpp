#include <iostream>
#include <string>
#include <memory>
#include "my_print.cpp"
using namespace std;
using std::string;

class Beverage{
  protected:
  bool pure=false;
  string beverage_description;
  double beverage_cost;
  public:
  Beverage(string description,double cost){
    beverage_description=description;
    beverage_cost=cost;
    }
  virtual string getDescription(){
    return beverage_description;
  }
  virtual double cost(){
    return beverage_cost;
  }
  public:
  virtual void setDescription(string new_str){
    if(!pure)
    beverage_description=beverage_description+" with added "+new_str;
    else 
    beverage_description=beverage_description+new_str;
  }
};

class Coffee:public Beverage{
  public:
  Coffee():Beverage("咖啡",12.0){}
};

class CondimentDecorator :public Beverage{
  public:
    CondimentDecorator(string description, double cost) : Beverage(description, cost) {}
  protected:
  unique_ptr<Beverage> my_Beverage;
  public:
  void addBeverage(unique_ptr<Beverage> new_beverage){
    my_Beverage=move(new_beverage);
  }
  void addSugar(){
    my_Beverage->setDescription("sugar");
    beverage_cost += 1.0; // 假设糖的成本是1.0
  }
  string getDescription() override {
        return my_Beverage->getDescription();
  }
  double cost() override {
    printNonPln("The ",getDescription()," price is ");
    return my_Beverage->cost() + beverage_cost;
  }
};

int main(){
    unique_ptr<Beverage> coffee = make_unique<Coffee>();
    unique_ptr<CondimentDecorator> condimentDecorator = make_unique<CondimentDecorator>("", 0);
    condimentDecorator->addBeverage(move(coffee));
    condimentDecorator->addSugar();
    print(condimentDecorator->getDescription());
    printNonPln(condimentDecorator->cost());

    return 0;
}