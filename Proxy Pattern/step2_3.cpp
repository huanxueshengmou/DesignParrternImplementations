
#include <iostream>
#include <regex>
#include "my_print.cpp"
#include  <string>
#include <memory>
using std::string;
using std::regex;
using namespace std;
using std::unique_ptr;

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
class ProxyImage {
protected:
    unique_ptr<Image> realImage;
public:
    ProxyImage(unique_ptr<Image> realImage) : realImage(std::move(realImage)) {}

    void initImage() {
        realImage->display("");
    }

    bool validateUrl(const std::string& url) {
        std::regex imageUrlRegex(R"(https?:\/\/.*\.(jpg|jpeg|png|gif|bmp|svg|webp|icon)$)", std::regex::icase);
        return std::regex_match(url, imageUrlRegex);
    }

    void displayImage(const std::string& url) {
        if (!validateUrl(url)) {
            realImage->display("Invalid image URL");
        }else{
            realImage->display(url);
        }
    }
};
int main(){
  unique_ptr<RealImage>image(new RealImage("image of DesignPattern"));
  unique_ptr<ProxyImage> myProxyImage(new ProxyImage(std::move(image)));
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
  ![image of DesignPattern](Invalid image URL)
*/ 