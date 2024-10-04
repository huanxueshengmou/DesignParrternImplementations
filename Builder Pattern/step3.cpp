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
class CarBuilderBase {
public:
    virtual CarBuilderBase& set_engine(const string& engine) = 0;
    virtual CarBuilderBase& set_wheels(const string& wheels) = 0;
    virtual CarBuilderBase& set_doors(int doors) = 0;
    virtual Car build() = 0;
};

class StandardCarBuilder : public CarBuilderBase {
private:
    string engine = "Standard Engine";
    string wheels = "Standard Wheels";
    int doors = 4;

public:
    StandardCarBuilder& set_engine(const string& engine) override {
        this->engine = engine;
        return *this;
    }

    StandardCarBuilder& set_wheels(const string& wheels) override {
        this->wheels = wheels;
        return *this;
    }

    StandardCarBuilder& set_doors(int doors) override {
        this->doors = doors;
        return *this;
    }

    Car build() override {
        return Car(engine, wheels, doors);
    }
};

// CarDirector 负责指导如何构建汽车
class CarDirector {
public:
    Car build_sport_car(CarBuilderBase& builder) {
        return builder.set_engine("V8 Engine").set_wheels("Alloy Wheels").set_doors(2).build();
    }

    Car build_suv(CarBuilderBase& builder) {
        return builder.set_engine("SUV Engine").set_wheels("Big Wheels").set_doors(4).build();
    }
};


int main() {
    CarDirector director;
    StandardCarBuilder builder;
    Car sportCar = director.build_sport_car(builder);
    cout << "Sport Car Details:" << endl;
    cout << "Engine: " << sportCar.get_engine() << endl;
    cout << "Wheels: " << sportCar.get_wheels() << endl;
    cout << "Doors: " << sportCar.get_doors() << endl;
    cout << endl;
    builder = StandardCarBuilder();
    Car suv = director.build_suv(builder);
    cout << "SUV Details:" << endl;
    cout << "Engine: " << suv.get_engine() << endl;
    cout << "Wheels: " << suv.get_wheels() << endl;
    cout << "Doors: " << suv.get_doors() << endl;

    return 0;
}