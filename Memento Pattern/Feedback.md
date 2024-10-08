# 备忘录模式

## 问题 1： 假设你正在开发一个简单的文本编辑器，该编辑器允许用户输入文本、保存状态和回滚到之前的状态。首先，我们需要为编辑器的状态定义一个类。请设计一个编辑器类Editor，它应该能够写入文本、保存状态到备忘录以及从备忘录恢复状态

提示：你可以创建一个Editor类，它包含一个字符串属性来存储文本内容。此外，创建一个Memento类，用于存储Editor状态的快照。Editor类应提供save()方法来创建一个Memento对象，并提供restore()方法来从Memento对象恢复状态