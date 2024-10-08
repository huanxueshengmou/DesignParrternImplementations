# 中介模式

## 问题 1： 假设你正在开发一个聊天应用，这个应用中有多个用户（User）可以相互发送消息。为了简化用户间的通信并降低他们之间的直接耦合，我们将引入一个中介者。请设计一个中介者接口`ChatMediator`和一个具体的用户类`User`。中介者接口应该包括注册用户和发送消息的方法，而用户类应该能发送和接收消息。 提示：`ChatMediator`接口可以包含`sendMessage`和`addUser`方法。`User`类需要有方法`send`和`receive`，其中`send`方法会通过中介者来发送消息给其他用户，`receive`方法用于接收来自其他用户的消息

![step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008152835.png)

![step1_gpt UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008153445.png)
