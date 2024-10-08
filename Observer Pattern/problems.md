# 观察者模式

## 问题 1： 假设你正在开发一个天气监测应用，需要实时更新气象数据并通知所有关注天气更新的用户。首先，我们需要定义两个接口：一个是Subject（主题），它能够附加或移除观察者，并通知所有观察者状态改变；另一个是Observer（观察者），每当接收到更新通知时能够获取最新数据

提示：Subject接口应包含registerObserver、removeObserver和notifyObservers方法。Observer接口应有一个update方法，用于接收来自Subject的更新
