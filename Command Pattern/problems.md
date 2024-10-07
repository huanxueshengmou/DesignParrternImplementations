# 命令模式

## 问题 1： 假设你正在开发一个文本编辑器，该编辑器允许用户进行文本编辑操作，如添加文本、删除文本等。请设计一个`Command`接口，该接口包括执行命令的方法（如`execute`），并为添加文本创建一个具体的命令类。 提示：你可以首先定义一个`Command`接口，该接口中包含一个`execute()`方法。然后，创建一个`AddTextCommand`类实现这个接口，这个类需要有方法来具体实现添加文本到文档中的操作

![step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241007170006.png)

## 问题 2： 考虑到一个文本编辑器通常需要处理多种不同的文本操作，除了添加和删除文本之外，如何设计和实现以下两个新的功能命令？

替换文本命令（ReplaceTextCommand）：

设计一个命令用于替换文本。该命令应能接受目标文本和替换文本作为参数，并执行替换操作。
复制文本命令（CopyTextCommand）：

设计一个命令用于复制文本。该命令应能接受要复制的文本的开始位置和长度作为参数，并执行复制操作。
提示：为每个命令类定义必要的成员变量以存储所有执行命令所需的信息，比如文本、位置等。同时，考虑如何集成这些命令到现有的系统中，确保它们能够与其他命令一样通过命令调用者（Invoker）来管理和执行。

引入Invoker类：

创建一个Invoker类，它负责调用命令对象的execute方法来执行请求。这个类可以存储命令历史，支持撤销（undo）操作。
增强命令的封装性：

让你的命令类（如AddTextCommand和DeleteTextCommand）不仅封装操作，还可以封装执行操作所需的所有信息，例如，可以将TXT对象直接传递给命令类的构造器。
支持撤销操作：

为Command接口添加一个undo方法，让所有的ConcreteCommand类实现这个方法。这样，每执行一次操作后，都可以通过调用undo方法来撤销它

![step2 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241007170152.png)

![step3 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241007170317.png)
