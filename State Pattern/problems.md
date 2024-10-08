# 状态模式

第一步：定义状态接口和上下文类
问题 1： 假设你正在开发一个电商应用，其中订单（Order）具有几种不同的状态，如待支付、已支付、已发货、已取消等。首先，我们需要定义一个状态接口和一个订单类。状态接口应该包括执行状态相关行为的方法，例如支付、取消和发货。订单类应该能够根据不同的状态改变其行为。

提示：创建一个State接口，包含handlePayment(), shipOrder(), cancelOrder()等方法。创建一个Order类，其中包含一个指向State的引用，以及方法来改变状态和调用状态方法

当前的思路有：
待支付->已支付->已发货

待支付->已取消

![step1 UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008230920.png)

## 问题 2：考虑错误处理

问题 2： 如果在处理支付或发货过程中出现错误怎么办？例如，支付失败或发货地址错误。

提示：你可以为这些情况引入异常处理或特定的状态，比如PaymentFailedState或ShippingErrorState

![step1_Improved UML](https://cdn.jsdelivr.net/gh/huanxueshengmou/picture-host/20241008231307.png)
