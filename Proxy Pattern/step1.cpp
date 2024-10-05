#include <iostream>
#include "my_print.cpp"

using namespace std;


class Image{
  public:
  Image(string alternateText){
    url="";
    this->alternateText=alternateText;
    result="";
    }
  protected:
  string url;
  string alternateText;
  string result;
  public:
  virtual Image& display(){
    result="!["+alternateText+"]"+"("+url+")";
    print(result);
    return *this;
  }
};

class RealImage:Image{
  public:
  RealImage(string alternateText):Image(alternateText){
  }
  protected:
  bool isSetImage=false;
  public:
  Image& display()override{
    if(!isSetImage) return *this;
    result="!["+alternateText+"]"+"("+url+")";
    print(result);
    return *this;
  }
  Image& setUrl(string url){
    this->url=url;
    this->isSetImage=true;
    return *this;
  }
};
int main(){
  Image* image=new Image("image of DesignPattern");
  RealImage* realImage=new RealImage("image of DesignPattern");
  image->display();
  realImage->setUrl("https://learngitbranching.js.org/").display();
}
/* output:
  ![image of DesignPattern]()
  ![image of DesignPattern](https://learngitbranching.js.org/)
*/ 