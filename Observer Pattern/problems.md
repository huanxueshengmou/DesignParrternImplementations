# 观察者模式

## 问题 1： 假设你正在开发一个天气监测应用，需要实时更新气象数据并通知所有关注天气更新的用户。首先，我们需要定义两个接口：一个是Subject（主题），它能够附加或移除观察者，并通知所有观察者状态改变；另一个是Observer（观察者），每当接收到更新通知时能够获取最新数据

提示：Subject接口应包含registerObserver、removeObserver和notifyObservers方法。Observer接口应有一个update方法，用于接收来自Subject的更新

![step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008215041.png)

## 问题 2：扩展功能

问题 2： 如果我们需要在观察者模式中添加功能，比如在接收到天气更新时添加日志记录，或者在观察者更新时执行特定的动作（如发送警报），你会如何扩展当前的实现？

提示：考虑在观察者类中添加新的方法来处理这些操作，或者在 WeatherSubject 中引入策略来处理不同类型的通知。

请根据这个新需求设计并实现所需的扩展。这将帮助你更深入理解观察者模式的灵活性和可扩展性

![step2 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008215438.png)
