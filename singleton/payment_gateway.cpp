#include <iostream>
using namespace std;

class PaymentGatewayManager {
private:
    PaymentGatewayManager() {
        cout << "Payment Gateway Manager initialized." << endl;
    }

    static PaymentGatewayManager* instance;
    static mutex mtx;

public:
    static PaymentGatewayManager* getInstance() {
        // Double-checked locking to ensure thread safety
        // and to avoid unnecessary locking after the instance is created.
        if(instance == nullptr) {
            // Lock only if the instance is not created yet
            // This reduces the overhead of locking after the instance is created.
            mtx.lock();
            if(instance == nullptr) {
                instance = new PaymentGatewayManager();
            }
            mtx.unlock();
        }
        return instance;
    }

    void processPayment(double amount) {
        cout << "Processing payment of $" << amount << " through the payment gateway." << endl;
    }
};

PaymentGatewayManager* PaymentGatewayManager::instance = nullptr;
mutex PaymentGatewayManager::mtx;

int main() {
    PaymentGatewayManager* paymentGateway = PaymentGatewayManager::getInstance();
    paymentGateway->processPayment(100.0);

    // Attempt to create another instance (should return the existing instance)
    PaymentGatewayManager* anotherPaymentGateway = PaymentGatewayManager::getInstance();
    // Check if both instances are the same.
    if(paymentGateway == anotherPaymentGateway) {
        cout << "Both instances are the same. Singleton pattern works!" << endl;
    } else {
        cout << "Instances are different. Singleton pattern failed!" << endl;
    }

    return 0;
};