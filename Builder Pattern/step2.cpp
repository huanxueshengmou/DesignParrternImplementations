#include <iostream>
#include "my_print.cpp"
#include <string>
using namespace std;

class Car
{
private:
  string engine;
  string wheels;
  int doors;

public:
  Car() : engine("Standard Engine"), wheels("Standard Wheels"), doors(4) {}
  Car(string engine, string wheels, int doors) : engine(engine), wheels(wheels), doors(doors) {}

public:
  string get_engine()
  {
    return engine;
  }
  string get_wheels()
  {
    return wheels;
  }
  int get_doors()
  {
    return doors;
  }
};
class CarBuilder
{
private:
  string engine;
  string wheels;
  int doors;

public:
  CarBuilder &set_engine(string engine)
  {
    this->engine = engine;
    return *this;
  }
  CarBuilder &set_wheels(string wheels)
  {
    this->wheels = wheels;
    return *this;
  }
  CarBuilder &set_doors(int doors)
  {
    this->doors = doors;
    return *this;
  }
  Car getCar()
  {
    return Car(engine, wheels, doors);
  }
};

int main()
{
  CarBuilder carBuilder;
  carBuilder.set_doors(10).set_engine("V8 Engine").set_wheels("Alloy Wheels");
  Car myCar = carBuilder.getCar();
  print(myCar.get_doors());
  print(myCar.get_engine());
  print(myCar.get_wheels());
}