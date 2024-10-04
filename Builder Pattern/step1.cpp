#include <iostream>
#include <string>
#include "my_print.cpp"
using namespace std;
using std::string;
class Car {
private:
    string engine;
    string wheels;
    int doors;
public:
    Car() : engine("Standard Engine"), wheels("Standard Wheels"), doors(4) {}
    Car(string engine, string wheels, int doors) : engine(engine), wheels(wheels), doors(doors) {}

public:
    string get_engine(){
      return engine;
    }
    string get_wheels(){
      return wheels;
    }
    int get_doors(){
      return doors;
    }
};


int main(){
  Car car;
  print(car.get_engine());
  print(car.get_wheels());
  print(car.get_doors());
  Car car_2("V8 Engine","Alloy Wheels",2);
  print(car_2.get_engine());
  print(car_2.get_wheels());
  print(car_2.get_doors());
}