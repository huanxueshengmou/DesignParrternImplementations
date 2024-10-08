# 责任链模式

## 问题 1： 假设你正在开发一个问题报告系统，系统可以处理不同级别的问题（如普通问题、重要问题、紧急问题）。请设计一个抽象的处理者类（Handler），它包含一个方法来处理请求（handleRequest），并且可以设置下一个处理者（setNext）

提示：你可以创建一个基类Handler，其中包含一个成员变量来引用链中的下一个Handler，并定义一个虚函数handleRequest用于在子类中实现具体处理逻辑

![COR step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241006144350.png)

## 问题 2： 现在，假设问题报告系统需要处理更多类型的问题，比如技术问题和客户服务问题。如何扩展现有的责任链模式来包括这些新类型的问题处理？

提示：设计两个新的处理器类，分别对应技术问题和客户服务问题。考虑问题的优先级和处理的顺序，确保链中的顺序能够正确反映这些优先级

![COR step2 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241006144914.png)
