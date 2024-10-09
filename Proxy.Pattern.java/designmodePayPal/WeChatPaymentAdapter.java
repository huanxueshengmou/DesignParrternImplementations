package designmodePayPal;

public class WeChatPaymentAdapter implements PaymentGateway{
    private WeChatPay weChatPay;
    public WeChatPaymentAdapter(WeChatPay weChatPay){
        this.weChatPay=weChatPay;
    }
    @Override
    public void processPayment(double amount) {
        weChatPay.processWeChatPayment(amount);
    }

}
