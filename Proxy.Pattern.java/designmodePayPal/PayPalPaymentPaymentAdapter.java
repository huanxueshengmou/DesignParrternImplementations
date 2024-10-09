package designmodePayPal;

public class PayPalPaymentPaymentAdapter implements PaymentGateway{
    private PayPalPayment payPalPayment;

    public PayPalPaymentPaymentAdapter(PayPalPayment payPalPayment) {
        this.payPalPayment = payPalPayment;
    }

    @Override
    public void processPayment(double amount) {
        payPalPayment.processPayPalPayment(amount);
    }
}
