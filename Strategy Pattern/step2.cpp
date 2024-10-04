#include <iostream>
#include <string>
#include "my_print.cpp"
using namespace std;
using std::string;

// 确保 Calculator 类在 Commodity 类之前定义
class Calculator
{
public:
  virtual double getTotal(double basePrice) = 0;
};

class Commodity
{
protected:
  string name;
  double basePrice;
  Calculator *calculator;

public:
  virtual double getPrice()
  {
    return basePrice;
  }
  virtual void setPrice(double price)
  {
    basePrice = price;
  }
  virtual string getName()
  {
    return name;
  }
  virtual double getTotal()
  {
    return calculator->getTotal(basePrice);
  }
};

class Electronics : public Commodity
{
public:
public:
  Electronics(Calculator &new_calculator) { calculator = &new_calculator; }
  // Electronics(Calculator *new_calculator) { calculator = new_calculator; }

public:
  double getPrice() override
  {
    return basePrice;
  }
  void setPrice(double price) override
  {
    basePrice = price;
  }
  string getName() override
  {
    return name;
  }
};

class FoodProducts : public Commodity
{
public:
  FoodProducts(Calculator *new_calculator) { calculator = new_calculator; }

public:
  double getPrice()
  {
    return basePrice;
  }
  void setPrice(double price) override
  {
    basePrice = price;
  }
  string getName() override
  {
    return name;
  }
};

class CalFoodProducts : public Calculator
{
public:
  double getTotal(double basePrice) override
  {
    return basePrice * 1.2;
  }
};

class CalElectronics : public Calculator
{
public:
  double getTotal(double basePrice) override
  {
    return basePrice * 1.01;
  }
};

int main()
{
  CalElectronics calElectronics;
  Commodity *commdity = new Electronics(calElectronics);
  commdity->setPrice(100);
  print(commdity->getTotal());
}