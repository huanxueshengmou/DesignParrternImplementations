#include <iostream>
#include <string>
#include <vector>
#include "my_print.cpp"
using namespace std;

class Memento {
public:
    virtual ~Memento() {}
protected:
    friend class Editor;
    virtual string getState() const = 0;
    virtual void setState(const string& state) = 0;
};

class ConcreteMemento : public Memento {
private:
    string state;
public:
    ConcreteMemento(const string& state) : state(state) {}
    string getState() const override {
        return state;
    }
    void setState(const string& state) override {
        this->state = state;
    }
};

class Editor {
private:
    string text;
public:
    void setText(const string& text) {
        this->text = text;
    }
    void printText() const {
        print(this->text);
    }
    Memento* save() {
        return new ConcreteMemento(this->text);
    }
    void restore(Memento* memento) {
        this->text = static_cast<ConcreteMemento*>(memento)->getState();
        delete memento; // Optionally delete memento if no longer needed
    }
};

int main() {
    Editor editor;
    editor.setText("Initial state of the text editor.");
    editor.printText();

    Memento* memento = editor.save();
    editor.setText("New state of the text editor.");
    editor.printText();

    editor.restore(memento);
    editor.printText();

    return 0;
}

/*
Output:
Initial state of the text editor.
New state of the text editor.
Initial state of the text editor.
*/
