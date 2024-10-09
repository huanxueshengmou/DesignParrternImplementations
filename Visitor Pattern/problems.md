# 访问者模式

## 问题 1： 假设你正在开发一个图形设计程序，其中有多种类型的图形对象，如圆形、矩形和线段。你需要能够在这些图形上执行多种操作，如绘图和转换。请定义一个元素接口Graphic和一个访问者接口GraphicVisitor。元素接口应该包含一个accept方法，允许访问者访问该元素，而访问者接口应该包含对每种类型图形的访问方法

提示：创建一个Graphic接口，其中包含一个accept(GraphicVisitor&)方法。GraphicVisitor接口应该有visitCircle(Circle&)、visitRectangle(Rectangle&)和visitLine(Line&)方法

![step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241009230728.png)

## 问题 2: 如何使用访问者模式来处理图形的不同表示形式？

例如，如果您想要为每种图形类增加一个新的操作，比如计算图形的周长，您会如何扩展当前的系统？您可以考虑创建一个新的访问者类来处理这些操作。

这种方式允许您在不修改图形类的前提下，通过添加新的访问者来增加新的操作，这展示了访问者模式的强大扩展性。

![step2.cpp UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241009231431.png)
