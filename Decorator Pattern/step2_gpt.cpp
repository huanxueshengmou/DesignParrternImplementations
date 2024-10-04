
#include <iostream>
#include <string>
#include <memory>
#include "my_print.cpp"
using namespace std;
using std::string;

class Beverage
{
protected:
  bool pure = false;
  string beverage_description;
  double beverage_cost;

public:
  Beverage(string description, double cost)
  {
    beverage_description = description;
    beverage_cost = cost;
  }
  virtual string getDescription()
  {
    return beverage_description;
  }
  virtual string getDescription(string new_str)
  {
    return beverage_description;
  }
  virtual double cost()
  {
    return beverage_cost;
  }

public:
  virtual void setDescription(string new_str)
  {
    if (!pure)
      beverage_description = beverage_description + " with added " + new_str;
    else
      beverage_description = beverage_description + new_str;
  }
};

class Coffee : public Beverage
{
public:
  Coffee() : Beverage("咖啡", 12.0) {}
public:
  string getDescription()
  {
    return beverage_description;
  }
};

class CondimentDecorator : public Beverage
{
public:
  CondimentDecorator(string description, double cost) : Beverage(description, cost) {}

protected:
  unique_ptr<Beverage> my_Beverage;

public:
  void addBeverage(unique_ptr<Beverage> new_beverage)
  {
    my_Beverage = move(new_beverage);
  }
};

class SugarDecorator : public CondimentDecorator
{
public:
  SugarDecorator() : CondimentDecorator("Sugar", 1.0) {}

  void addSugar()
  {
    my_Beverage->setDescription("sugar");
    beverage_cost += 1.0; // 假设糖的成本是1.0
  }

  double cost() override
  {
    printNonPln("The ", getDescription(), " price is ");
    return my_Beverage->cost() + beverage_cost;
  }
};

class MilkDecorator : public CondimentDecorator
{
public:
  MilkDecorator() : CondimentDecorator("Milk", 2.0) {}

  void addMilk()
  {
    my_Beverage->setDescription("MILK");
    beverage_cost += 2.0; // 假设牛奶的成本是2.0
  }

  double cost() override
  {
    printNonPln("The ", getDescription(), " price is ");
    return my_Beverage->cost() + beverage_cost;
  }
};

int main()
{
  unique_ptr<Beverage> coffee = make_unique<Coffee>();
  unique_ptr<CondimentDecorator> sugarDecorator = make_unique<SugarDecorator>();
  unique_ptr<CondimentDecorator> milkDecorator = make_unique<MilkDecorator>();

  sugarDecorator->addBeverage(move(coffee));
  milkDecorator->addBeverage(move(sugarDecorator));

  print(milkDecorator->getDescription());
  printNonPln(milkDecorator->cost());

  return 0;
}