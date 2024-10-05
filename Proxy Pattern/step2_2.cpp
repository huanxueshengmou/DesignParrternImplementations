
#include <iostream>
#include "my_print.cpp"

using namespace std;


class Image{
  public:
  virtual void display(string url)=0;
};

class RealImage:Image{
  public:
  RealImage(string alternateText){
    this->alternateText=alternateText;
    result="";
  }
  protected:
  bool isSetImage=false;
  string alternateText;
  string result;
  public:
  void display(string url){
    if(url==""){
    result="!["+alternateText+"]"+"("+"loading..."+")";
    print(result);
    }else{
      result="!["+alternateText+"]"+"("+url+")";
    print(result);
    }
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
    realImage->display("");
  }
  void displayImage(string url){
    realImage->display(url);
  }
};
int main(){
  RealImage* image=new RealImage("image of DesignPattern");
  ProxyImage* myProxyImage=new ProxyImage(image);
  print("Initializing... ");
  myProxyImage->initImage();
  print("Displaying...");
  myProxyImage->displayImage("https://learngitbranching.js.org/icon");
}
/* output:
  Initializing... 
  ![image of DesignPattern](loading...)
  Displaying...
  ![image of DesignPattern](https://learngitbranching.js.org/icon)
*/ 