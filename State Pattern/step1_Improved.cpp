#include <iostream>
using namespace std;

class Order; // Forward declaration for Order


class State {
public:
    virtual void handlePayment(Order* order) = 0;
    virtual void shipOrder(Order* order) = 0;
    virtual void cancelOrder(Order* order) = 0;
    virtual ~State() {}
};

class Order {
protected:
    State* currentState;
public:
    Order() : currentState(nullptr) {}
    void setState(State* state) {
        if (currentState) {
            delete currentState; // Ensure to clean up memory
        }
        this->currentState = state;
    }
    void pay() {
        currentState->handlePayment(this);
    }
    void ship() {
        currentState->shipOrder(this);
    }
    void cancel() {
        currentState->cancelOrder(this);
    }
    ~Order() {
        if (currentState) {
            delete currentState; // Clean up any state left
        }
    }
};
class ShippedState : public State {
public:
    void handlePayment(Order* order) override {
        cout << "Order already shipped." << endl;
    }
    void shipOrder(Order* order) override {
        cout << "Order already shipped." << endl;
    }
    void cancelOrder(Order* order) override {
        cout << "Order cannot be canceled after shipping." << endl;
    }
};
class PaidState : public State {
public:
    void handlePayment(Order* order) override {
        cout << "Payment already processed." << endl;
    }
    void shipOrder(Order* order) override {
        cout << "Shipping now..." << endl;
        order->setState(new ShippedState());
    }
    void cancelOrder(Order* order) override {
        cout << "Order cannot be canceled after payment." << endl;
    }
};
class CanceledState : public State {
public:
    void handlePayment(Order* order) override {
        cout << "Order canceled, cannot process payment." << endl;
    }
    void shipOrder(Order* order) override {
        cout << "Order canceled, cannot ship." << endl;
    }
    void cancelOrder(Order* order) override {
        cout << "Order already canceled." << endl;
    }
};
class PendingPaymentState : public State {
public:
    void handlePayment(Order* order) override {
        cout << "Processing payment..." << endl;
        order->setState(new PaidState());
    }
    void shipOrder(Order* order) override {
        cout << "Cannot ship order. Payment required." << endl;
    }
    void cancelOrder(Order* order) override {
        cout << "Order canceled." << endl;
        order->setState(new CanceledState());
    }
};

int main() {
    Order order;

    // Testing in Pending Payment State
    order.setState(new PendingPaymentState());
    order.pay();
    order.ship();
    order.cancel();

    // Reset to Pending Payment State and test cancellation before payment
    order.setState(new PendingPaymentState());
    order.cancel();

    // Test order already paid state
    order.setState(new PaidState());
    order.pay();  // Should print that payment is already processed
    order.ship(); // Should transition to ShippedState

    // Test order in Shipped State
    order.setState(new ShippedState());
    order.pay();  // Should be no effect
    order.ship(); // Should print already shipped
    order.cancel(); // Should say cannot cancel

    // Test order in Canceled State
    order.setState(new CanceledState());
    order.pay();
    order.ship();
    order.cancel(); // Should print already canceled

    return 0;
}

/*output:
  Processing payment...
  Shipping now...
  Order cannot be canceled after shipping.
  Order canceled.
  Payment already processed.
  Shipping now...
  Order already shipped.
  Order already shipped.
  Order cannot be canceled after shipping.
  Order canceled, cannot process payment.
  Order canceled, cannot ship.
  Order already canceled.
*/ 