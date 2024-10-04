
#include <iostream>
#include <string>
#include <memory>
#include "my_print.cpp"
using namespace std;

class Beverage {
protected:
    bool pure = false;
    string beverage_description;
    double beverage_cost;
public:
    Beverage(string description, double cost) : beverage_description(description), beverage_cost(cost) {}

    virtual string getDescription() {
        return beverage_description;
    }

    virtual double cost() {
        return beverage_cost;
    }

    virtual void setDescription(string new_str) {
        if (!pure)
            beverage_description += " with added " + new_str;
        else
            beverage_description += new_str;
    }
};

class Coffee : public Beverage {
public:
    Coffee() : Beverage("咖啡", 12.0) {}
};

class CondimentDecorator : public Beverage {
protected:
    unique_ptr<Beverage> beverage;
public:
    CondimentDecorator(string description, double cost) : Beverage(description, cost) {}

    void addBeverage(unique_ptr<Beverage> new_beverage) {
        beverage = move(new_beverage);
    }

    void addSugar() {
        beverage->setDescription("sugar");
        beverage_cost += 1.0; // 假设糖的成本是1.0
    }

    string getDescription() override {
        return beverage->getDescription();
    }

    double cost() override {
        return beverage->cost() + beverage_cost;
    }
};

int main() {
    unique_ptr<Beverage> coffee = make_unique<Coffee>();
    unique_ptr<CondimentDecorator> condimentDecorator = make_unique<CondimentDecorator>("", 0);
    condimentDecorator->addBeverage(move(coffee));
    condimentDecorator->addSugar();
    print(condimentDecorator->getDescription());
    print(condimentDecorator->cost());

    return 0;
}