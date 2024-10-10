# 关于代码的优化建议

---

`step2.cpp`有如下建议:

- 集合选择：使用std::set来存储Color和Style实例是一个不错的选择，因为它支持快速查找。但是，使用set存储Character对象可能不是最佳选择，因为Character对象的唯一性通常是由它的非固有状态（如位置）定义的，这些状态不应该用于判定对象的等价性。

- 内存管理：在现代C++中，推荐使用智能指针（如std::unique_ptr或std::shared_ptr）来管理对象生命周期，以避免手动delete可能导致的内存泄漏。

- 工厂方法改进：当前的setCharacter方法实际上不仅设置当前字符，还将字符添加到工厂的集合中。更清晰的实现应该是将这两个功能分开，确保每个方法只执行一个功能

---

![设计后的uml关系图](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241005013651.png)
![Flyweight](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241010192248.png)
