package designmodePayPal;

public class Test {
    public static void main(String[] args) {
        PaymentGateway paymentGateway=new PayPalPaymentPaymentAdapter(new PayPalPayment());
        paymentGateway.processPayment(100.1);

        PaymentGateway weChatapater=new WeChatPaymentAdapter(new WeChatPay());
        weChatapater.processPayment(250.0);

        PaymentGateway bankadapter=new BankTransferPaymentAdapter(new BankTransfer());
        bankadapter.processPayment(156.0);
    }
}
