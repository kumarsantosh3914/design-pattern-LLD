#include <iostream>

using namespace std;

class PaymentStrategy {
public:
    // Pure virtual function for processing payment
    virtual void processPayment(double amount) = 0;
    // Virtual destructor for proper cleanup of derived classes
    virtual ~PaymentStrategy() {}
};

// Concrete strategy: credit card payment
class CreditCardPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
    }
};

// Concrete strategy: PayPal payment
class PayPalPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

// Concrete strategy: cryptocurrency payment
class CryptocurrencyPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing cryptocurrency payment of $" << amount << endl;
    }
};

class PaymnetProcessor {
private:
    PaymentStrategy* paymentStrategy;

public:
    // Constructor initializes the strategy to nullptr
    PaymnetProcessor() : paymentStrategy(nullptr) {}

    // Destructor to clean up the strategy object
    void setPaymentStrategy(PaymentStrategy* strategy) {
        paymentStrategy = strategy;
    }

    // Method to process payment using the current strategy
    void processPayment(double amount) {
        if(paymentStrategy) {
            paymentStrategy->processPayment(amount);
        } else {
            cout << "No payment strategy set." << endl;
        }
    }

    // Destructor to clean up the strategy object
    ~PaymnetProcessor() {
        if(paymentStrategy) {
            delete paymentStrategy; // Clean up the strategy object
        }
    }
};

int main() {
    PaymnetProcessor processor;

    // Select and set the payment strategy at runtime
    PaymentStrategy* strategy = new CreditCardPayment();
    processor.setPaymentStrategy(strategy);

    // Process the payment
    processor.processPayment(100.0);

    // Change the payment startegy
    delete strategy; // Clean up the previous strategy
    strategy = new PayPalPayment();
    processor.setPaymentStrategy(strategy);

    // Process another payment using the new strategy
    processor.processPayment(200.0);

    delete strategy; // Clean up the last strategy
    
    return 0;
}