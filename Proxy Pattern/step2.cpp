
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
  string getUrl(){
    return this->url;
  }
};
class ProxyImage{
  public:
  ProxyImage(RealImage* realImage){
    this->realImage=realImage;
  }
  protected:
  RealImage* realImage;
  public:
  void initImage(){
    realImage->setUrl("loading...").display();
  }
  void setUrl(string url){
    realImage->setUrl(url);
  }
  void displayImage(){
    realImage->setUrl(realImage->getUrl()).display();
  }
};
int main(){
  RealImage* image=new RealImage("image of DesignPattern");
  ProxyImage* myProxyImage=new ProxyImage(image);
  print("Initializing... ");
  myProxyImage->initImage();
  myProxyImage->setUrl("https://learngitbranching.js.org/");
  print("Displaying...");
  myProxyImage->displayImage();
}
/* output:
  Initializing... 
  ![image of DesignPattern](loading...)
  Displaying...
  ![image of DesignPattern](https://learngitbranching.js.org/)
*/ 