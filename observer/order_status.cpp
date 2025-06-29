#include <iostream>
#include <vector>
using namespace std;

class Order;

class Observer {
public:
    // Pure virtual function to update the observer with an order
    virtual void update(Order* order) = 0;
};

// Concrete Observer: Customer
class Customer : public Observer {
private:
    string name;

public:
    Customer(const string& name): name(name) {}

    void update(Order* order);
};

// Concrete Observer: Restaurant
class Restaurant : public Observer {
private:
    string restaurantName;

public:
    Restaurant(const string& name): restaurantName(name) {}

    void update(Order* order);
};


// Concrete Observer: DeliveryDriver
class DeliveryDriver : public Observer {
private:
    string driverName;

public:
    DeliveryDriver(const string& name): driverName(name) {}
    void update(Order* order);
};

// Concrete Observer: CallCenter
class CallCenter : public Observer {
public:
    void update(Order* order);
};

// Subject: Order
class Order {
private:
    int id;
    string status;
    vector<Observer*> observers;

public:
    Order(int id): id(id), status("Order Palced") {}

    int getId() const {
        return id;
    }

    string getStatus() const {
        return status;
    }

    void setStatus(const string& newStatus) {
        status = newStatus;
        notifyObserver();
    }

    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                // Assuming each observer can be attached only once
                break;
            }
        }
    }

    void notifyObserver() {
        for (Observer* observer : observers) {
            observer->update(this);
        }
    }
};

void Customer::update(Order* order) {
    cout << "Customer " << name << " notified. Order ID: " << order->getId() 
         << ", Status: " << order->getStatus() << endl;
}

void Restaurant::update(Order* order) {
    cout << "Restaurant " << restaurantName << " notified. Order ID: " << order->getId() 
         << ", Status: " << order->getStatus() << endl;
}

void DeliveryDriver::update(Order* order) {
    cout << "Delivery Driver " << driverName << " notified. Order ID: " << order->getId() 
         << ", Status: " << order->getStatus() << endl;
}

void CallCenter::update(Order* order) {
    cout << "Call Center notified. Order ID: " << order->getId() 
         << ", Status: " << order->getStatus() << endl;
}

int main() {
    // Create an order
    Order order1(123);

    // Create customers, restaurant, delivery driver, and call center to track the order
    Customer customer1("Customer 1");
    Restaurant restaurant1("Restaurant 1");
    DeliveryDriver driver1("Driver 1");
    CallCenter callCenter;

    // Attach observers to the order
    order1.attach(&customer1);
    order1.attach(&restaurant1);
    order1.attach(&driver1);
    order1.attach(&callCenter);

    // Simulate order status updates
    order1.setStatus("Out for Delivery");

    // Detach an observer (if needed)
    order1.detach(&callCenter);

    // Simulate more order status updates
    order1.setStatus("Delivered");

    return 0;
}