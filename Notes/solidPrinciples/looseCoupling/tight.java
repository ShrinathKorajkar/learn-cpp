public class ShoppingCart {
    private List<Item> items;

    public ShoppingCart() {
        this.items = new ArrayList<>();
    }

    public void addItem(Item item) {
        this.items.add(item);
    }

    public void checkout() {
        PaymentService paymentService = new PaymentService();
        for (Item item : items) {
            paymentService.processPayment(item.getPrice());
        }
    }
}

public class PaymentService {
    public void processPayment(double amount) {
        // Logic to process payment
    }
}
