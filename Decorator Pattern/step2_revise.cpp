
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Beverage {
public:
    virtual string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() = default;  // 基类的析构函数应为虚函数
};

// 具体的咖啡类
class Coffee : public Beverage {
public:
    string getDescription() const override {
        return "咖啡";
    }

    double cost() const override {
        return 12.0;
    }
};

// 装饰器基类
class CondimentDecorator : public Beverage {
protected:
    unique_ptr<Beverage> beverage;
public:
    CondimentDecorator(unique_ptr<Beverage> b) : beverage(move(b)) {}

    virtual string getDescription() const override = 0;
    virtual double cost() const override = 0;
};

// 具体的糖装饰器
class SugarDecorator : public CondimentDecorator {
public:
    SugarDecorator(unique_ptr<Beverage> b) : CondimentDecorator(move(b)) {}

    string getDescription() const override {
        return beverage->getDescription() + " with sugar";
    }

    double cost() const override {
        return beverage->cost() + 1.0;  // 加糖费用
    }
};

// 具体的牛奶装饰器
class MilkDecorator : public CondimentDecorator {
public:
    MilkDecorator(unique_ptr<Beverage> b) : CondimentDecorator(move(b)) {}

    string getDescription() const override {
        return beverage->getDescription() + " with milk";
    }

    double cost() const override {
        return beverage->cost() + 2.0;  // 加牛奶费用
    }
};

int main() {
    // 创建一杯咖啡
    unique_ptr<Beverage> coffee = make_unique<Coffee>();
    
    // 给咖啡加糖
    coffee = make_unique<SugarDecorator>(move(coffee));
    
    // 再给咖啡加牛奶
    coffee = make_unique<MilkDecorator>(move(coffee));

    // 输出咖啡的描述和价格
    cout << coffee->getDescription() << endl;   // 输出: 咖啡 with sugar with milk
    cout << "价格: " << coffee->cost() << endl; // 输出: 12 + 1 + 2 = 15

    return 0;
}
