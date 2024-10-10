# 反馈

## step2

- 问题1
这个值被直接设置到了RealImage的url属性中，这可能不是最佳选择，因为它改变了RealImage本应存储的实际URL

- 问题2
在ProxyImage的displayImage()方法中，调用setUrl(realImage->getUrl())看起来有些冗余，因为你已经在setUrl()方法中设置了URL。如果只是想显示图片，直接调用realImage->display()可能更直接

- 问题3
考虑让ProxyImage也实现Image接口。这样可以提高代码的一致性和可替换性，允许ProxyImage在任何需要Image对象的地方被透明地使用

---

![Proxy](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/Proxy.jpg)
!["proxy_2 UML"](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241005231425.png)
