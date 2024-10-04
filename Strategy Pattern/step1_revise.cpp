#include <iostream>
#include <string>
using namespace std;
using std::string;
class TaxStrategy {
public:
    virtual double calculateTax() = 0;  // 纯虚函数，定义税率计算
};
class ElectronicsTaxStrategy : public TaxStrategy {
public:
    double calculateTax() override {
        return 0.1;  // 电子产品税率 10%
    }
};

class FoodProductsTaxStrategy : public TaxStrategy {
public:
    double calculateTax() override {
        return 0.02;  // 食品产品税率 2%
    }
};

class Commodity {
protected:
    string name;
    double basePrice;
    TaxStrategy* taxStrategy;  // 税率策略

public:
    Commodity(TaxStrategy* strategy) : taxStrategy(strategy) {}  // 构造时指定税率策略
    
    virtual double getPrice() {
        return basePrice;
    }

    double getTaxe() {
        return taxStrategy->calculateTax();  // 使用策略来计算税率
    }

    void setPrice(double price) {
        basePrice = price;
    }

    string getName() {
        return name;
    }
};
class Electronics : public Commodity {
public:
    Electronics() : Commodity(new ElectronicsTaxStrategy()) {}  // 使用电子产品税率策略
};

class FoodProducts : public Commodity {
public:
    FoodProducts() : Commodity(new FoodProductsTaxStrategy()) {}  // 使用食品产品税率策略
};
class CalCommodity {
public:
    double calculate(Commodity& commodity) {
        return commodity.getPrice() * (1 + commodity.getTaxe());  // 使用策略计算
    }
};
int main() {
    // 创建电子产品实例
    Electronics electronics;
    electronics.setPrice(100.0);  // 设置电子产品的基本价格为100

    // 创建食品产品实例
    FoodProducts foodProducts;
    foodProducts.setPrice(50.0);  // 设置食品产品的基本价格为50

    // 创建计算商品总价的实例
    CalCommodity calCommodity;

    // 计算电子产品的总价
    double electronicsTotalPrice = calCommodity.calculate(electronics);
    cout << "Electronics Total Price: " << electronicsTotalPrice << endl;

    // 计算食品产品的总价
    double foodProductsTotalPrice = calCommodity.calculate(foodProducts);
    cout << "Food Products Total Price: " << foodProductsTotalPrice << endl;

    return 0;
}
