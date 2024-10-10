# 反馈

---

## step1.cpp

在您的代码中，addCondiments方法需要一个字符串参数来确定加入的调味料。虽然这种方式灵活，但它依赖于外部输入。如果调味步骤不仅依赖于外部传入的字符串，还可能有其他复杂的条件和变化，您可能需要更复杂的策略或参数来处理这些情况。
方法访问权限：

在Beverage类中，如boilWater()和pourInCup()是共通的实现，通常不需要被子类覆写。可以将这些方法声明为非虚拟，并限定其访问级别为protected（如果只希望在派生类中使用它们）或private（如果不希望它们被更改或直接访问）。
钩子方法：

在模板方法模式中，可以提供所谓的钩子方法（hook methods），这些方法在基类中通常什么都不做或只做很少的工作，但它们提供了一个接口，子类可以覆盖这些方法以便在算法中加入额外的行为

---

![step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241009220750.png)
![Template UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/Template_Method_UML.svg.png)
