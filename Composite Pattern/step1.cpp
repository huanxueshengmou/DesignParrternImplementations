#include <iostream>
#include <string>
#include <vector>
#include "my_print.cpp"
using namespace std;

class Graphic{
  public:
  Graphic(string name){
    this->name=name;
  }
  protected:
  string name;
  public:
  virtual void drow()=0;
};
class Circle:public Graphic{
  public:
  Circle():Graphic("Circle"){}
  public:
  virtual void drow(){
    printNonPln("drow a ",name);
  }
};
class Rectangle:public Graphic{
  public:
  Rectangle():Graphic("Rectangle"){}
  public:
  virtual void drow(){
    printNonPln("drow a ",name);
  }
};
class GraphicGroup:public Graphic{
  public:
  GraphicGroup():Graphic("GraphicGroup"){}
  protected:
  vector<Graphic*> graphicGroup;
  public:
  void pushGraphic(Graphic* graphic){
    graphicGroup.push_back(graphic);
  }
  Graphic* getGraphic(){
    Graphic* temp=graphicGroup.back();
    graphicGroup.pop_back();
    return temp;
  }
  void drow(){
    if(graphicGroup.empty()) return;
    for(auto graphic : graphicGroup){
      print();
      graphic->drow();
    }
  }
};
int main(){
  Circle* c=new Circle();
  Rectangle* r=new Rectangle();
  GraphicGroup* gg=new GraphicGroup();
  GraphicGroup* gg2=new GraphicGroup();
  c->drow();
  print();
  r->drow();
  gg->pushGraphic(c);
  gg->pushGraphic(r);
  print();
  gg->drow();
  gg2->pushGraphic(gg);
  gg2->pushGraphic(c);
  gg2->pushGraphic(r);
  print();
  gg2->drow();
}