# 代理模式练习

## 问题 1： 假设你正在开发一个应用程序，需要从网络上加载图片，并显示在界面上。加载图片可能会占用较多时间，特别是在网络条件不佳的情况下。请设计一个Image接口和一个RealImage类，后者负责实际加载图片

提示：你可以为Image接口定义一个display()方法，RealImage类则实现这个方法，并在其中模拟加载和显示图片的过程

!["proxy UML"](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241005231050.png)

## 问题 2： 请设计一个ProxyImage类作为RealImage的代理。ProxyImage类应该能在RealImage的图片还未加载完成时，显示一个加载中的占位符，当图片加载完成后再显示实际图片

提示：你可以在ProxyImage中维护一个RealImage的引用，并在display方法中实现延迟加载的逻辑。如果图片未加载，则显示占位符；如果加载完成，则显示实际图片

!["proxy_2 UML"](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241005231425.png)

Implemented Proxy pattern in C++
