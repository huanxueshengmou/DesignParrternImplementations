#include <iostream>
#include"my_print.cpp"
using namespace std;
class Color{
  public:
  Color(string color=""){
    this->color=color;
  }
  protected:
  string color="";
  public:
  string getColor(){
    return color;
  }
};
class rad:public Color{
  public:
  rad():Color("red"){ 
  }
};
class blue:public Color{
  public:
  blue():Color("blue"){ 
  }
};
class yellow:public Color{
  public:
  yellow():Color("yellow"){ 
  }
};
class green:public Color{
  public:
  green():Color("green"){ 
  }
};
class Shape {
  public:
  protected:
  string name;
  Color color;
  public:
  virtual void draw() = 0; 
};

class Rectangle : public Shape {
  public:
  Rectangle(Color color, string name="Rectangle") { 
    this->name = name;
    this->color = color;
  }
  void draw() override {
    printNonPln("draw a ", name, " which color is ", color.getColor());
    print();
  }
};

class Circle : public Shape {
  public:
  Circle(Color color, string name="Circle") { 
    this->name = name;
    this->color = color;
  }
  void draw() override {
    printNonPln("draw a ", name, " which color is ", color.getColor());
    print();
  }
};

int main() {
  rad rad;
  blue blue;
  yellow yellow;
  green grenn;
  Rectangle* r1 = new Rectangle(rad);
  Circle* c1 = new Circle(blue);
  r1->draw();
  c1->draw();

  Rectangle* r2 = new Rectangle(grenn, "CustomRectangle");
  Circle* c2 = new Circle(yellow, "CustomCircle");
  r2->draw();
  c2->draw();

  return 0;
}
