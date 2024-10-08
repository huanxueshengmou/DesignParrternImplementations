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

int main()
{
  Editor editor;
  Caretaker caretaker;

  // Set initial text
  editor.setText("Initial text");
  editor.printText(); // Outputs: Initial text

  // Save initial state
  Memento *memento1 = editor.save();
  caretaker.addUndoMemento(memento1);

  // Change text and print
  editor.setText("Second version of text");
  editor.printText(); // Outputs: Second version of text

  // Save second state
  Memento *memento2 = editor.save();
  caretaker.addUndoMemento(memento2);

  // More changes
  editor.setText("Third version of text");
  editor.printText(); // Outputs: Third version of text

  // Undo last change
  editor.restore(caretaker.getUndoMemento().top());
  caretaker.POPUndoMemento();
  editor.printText(); // Outputs: Second version of text

  // Undo to initial state
  editor.restore(caretaker.getUndoMemento().top());
  caretaker.POPUndoMemento();
  editor.printText(); // Outputs: Initial text

  // Cleaning up Mementos to prevent memory leaks
  caretaker.destroyUndoMemento();
  caretaker.destroyDeletedMemento();

  return 0;  
}

/*
Output:
Initial text
Second version of text
Third version of text
Second version of text
Initial text 
*/