#include <iostream>
#include <string>
#include "my_print.cpp"
using namespace std;
using std::string;
class Commodity
{
protected:
  string name;
  double basePrice;
  double taxe;

public:
  virtual double getPrice()
  {
    return basePrice;
  }
  virtual double getTaxe()
  {
    return taxe;
  }
  virtual void setPrice(double price)
  {
    basePrice = price;
  }
  virtual void setTaxe(double new_taxe)
  {
    taxe = new_taxe;
  }
  virtual string getName()
  {
    return name;
  }
};
class Electronics : public Commodity
{
public:
  Electronics() { name = "Electronics"; }
  double getPrice() override
  {
    return basePrice;
  }
  double getTaxe() override
  {
    return taxe;
  }
  void setPrice(double price) override
  {
    basePrice = price;
  }
  void setTaxe(double new_taxe) override
  {
    taxe = new_taxe;
  }
  string getName() override
  {
    return name;
  }
};
class FoodProducts : public Commodity
{
public:
  FoodProducts() { name = "FoodProducts"; }
  double getPrice()
  {
    return basePrice;
  }
  double getTaxe()
  {
    return taxe;
  }
  void setPrice(double price) override
  {
    basePrice = price;
  }
  void setTaxe(double new_taxe) override
  {
    taxe = new_taxe;
  }
  string getName() override
  {
    return name;
  }
};
class Calculator
{
public:
  virtual double calculate(Commodity &commodity) = 0;
};
class CalCommodity : public Calculator
{
public:
  double calculate(Commodity &commodity)
  {
    if (commodity.getName() == "Electronics")
    {
      commodity.setTaxe(0.1);
      return commodity.getPrice() * (1 + commodity.getTaxe());
    }
    if (commodity.getName() == "FoodProducts")
    {
      commodity.setTaxe(0.02);
      return commodity.getPrice() * (1 + commodity.getTaxe());
    }
    return -1;
  }
};
int main()
{
  Calculator *my_calculator = new CalCommodity();
  Commodity foodProducts = FoodProducts();
  foodProducts.setPrice(100);
  double total = my_calculator->calculate(foodProducts);
  print(total);
}
