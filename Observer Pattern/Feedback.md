# 反馈

---

## step1

改进点

支持多个观察者：

当前实现中，WeatherSubject 只支持一个观察者。如果将来需要支持多个观察者，你需要在 WeatherSubject 中维护一个观察者列表。
内存管理：

使用原始指针 (Observer *) 时需要特别注意内存管理，尤其是在添加或移除观察者时。可以考虑使用智能指针（如 std::shared_ptr）来自动管理观察者的生命周期。
消息内容的处理：

WeatherSubject 的 WeatherJson 存储了多条信息，但每次更新后只会更新最后一条信息。可以考虑将消息内容组织成更结构化的方式，或使用不同的属性来存储。

---

## step2

改进点
日志存储顺序：

当前的日志记录顺序似乎与实际发生的顺序相反。这可能是由于你在打印日志时使用栈的特性（后进先出），而通常日志记录应该保持时间顺序（先进先出）。考虑使用其他数据结构（如队列）来维持正确的顺序。
日志内存管理：

你已经实现了日志的内存管理，确保在日志被读取后释放内存。使用智能指针（如std::unique_ptr）可以进一步简化内存管理，并自动处理对象的生命周期。
通知和警报逻辑：

alert 方法当前是硬编码在 update 方法中，这可能不够灵活。在实际应用中，你可能希望根据特定条件触发警报，比如只有在温度超过某个阈值时才发出警报

---

![Observer UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/Observer.jpg)

![Observer UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241010175910.png)

![step2 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008215438.png)
