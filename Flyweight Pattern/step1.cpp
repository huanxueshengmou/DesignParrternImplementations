#include <iostream>
#include <string>
#include "my_print.cpp"
using namespace std;
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
int main()
{
  TxtCharacter *txtcharacter = new TxtCharacter();
  txtcharacter->drawCharacters();
  print();
  txtcharacter->drawCharacters();
  print();
  Red red;
  Sans_serif sans_serif;
  txtcharacter->setColor(&red);
  txtcharacter->setLeft(50);
  txtcharacter->setTop(10);
  txtcharacter->setStyle(&sans_serif);
  txtcharacter->drawCharacters();
  delete txtcharacter;
}


/* output:
Draw a character of size 5 color black and style default at position 0 0.
Draw a character of size 5 color black and style default at position 0 5.
Draw a character of size 5 color red and style Sans_serif at position 10 50.
*/