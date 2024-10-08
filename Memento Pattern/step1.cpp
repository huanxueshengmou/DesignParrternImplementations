#include <iostream>
#include <string>
#include <vector>
#include "my_print.cpp"
using namespace std;
class Memento
{
};
class MementoText : public Memento
{
public:
  MementoText(string data) : data(data) {}

protected:
  string data;

public:
  string getDate()
  {
    return data;
  }
};

class Editor
{
protected:
  string data;

public:
  virtual MementoText save() = 0;
  virtual void restore(MementoText *mementoText) = 0;
};
class EditorText : public Editor
{
public:
  MementoText save()
  {
    MementoText mementoText(data);
    return mementoText;
  }
  void restore(MementoText *mementoText)
  {
    this->data = mementoText->getDate();
  }
  void setDate(string data)
  {
    this->data = data;
  }
  void printDate()
  {
    print(data);
  }
};

int main()
{
  EditorText editor;
  print();
  editor.setDate("Suppose you are developing a simple text editor");
  editor.printDate();
  print();
  auto memory = editor.save();
  editor.setDate(".");
  editor.printDate();
  print();
  editor.restore(&memory);
  editor.printDate();
  print();
}

/*output:
Suppose you are developing a simple text editor

.

Suppose you are developing a simple text editor

*/