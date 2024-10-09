#include <iostream>
#include <string>
#include "my_print.cpp"

using namespace std;

class Beverage{
  public:
  virtual void boilWater(){
    printNonPln("bubble and gurgle, ");
  };
  virtual void brew()=0;
  virtual void pourInCup(){
    printNonPln("The water poured from the jug into the glass. ");
  }
  virtual void addCondiments(string str)=0;
  virtual void prepareRecipe(string str){
    boilWater();
    brew();
    pourInCup();
    addCondiments(str);
  }
};
class Coffee:public Beverage{
  public:
  void brew(){
    printNonPln("There was a gentle tap-tap-tap as the coffee grounds settled into the mug. ");
  }
  void addCondiments(string str){
    printNonPln(str,"was dropped into the cup. ");
  }
};
class Tea:public Beverage{
  public:
  void brew(){
    print("A soft plop as the tea hit the bottom of the cup.");
  }
  void addCondiments(string str){
    printNonPln(str,"was dropped into the cup. ");
  }
};

// 测试 main 函数
int main() {
    // 创建 Coffee 对象
    Coffee coffee;
    print("Preparing Coffee Recipe:");
    coffee.prepareRecipe("Sugar");
    print();

    // 创建 Tea 对象
    Tea tea;
    print("Preparing Tea Recipe:");
    tea.prepareRecipe("Lemon");
    print();

    return 0;
}

/*output:
  reparing Coffee Recipe:
  bubble and gurgle, There was a gentle tap-tap-tap as the coffee grounds settled into the mug. The water poured from the jug into the glass. Sugarwas dropped into the cup. 
  Preparing Tea Recipe:
  bubble and gurgle, A soft plop as the tea hit the bottom of the cup.
  The water poured from the jug into the glass. Lemonwas dropped into the cup. 
*/ 