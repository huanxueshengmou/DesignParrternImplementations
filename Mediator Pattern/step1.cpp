#include <iostream>
#include "my_print.cpp"
#include <string>
using std::string;

// 前向声明
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
  virtual void sendUser_1(Message *message) = 0;
  virtual void sendUser_2(Message *message) = 0;
  virtual void addUser1(User *user1) = 0;
  virtual void addUser2(User *user2) = 0;
};

class User
{
protected:
  Message myMessage;
  ChatMediator *chatMediator;

public:
  User(const string& message, ChatMediator *mediator) : myMessage(message), chatMediator(mediator) {}

  void send();
  void receive(Message *otherMessage);
};

class ChatMediatorUser : public ChatMediator
{
protected:
  User *user1;
  User *user2;

public:
  void addUser1(User *user1) override
  {
    this->user1 = user1;
  }
  void addUser2(User *user2) override
  {
    this->user2 = user2;
  }
  void sendUser_1(Message *message) override
  {
    print("user2 receive:");
    user2->receive(message);
  }
  void sendUser_2(Message *message) override
  {
    print("user1 receive:");
    user1->receive(message);
  }
};

void User::send()
{
  chatMediator->sendUser_1(&myMessage);
}

void User::receive(Message *otherMessage)
{
  print(otherMessage->getMessage());
}

int main()
{
  ChatMediatorUser mediator;
  User user1("Hello from User 1!", &mediator);
  User user2("Hello from User 2!", &mediator);

  mediator.addUser1(&user1);
  mediator.addUser2(&user2);

  user1.send();
  user2.send();

  return 0;
}
/*output
  user2 receive:
  Hello from User 1!
  user2 receive:
  Hello from User 2!
*/