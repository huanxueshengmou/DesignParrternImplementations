
#include <iostream>
#include <memory>
#include "my_print.cpp"
using std::shared_ptr;
using std::make_shared;
class Expression
{
public:
  virtual double interpret() = 0;
};

class Number : public Expression
{
private:
  double num;

public:
  Number(double num) : num(num) {}
  double interpret() override
  {
    return num;
  }
};

class BinaryExpression : public Expression
{
protected:
  shared_ptr<Expression> left;
  shared_ptr<Expression> right;

public:
  BinaryExpression(shared_ptr<Expression> left, shared_ptr<Expression> right)
      : left(left), right(right) {}
};

class AddExpression : public BinaryExpression
{
public:
  AddExpression(shared_ptr<Expression> left, shared_ptr<Expression> right)
      : BinaryExpression(left, right) {}
  double interpret() override
  {
    return left->interpret() + right->interpret();
  }
};

class SubtractExpression : public BinaryExpression
{
public:
  SubtractExpression(shared_ptr<Expression> left, shared_ptr<Expression> right)
      : BinaryExpression(left, right) {}
  double interpret() override
  {
    return left->interpret() - right->interpret();
  }
};

int main()
{
  auto num10 =make_shared<Number>(10);
  auto num5 =make_shared<Number>(5);
  auto num3 =make_shared<Number>(3);
  auto num2 =make_shared<Number>(2);
  auto num1 =make_shared<Number>(1);

  auto subExpr1 =make_shared<SubtractExpression>(num5, num3);
  auto addExpr1 =make_shared<AddExpression>(num10, subExpr1);

  auto addExpr2 =make_shared<AddExpression>(num2, num1);
  auto finalExpr =make_shared<AddExpression>(addExpr1, addExpr2);

  print(finalExpr->interpret());

  return 0;
}

// Output:  15
