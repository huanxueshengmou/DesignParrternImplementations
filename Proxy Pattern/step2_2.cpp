
#include <iostream>
#include <regex>
#include "my_print.cpp"
#include  <string>
using std::string;
using std::regex;
using namespace std;


class Image{
  public:
  virtual void display(string url)=0;
};

class RealImage:public Image{
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
  /*
    https?:\/\/：匹配 http:// 或 https://。
    .*：匹配任意字符（除了换行符）零次或多次。
    \.(jpg|jpeg|png|gif|bmp|svg|webp|icon)：匹配以图片格式结尾的部分。
    $：表示字符串的结尾。
  */
  bool isImageUrl(const std::string& url) {
    regex imageUrlRegex(R"(https?:\/\/.*\.(jpg|jpeg|png|gif|bmp|svg|webp|icon)$)",regex::icase);
    return regex_match(url, imageUrlRegex);
  }
  void display(string url){
    if(url==""){
    result="!["+alternateText+"]"+"("+"loading..."+")";
    print(result);
    }else{
      if(isImageUrl(url)){
        result="!["+alternateText+"]"+"("+url+")";
        print(result);
      }
      else{
        result="!["+alternateText+"]"+"("+"nullpter"+")";
        print(result);
      }
    }
  }
};
class ProxyImage{
  public:
  ProxyImage(Image* realImage){
    this->realImage=realImage;
  }
  protected:
  Image* realImage;
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
  myProxyImage->displayImage("https://learngitbranching.js.org/xx.icon");
  myProxyImage->displayImage("https://learngitbranching.js.org/i");
}
/* output:
  Initializing... 
  ![image of DesignPattern](loading...)
  Displaying...
  ![image of DesignPattern](https://learngitbranching.js.org/xx.icon)
  ![image of DesignPattern](nullpter)
*/ 