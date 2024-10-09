package designmodePayPal;

public class BankTransferPaymentAdapter implements PaymentGateway{
    private BankTransfer bankTransfer;

    public BankTransferPaymentAdapter(BankTransfer bankTransfer) {
        this.bankTransfer = bankTransfer;
    }

    @Override
    public void processPayment(double amount) {
        bankTransfer.processBankTransfer(amount);
    }
}
