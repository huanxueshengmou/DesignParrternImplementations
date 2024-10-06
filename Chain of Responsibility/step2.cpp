#include <iostream>
#include <string>
#include <memory>
#include "my_print.cpp"
using namespace std;
using std::string;
using std::shared_ptr;
#define Maxrecursion 10
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
            printNonPln("The question is ", question, " and the default solution was used.");
            print();
            if (handler == nullptr) return;
            handler->handleRequest(question);
            return;
        }
    }
};

class ProblemSolution {
protected:
    shared_ptr<HandlerGeneralQuestion> handlerGeneralQuestion;
    shared_ptr<HandlerImportantQuestion> handlerImportantQuestion;
    shared_ptr<HandlerUrgentQuestion> handlerUrgentQuestion;
    shared_ptr<HandlerDefaultQuestion> handlerDefaultQuestion;
    shared_ptr<HandlerBase> handlerQuestion;
    shared_ptr<ProblemSolution> problemSolution;
    int level;
private:
    void initQuestiontype() {
        handlerGeneralQuestion = make_shared<HandlerGeneralQuestion>();
        handlerImportantQuestion = make_shared<HandlerImportantQuestion>();
        handlerUrgentQuestion = make_shared<HandlerUrgentQuestion>();
        handlerDefaultQuestion = make_shared<HandlerDefaultQuestion>();
    }
    void setQuestionLevel(shared_ptr<HandlerBase> &handlerQuestion) {
        handlerQuestion->setNext(handlerGeneralQuestion)
                      ->setNext(handlerImportantQuestion)
                      ->setNext(handlerUrgentQuestion)
                      ->setNext(handlerDefaultQuestion);
    }
public:
    shared_ptr<ProblemSolution> init() {
        handlerQuestion = make_shared<HandlerBase>();
        initQuestiontype();
        setQuestionLevel(handlerQuestion);
        return make_shared<ProblemSolution>(*this);
    }
    void questionSolution(string question) {
        handlerQuestion->handleRequest(question);
        print();
    }
    void setProblemServiceMode(shared_ptr<ProblemSolution> problemSolution) {
        this->problemSolution = problemSolution;
    }
    virtual shared_ptr<ProblemSolution> LevelProblem(int level,int layers) {
        if(layers>Maxrecursion){cerr << "No corresponding processing personnel found"<< std::endl;return nullptr;}
        if (this->level <= level) {
            print("CustomerServiceIssue:");
            print();
            return make_shared<ProblemSolution>(*this);
        } else {
            if (!problemSolution){print("No corresponding processing personnel found");return nullptr;}
            return problemSolution->LevelProblem(level,layers);
            layers++;
        }
    }
    void setLevel(int level){
        this->level=level;
    }
};

class TechnicalIssue : public ProblemSolution {
    public:
    shared_ptr<ProblemSolution> LevelProblem(int level,int layers) override{
        if(layers>Maxrecursion){cerr << "No corresponding processing personnel found"<< std::endl;return nullptr;}
        if (this->level <= level) {
            print("TechnicalIssue:");
            print();
            return make_shared<ProblemSolution>(*this);
        } else {
            if (!problemSolution){print("No corresponding processing personnel found");return nullptr;}
            return problemSolution->LevelProblem(level,layers);
            layers++;
        }
    }
};

class CustomerServiceIssue : public ProblemSolution {
    public:
    shared_ptr<ProblemSolution> LevelProblem(int level,int layers) override{
        if(layers>Maxrecursion){cerr << "No corresponding processing personnel found"<< std::endl;return nullptr;}
        if (this->level <= level) {
            print("CustomerServiceIssue:");
            print();
            return make_shared<ProblemSolution>(*this);
        } else {
            if (!problemSolution){print("No corresponding processing personnel found");return nullptr;}
            return problemSolution->LevelProblem(level,layers);
            layers++;
        }
    }
};
class UnifiedProcessingProcedure {
protected:
    shared_ptr<TechnicalIssue> technicalIssue;
    shared_ptr<CustomerServiceIssue> customerServiceIssue;
    bool mark = false;
private:
    void initList() {
        customerServiceIssue->setProblemServiceMode(technicalIssue);
    }
public:
    void init() {
        technicalIssue = make_shared<TechnicalIssue>();
        customerServiceIssue = make_shared<CustomerServiceIssue>();
        technicalIssue->setLevel(1);
        customerServiceIssue->setLevel(2);
        initList();
    }
    void solution(int level, string question) {
        printNonPln("UnifiedProcessingProcedure->");
            auto system=customerServiceIssue->LevelProblem(level,0);
            if(system==nullptr) return;
            system->init()->questionSolution(question);
    }
};

int main() {
    shared_ptr<UnifiedProcessingProcedure> UPP = make_shared<UnifiedProcessingProcedure>();
    UPP->init();
    UPP->solution(1, "");
    UPP->solution(1, "Urgent");
    UPP->solution(1, "General");
    UPP->solution(1, "Important");
    UPP->solution(1, "Emerald Ore");
    UPP->solution(2, "");
    UPP->solution(2, "Emerald Ore");
    UPP->solution(2, "General");
    UPP->solution(3, "Redstone Ore");
    UPP->solution(0, "error");
    return 0;
}

/*output:
    UnifiedProcessingProcedure->TechnicalIssue:


    UnifiedProcessingProcedure->TechnicalIssue:

    Urgent question solution

    UnifiedProcessingProcedure->TechnicalIssue:

    General question solution

    UnifiedProcessingProcedure->TechnicalIssue:

    Important question solution

    UnifiedProcessingProcedure->TechnicalIssue:

    The question is Emerald Ore and the default solution was used.

    UnifiedProcessingProcedure->CustomerServiceIssue:


    UnifiedProcessingProcedure->CustomerServiceIssue:

    The question is Emerald Ore and the default solution was used.

    UnifiedProcessingProcedure->CustomerServiceIssue:

    General question solution

    UnifiedProcessingProcedure->CustomerServiceIssue:

    The question is Redstone Ore and the default solution was used.

    UnifiedProcessingProcedure->No corresponding processing personnel found
*/