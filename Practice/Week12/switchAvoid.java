public interface PaymentMethod
{
    void processPayment();
}

public class CreditCardPayment implements PaymentMethod
{
    @Override public void processPayment()
    {
        // Process credit card payment
    }
}

public class PaypalPayment implements PaymentMethod
{
    @Override public void processPayment()
    {
        // Process PayPal payment
    }
}

public class BankTransferPayment implements PaymentMethod
{
    @Override public void processPayment()
    {
        // Process bank transfer payment
    }
}

public class PaymentProcessor
{
    public void processPayment(PaymentMethod method)
    {
        method.processPayment();
    }
}

// public class PaymentProcessor {
//     public void processPayment(PaymentMethod method) {
//         switch (method) {
//             case CREDIT_CARD:
//                 // Process credit card payment
//                 break;
//             case PAYPAL:
//                 // Process PayPal payment
//                 break;
//             case BANK_TRANSFER:
//                 // Process bank transfer payment
//                 break;
//             // ... more cases for other payment methods
//         }
//     }
// }
