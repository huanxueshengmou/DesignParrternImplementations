#include <iostream>
#include <string>
#include "my_print.cpp"
class Number{
  public:
  Number(double num):num(num){}
  protected:
  double num;
  public:
  const double& getNum(){
    return this->num;
  }
};
class Expression{
  public:
  virtual double interpret(Number num1,Number num2)=0;
};

class AddExpression:Expression{
  public:
  double interpret(Number num1,Number num2){
    return num1.getNum()+num2.getNum();
  }
};
class SubtractExpression:Expression{
  public:
  double interpret(Number num1,Number num2){
    return num1.getNum()-num2.getNum();
  }
};

int main() {
    Number num1(10.5);
    Number num2(5.5);

    AddExpression addExpr;
    SubtractExpression subExpr;

    print("Addition Result: ",addExpr.interpret(num1, num2));
    print("Subtraction Result: ",subExpr.interpret(num1, num2));

}

/*OUTPUT:
  Addition Result: 
  16
  Subtraction Result: 
  5
*/