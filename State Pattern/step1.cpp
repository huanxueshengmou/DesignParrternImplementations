#include <iostream>
#include "my_print.cpp"

class State {
public:
  virtual void handlePayment() = 0;
  virtual void shipOrder() = 0;
  virtual void cancelOrder() = 0;
};

class Order {
protected:
  State *myState;

public:
  void setState(State *state) {
    this->myState = state;
  }
};

class StateECommerce : public State {
public:
  void handlePayment() {
    print("Processing payment....");
  }
  void shipOrder() {
    print("Shipping now....");
  }
  void cancelOrder() {
    print("Canceling order....");
  }
};

class ECommerceOrder : public Order {
protected:
  bool pendingPayment = true;
  bool shipped = false;
  bool paid = false;
  bool placeOrder = false;

public:
  void ViewOrder() {
    if (!placeOrder) {
      print("No order placed.");
    } else {
      if (shipped) {
        print("Shipped");
      } else if (paid) {
        print("Paid");
      } else if (pendingPayment) {
        print("Pending Payment");
      } else {
        print("Order status unknown.");
      }
    }
  }

  void delivery() {
    if (paid && !shipped) {
      myState->shipOrder();
      shipped = true;
    }
  }

  void pay() {
    if (pendingPayment && placeOrder) {
      myState->handlePayment();
      paid = true;
      pendingPayment = false;
    }
  }
  void CancelOrder(){
    if(shipped)return ;
    pendingPayment=false;
    placeOrder=false;
  }
  void placeToOrder() {
    if (!placeOrder) {
      placeOrder = true;
      pendingPayment = true;  // Assuming payment is pending when the order is placed
    }
  }
};

int main() {
  StateECommerce state;
  ECommerceOrder order;
  order.setState(&state);

  print("Placing an order...\n");
  order.placeToOrder();

  print("Trying to view the order status...\n");
  order.ViewOrder();

  print("Attempting to pay for the order...\n");
  order.CancelOrder();
  order.placeToOrder();
  print("Trying to ship the order without payment...\n");
  order.delivery();

  print("Paying for the order...\n");
  order.pay();

  print("Shipping the order...\n");
  order.delivery();

  print("Viewing final order status...\n");
  order.ViewOrder();

  return 0;
}
/*output:
Placing an order...

Trying to view the order status...

Pending Payment
Attempting to pay for the order...

Trying to ship the order without payment...

Paying for the order...

Processing payment....
Shipping the order...

Shipping now....
Viewing final order status...

Shipped

*/ 