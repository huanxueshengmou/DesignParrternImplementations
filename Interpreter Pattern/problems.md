# 解释器模式

## 问题 1： 假设你需要创建一个简单的表达式解释器，这个解释器可以处理简单的加法和减法运算。首先，我们需要定义表达式的表示方式。请设计一个表达式接口（Expression），以及实现该接口的具体类来代表数字和简单的加法和减法运算

提示：你可以创建一个Expression接口，该接口包含一个方法interpret，用于返回表达式的值。然后，创建Number类来表示数字，AddExpression和SubtractExpression类来表示加法和减法表达式。每个类都需要实现interpret方法。

![step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008123845.png)

## 问题 2： 现在，你已经有了基本的数字和简单的二元运算。让我们扩展这个解释器，以便它可以处理更复杂的表达式，例如嵌套表达式（例如 `(10 + 5) - (3 - 1)`）。 为了实现这个目标，你需要引入一种方式来组合已有的表达式。你可以考虑实现一个更通用的表达式类或修改现有的表达式类，使之能够接受其他`Expression`对象作为其操作数。 提示：你可以创建一个新的类，比如`CompoundExpression`，它接受两个`Expression`对象和一个运算符（比如 `+`, `-`），然后在`interpret`方法中根据运算符决定调用左右表达式的`interpret`方法的方式

![step2 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008124019.png)
