#include <iostream>
#include <string>
#include "my_print.cpp"

class GraphicVisitor; 
class Graphic {
public:
  virtual void accept(GraphicVisitor& visitor) = 0;
  virtual ~Graphic() {}
};


class GraphicVisitor {
public:
  virtual void visitCircle(class Circle& circle) = 0;
  virtual void visitRectangle(class Rectangle& rectangle) = 0;
  virtual void visitLine(class Line& line) = 0;
  virtual ~GraphicVisitor() {}
};


class Circle : public Graphic {
private:
  double radius;
public:
  Circle(double r) : radius(r) {}
  void accept(GraphicVisitor& visitor) override {
    visitor.visitCircle(*this);
  }
  double getRadius() const { return radius; }
};

class Rectangle : public Graphic {
private:
  double width;
  double height;
public:
  Rectangle(double w, double h) : width(w), height(h) {}
  void accept(GraphicVisitor& visitor) override {
    visitor.visitRectangle(*this);
  }
  double getWidth() const { return width; }
  double getHeight() const { return height; }
};

class Line : public Graphic {
private:
  double length;
public:
  Line(double l) : length(l) {}
  void accept(GraphicVisitor& visitor) override {
    visitor.visitLine(*this);
  }
  double getLength() const { return length; }
};
class DrawVisitor : public GraphicVisitor {
public:
  void visitCircle(Circle& circle) override {
    print("Drawing a circle with radius: ", circle.getRadius());
  }
  void visitRectangle(Rectangle& rectangle) override {
    print("Drawing a rectangle with width: ", rectangle.getWidth(), " and height: ", rectangle.getHeight());
  }
  void visitLine(Line& line) override {
    print("Drawing a line with length: ", line.getLength());
  }
};

class AreaCalculatorVisitor : public GraphicVisitor {
public:
  void visitCircle(Circle& circle) override {
    double area = 3.14159 * circle.getRadius() * circle.getRadius();
    print("Area of the circle: ", area);
  }
  void visitRectangle(Rectangle& rectangle) override {
    double area = rectangle.getWidth() * rectangle.getHeight();
    print("Area of the rectangle: ", area);
  }
  void visitLine(Line& line) override {
    print("Lines don't have areas, but here's the length: ", line.getLength());
  }
};
class PerimeterCalculatorVisitor : public GraphicVisitor {
public:
  void visitCircle(Circle& circle) override {
    double perimeter = 3.14159 * circle.getRadius() * 2;
    print("Perimeter of the circle: ", perimeter);
  }
  void visitRectangle(Rectangle& rectangle) override {
    double perimeter = rectangle.getWidth()*2 + rectangle.getHeight()*2;
    print("Perimeter of the rectangle: ", perimeter);
  }
  void visitLine(Line& line) override {
    print("the length: ", line.getLength());
  }
};


int main() {
    // Create some graphic objects
    Circle circle(5);         // Circle with radius 5
    Rectangle rectangle(4, 6); // Rectangle with width 4 and height 6
    Line line(10);            // Line with length 10

    // Create a visitor for drawing
    DrawVisitor drawVisitor;
    print("Drawing graphics:");
    circle.accept(drawVisitor);
    rectangle.accept(drawVisitor);
    line.accept(drawVisitor);

    // Create a visitor for calculating area
    AreaCalculatorVisitor areaCalculator;
    print();
    print("Calculating areas:");
    circle.accept(areaCalculator);
    rectangle.accept(areaCalculator);
    line.accept(areaCalculator);

    PerimeterCalculatorVisitor perimeterCalculator;
    print("Calculating perimeter:");
    circle.accept(perimeterCalculator);
    rectangle.accept(perimeterCalculator);
    line.accept(perimeterCalculator);
    return 0;
}
/*output:
  Drawing graphics:
  Drawing a circle with radius: 
  5
  Drawing a rectangle with width: 
  4
  and height: 
  6
  Drawing a line with length: 
  10

  Calculating areas:
  Area of the circle: 
  78.5397
  Area of the rectangle: 
  24
  Lines don't have areas, but here's the length: 
  10
  Calculating perimeter:
  Perimeter of the circle: 
  31.4159
  Perimeter of the rectangle: 
  20
  the length: 
  10
*/ 