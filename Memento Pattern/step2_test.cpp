#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "my_print.cpp"
using namespace std;

class Memento
{
public:
  virtual ~Memento() {}

protected:
  friend class Editor;
  virtual string getState() const = 0;
  virtual void setState(const string &state) = 0;
};

class ConcreteMemento : public Memento
{
private:
  string state;

public:
  ConcreteMemento(const string &state) : state(state) {}
  string getState() const override
  {
    return state;
  }
  void setState(const string &state) override
  {
    this->state = state;
  }
};

class Editor
{
private:
  string text;

public:
  void setText(const string &text)
  {
    this->text = text;
  }
  void printText() const
  {
    print(this->text);
  }
  Memento *save()
  {
    return new ConcreteMemento(this->text);
  }
  void restore(Memento *memento)
  {
    this->text = static_cast<ConcreteMemento *>(memento)->getState();
  }
};

class Caretaker
{
protected:
  stack<Memento *> deletedMemento;
  stack<Memento *> undoMemento;

public:
  stack<Memento *> &getDeletedMemento()
  {
    return deletedMemento;
  }
  stack<Memento *> &getUndoMemento()
  {
    return undoMemento;
  }
  stack<Memento *> &addDeleteMemento(Memento *memento)
  {
    deletedMemento.push(memento);
    return deletedMemento;
  }
  stack<Memento *> &addUndoMemento(Memento *memento)
  {
    undoMemento.push(memento);
    return undoMemento;
  }
  stack<Memento *> &POPDeleteMemento()
  {
    if (deletedMemento.empty())
      return deletedMemento;
    deletedMemento.pop();
    return deletedMemento;
  }
  stack<Memento *> &POPUndoMemento()
  {
    if (undoMemento.empty())
      return undoMemento;
    undoMemento.pop();
    return undoMemento;
  }
  void destroyUndoMemento (){
     while (!getUndoMemento().empty())
      {
        delete getUndoMemento().top();
        POPUndoMemento();
      }
  }
  void destroyDeletedMemento (){
    while (!getDeletedMemento().empty())
      {
        delete getDeletedMemento().top();
        POPDeleteMemento();
      }
  }
};

int main() {
    Editor editor;
    Caretaker caretaker;

    // 设置初始文本
    editor.setText("初始文本");
    editor.printText(); // 输出: 初始文本

    // 保存初始状态
    Memento* memento1 = editor.save();
    caretaker.addUndoMemento(memento1);

    // 修改文本并打印
    editor.setText("第二版文本");
    editor.printText(); // 输出: 第二版文本

    // 保存第二状态
    Memento* memento2 = editor.save();
    caretaker.addUndoMemento(memento2);

    // 更多修改
    editor.setText("第三版文本");
    editor.printText(); // 输出: 第三版文本

    // 保存第三状态
    Memento* memento3 = editor.save();
    caretaker.addUndoMemento(memento3);

    // 修改为第四版
    editor.setText("第四版文本");
    editor.printText(); // 输出: 第四版文本

    // 撤销到最后一次修改，回到第三版
    editor.restore(caretaker.getUndoMemento().top());
    caretaker.POPUndoMemento();
    editor.printText(); // 输出: 第三版文本

    // 撤销到第二版
    editor.restore(caretaker.getUndoMemento().top());
    caretaker.POPUndoMemento();
    editor.printText(); // 输出: 第二版文本

    // 撤销到初始状态
    editor.restore(caretaker.getUndoMemento().top());
    caretaker.POPUndoMemento();
    editor.printText(); // 输出: 初始文本

    // 重做到第二版（仅作为示例，需要实现）
    // 这需要不同的处理和重做栈，当前代码中未实现。

    // 清理Memento以防止内存泄漏
    caretaker.destroyDeletedMemento();
    return 0;
}

/*
初始文本
第二版文本
第三版文本
第四版文本
第三版文本
第二版文本
初始文本
*/