#include <iostream>
#include <string>
#include <memory>
#include "my_print.cpp"
using namespace std;
using std::string;
using std::shared_ptr;

class Handler {
public:
    virtual void handleRequest(string question) = 0;
    virtual shared_ptr<Handler> setNext(shared_ptr<Handler> handler) = 0;
};

class HandlerBase : public Handler {
protected:
    shared_ptr<Handler> handler;
public:
    shared_ptr<Handler> setNext(shared_ptr<Handler> handler) {
        this->handler = handler;
        return handler;
    }
    void handleRequest(string question) {
        if (question == "") return;
        if (handler == nullptr) return;
        handler->handleRequest(question);
    }
};

class HandlerGeneralQuestion : public HandlerBase {
public:
    void handleRequest(string question) {
        if (question == "General") {
            print("General question solution");
            return;
        } else {
            if (handler == nullptr) return;
            handler->handleRequest(question);
            return;
        }
    }
};

class HandlerImportantQuestion : public HandlerBase {
public:
    void handleRequest(string question) {
        if (question == "Important") {
            print("Important question solution");
            return;
        } else {
            if (handler == nullptr) return;
            handler->handleRequest(question);
            return;
        }
    }
};

class HandlerUrgentQuestion : public HandlerBase {
public:
    void handleRequest(string question) {
        if (question == "Urgent") {
            print("Urgent question solution");
            return;
        } else {
            if (handler == nullptr) return;
            handler->handleRequest(question);
            return;
        }
    }
};
class HandlerDefaultQuestion : public HandlerBase {
public:
    void handleRequest(string question) {
        if (question == "") {
            print("The question is null");
            return;
        } else {
            printNonPln("The question is ",question," and the default solution was used.");
            if (handler == nullptr) return;
            handler->handleRequest(question);
            return;
        }
    }
};

int main() {
    shared_ptr<HandlerBase> handlerQuestion = make_shared<HandlerBase>();
    shared_ptr<HandlerGeneralQuestion> handlerGeneralQuestion = make_shared<HandlerGeneralQuestion>();
    shared_ptr<HandlerImportantQuestion> handlerImportantQuestion = make_shared<HandlerImportantQuestion>();
    shared_ptr<HandlerUrgentQuestion> handlerUrgentQuestion = make_shared<HandlerUrgentQuestion>();
    shared_ptr<HandlerDefaultQuestion> handlerDefaultQuestion = make_shared<HandlerDefaultQuestion>();

    handlerQuestion->setNext(handlerGeneralQuestion)
                   ->setNext(handlerImportantQuestion)
                   ->setNext(handlerUrgentQuestion)
                   ->setNext(handlerDefaultQuestion);

    handlerQuestion->handleRequest("");
    handlerQuestion->handleRequest("Urgent");
    handlerQuestion->handleRequest("General");
    handlerQuestion->handleRequest("Important");
    handlerQuestion->handleRequest("Emerald Ore");

    return 0;
}
/*output:
    Urgent question solution
    General question solution
    Important question solution
    The question is Emerald Ore and the default solution was used.
*/