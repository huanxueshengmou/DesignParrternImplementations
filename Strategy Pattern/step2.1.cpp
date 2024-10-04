#include <iostream>
#include <string>
#include <memory>
#include "my_print.cpp"

using namespace std;

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
  unique_ptr<Calculator> calculator;

public:
  Commodity(string name, unique_ptr<Calculator> new_calculator)
    : name(name), calculator(move(new_calculator)) {}

  virtual double getPrice() const
  {
    return basePrice;
  }

  virtual void setPrice(double price)
  {
    basePrice = price;
  }

  virtual string getName() const
  {
    return name;
  }

  virtual double getTotal() const
  {
    return calculator->getTotal(basePrice);
  }
};

class Electronics : public Commodity
{
public:
  Electronics(unique_ptr<Calculator> new_calculator)
    : Commodity("Electronics", move(new_calculator)) {}
};

class FoodProducts : public Commodity
{
public:
  FoodProducts(unique_ptr<Calculator> new_calculator)
    : Commodity("FoodProducts", move(new_calculator)) {}
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
  auto foodCalculator = make_unique<CalFoodProducts>();
  auto electronicsCalculator = make_unique<CalElectronics>();

  unique_ptr<Commodity> foodProduct = make_unique<FoodProducts>(move(foodCalculator));
  unique_ptr<Commodity> electronics = make_unique<Electronics>(move(electronicsCalculator));

  foodProduct->setPrice(100);
  electronics->setPrice(100);

  print(foodProduct->getTotal());
  print(electronics->getTotal());

  return 0;
}