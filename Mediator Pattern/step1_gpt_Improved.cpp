#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User;
class ChatMediator;

class Message
{
protected:
  string message;

public:
  Message(string newMessage) : message(newMessage) {}
  string getMessage()
  {
    return message;
  }
};

class ChatMediator
{
public:
  virtual void sendMessage(const string &msg, User *user) = 0;
  virtual void addUser(User *user) = 0;
};

class User
{
protected:
  string name;
  ChatMediator *chatMediator;

public:
  User(const string &name, ChatMediator *mediator) : name(name), chatMediator(mediator)
  {
    mediator->addUser(this);
  }

  virtual void send(const string &message) = 0;
  virtual void receive(const string &message) = 0;
};

class ConcreteChatMediator : public ChatMediator
{
private:
  vector<User *> users;

public:
  void addUser(User *user) override
  {
    users.push_back(user);
  }

  void sendMessage(const string &msg, User *origin) override
  {
    for (auto user : users)
    {
      if (user != origin)
      { // Do not send message to the sender
        user->receive(msg);
      }
    }
  }
};

class ConcreteUser : public User
{
public:
  ConcreteUser(const string &name, ChatMediator *mediator) : User(name, mediator) {}

  void send(const string &message) override
  {
    cout << name << " sends: " << message << endl;
    chatMediator->sendMessage(message, this);
  }

  void receive(const string &message) override
  {
    cout << name << " receives: " << message << endl;
  }
};

int main()
{
  ConcreteChatMediator mediator;
  User *user1 = new ConcreteUser("User 1", &mediator);
  User *user2 = new ConcreteUser("User 2", &mediator);

  user1->send("Hello from User 1!");
  user2->send("Hello from User 2!");

  delete user1;
  delete user2;

  return 0;
}
/*output:
User 1 sends: Hello from User 1!
User 2 receives: Hello from User 1!
User 2 sends: Hello from User 2!
User 1 receives: Hello from User 2!
*/ 