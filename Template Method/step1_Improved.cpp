#include <iostream>
#include <string>
#include "my_print.cpp"

using namespace std;

class Beverage {
public:
    void prepareRecipe(const string& condiment) {
        boilWater();
        brew();
        pourInCup();
        if (customerWantsCondiments()) {
            addCondiments(condiment);
        }
    }
protected:
    void boilWater() {
        print("Boiling water...");
    }
    virtual void brew() = 0;
    void pourInCup() {
        print("Pouring into cup...");
    }
    virtual void addCondiments(const string& condiment) = 0;
    virtual bool customerWantsCondiments() { return true; } // Hook method
};

class Coffee : public Beverage {
protected:
    void brew() override {
        print("Dripping Coffee through filter...");
    }
    void addCondiments(const string& condiment) override {
        print("Adding " + condiment + " to coffee...");
    }
};

class Tea : public Beverage {
protected:
    void brew() override {
        print("Steeping the tea...");
    }
    void addCondiments(const string& condiment) override {
        print("Adding " + condiment + " to tea...");
    }
    bool customerWantsCondiments() override {
        // Here, you could ask the user or use some logic to decide
        return false; // Assuming the customer doesn't want condiments
    }
};

int main() {
    Coffee coffee;
    Tea tea;

    print("Making coffee...");
    coffee.prepareRecipe("Sugar");

    print("Making tea...");
    tea.prepareRecipe("Lemon");

    return 0;
}

