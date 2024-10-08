# 迭代器模式

## 问题 1： 假设你正在开发一个应用，需要处理一个学生名单的集合。首先，我们需要为这个学生名单创建一个容器，比如一个列表。请设计一个聚合接口Aggregate和一个迭代器接口Iterator。Aggregate应该提供一个方法来生成一个迭代器，Iterator接口应该包括访问和遍历元素的基本方法，比如hasNext(), next()

提示：Aggregate接口可以有一个方法createIterator()，返回一个Iterator接口的实现。Iterator接口可以包括hasNext()和next()方法，分别用来检查是否有下一个元素和访问下一个元素。
