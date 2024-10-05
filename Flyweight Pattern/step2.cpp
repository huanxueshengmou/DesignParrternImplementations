#include <iostream>
#include <string>
#include <set>
#include "my_print.cpp"
using namespace std;
using std::set;
class Color
{
public:
  Color(string color) { this->color = color; }

protected:
  string color;

public:
  string getColor()
  {
    return color;
  }
};
class Style
{
public:
  Style(string style) { this->style = style; }

protected:
  string style;

public:
  string getStyle()
  {
    return style;
  }
};
class Red : public Color
{
  public:
  Red() : Color("red") {}
};
class Sans_serif : public Style
{
  public:
  Sans_serif() : Style("Sans_serif") {}
};
class Character
{
protected:
  float width;
  float height;
  float top;
  float left;
  Style *style;
  Color *color;

public:
  virtual void setTop(float top) = 0;
  virtual void setLeft(float left) = 0;
  virtual void setStyle(Style* style) = 0;
  virtual void setColor(Color* color) = 0;

public:
  Character(
      float width = 5,
      float height = 5,
      Style *style = new Style("default"),
      Color *color = new Color("black"))
  {
    this->width = width;
    this->height = height;
    this->top = 0;
    this->left = 0;
    this->style = style;
    this->color = color;
  }

public:
  virtual void drawCharacters()
  {
    printNonPln("Draw a character of size ", width,
          " color ", color->getColor(),
          " and style ", style->getStyle(),
          " at position ", top,
          " ", left,
          ".");
    left += width;
  }
};
class TxtCharacter : public Character
{
protected:
  float pageSize = 100;
public:
  void setTop(float newTop)
  {
    if (pageSize > newTop&&top<newTop)
      this->top = newTop;
  }
  void setLeft(float newLeft)
  {
    if (pageSize > newLeft&&left<newLeft)
      this->left = newLeft;
  }
  void setStyle(Style *style)
  {
    this->style = style;
  }
  void setColor(Color *color)
  {
    this->color = color;
  }
  void drawCharacters() override
  {
    printNonPln("Draw a character of size ", width,
          " color ", color->getColor(),
          " and style ", style->getStyle(),
          " at position ", top,
          " ", left,
          ".");
    left += width;
    if (left >= pageSize)
    {
      top += height;
      left = 0;
    }
  }
};
class CharacterFactory
{
  protected:
  set<Character*> myCharacterSet;
  Character* currCharacter;
  set<Color*> myColorSet;
  set<Style*> myStyleSet;
  public:
  void setCharacter(Character* character){
    currCharacter=character;
    myCharacterSet.insert(character);
  }
  void addColor(Color* color){
    myColorSet.insert(color);
  }
  void addStyle(Style* style){
    myStyleSet.insert(style);
  }
  bool checkCharacter(Character* character,Character*& callback){
    auto it = myCharacterSet.find(character);
    if(it!=myCharacterSet.end()){
      callback=*it;
      currCharacter=*it;
      return true;
    }
    return false;
  }
  Character* getCharacter(Character* character){
    Character* callback= nullptr;
    if(checkCharacter(character,callback)){
      return callback;
    }else{
      return nullptr;
    }
  }
  Character& setColor(Color* color){
    if(!currCharacter)throw std::runtime_error("Current character is null");
    auto it = myColorSet.find(color);
    if(it!=myColorSet.end()){
      currCharacter->setColor(*it);
    }else{
      currCharacter->setColor(color);
    }
    return *currCharacter;
  }
  Character& setStyle(Style* style){
    if(!currCharacter)throw std::runtime_error("Current character is null");
    auto it = myStyleSet.find(style);
    if(it!=myStyleSet.end()){
      currCharacter->setStyle(*it);
    }else{
      currCharacter->setStyle(style);
    }
    return *currCharacter;
  }
};
int main()
{
    CharacterFactory factory;
    TxtCharacter* txtCharacter = new TxtCharacter();
    Red* red = new Red();
    Sans_serif* sansSerif = new Sans_serif();

    // 在工厂中添加字符和样式
    factory.setCharacter(txtCharacter);
    factory.addColor(red);
    factory.addStyle(sansSerif);

    // 绘制初始字符
    txtCharacter->drawCharacters();
    print();
    
    // 绘制另一个字符
    txtCharacter->drawCharacters();
    print();

    // 应用工厂中的样式和颜色
    factory.setCharacter(txtCharacter);
    factory.setColor(red);
    factory.setStyle(sansSerif);
    txtCharacter->setLeft(50);
    txtCharacter->setTop(10);

    // 绘制修改后的字符
    txtCharacter->drawCharacters();
    print();

    TxtCharacter* txtCharacter2 = new TxtCharacter();
    Character* retrievedCharacter2 = factory.getCharacter(txtCharacter2);
    Character* retrievedCharacter = factory.getCharacter(txtCharacter);
    printNonPln("factory.getCharacter(txtCharacter2): ");
    if (retrievedCharacter2) {
        retrievedCharacter2->drawCharacters();
    }else{
      printNonPln("draw error");
    }
    print();
    printNonPln("factory.getCharacter(txtCharacter): ");
    if (retrievedCharacter) {
        retrievedCharacter->drawCharacters();
    }

    // 清理资源
    delete txtCharacter;
    delete txtCharacter2;
    delete red;
    delete sansSerif;

    return 0;
}

/*output:
  Draw a character of size 5 color black and style default at position 0 0.
  Draw a character of size 5 color black and style default at position 0 5.
  Draw a character of size 5 color red and style Sans_serif at position 10 50.
  factory.getCharacter(txtCharacter2): draw error
  factory.getCharacter(txtCharacter): Draw a character of size 5 color red and style Sans_serif at position 10 55.
*/ 
