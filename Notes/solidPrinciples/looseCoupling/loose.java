public class ShoppingCart {
    private List<Item> items;
    private PaymentService paymentService;

    public ShoppingCart(PaymentService paymentService) {
        this.items = new ArrayList<>();
        this.paymentService = paymentService;
    }

    public void addItem(Item item) {
        this.items.add(item);
    }

    public void checkout() {
        for (Item item : items) {
            paymentService.processPayment(item.getPrice());
        }
    }
}

public interface PaymentService {
    void processPayment(double amount);
}

public class CreditCardPaymentService implements PaymentService {
    @Override
    public void processPayment(double amount) {
        // Logic to process credit card payment
    }
}

public class PayPalPaymentService implements PaymentService {
    @Override
    public void processPayment(double amount) {
        // Logic to process PayPal payment
    }
}
