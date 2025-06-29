#include <iostream>
#include <vector>
using namespace std;

// Observer (Subscriber) interface
class Observer {
public:
    // Pure virtual function to update the observer with a message
    virtual void update(const string& message) = 0;
};

// Concreate Observer class
class ConcreteObserver : public Observer {
public:
    // Implementation of the update method
    void update(const string& message) override {
        cout << "Received message: " << message << endl;
    }
};

// Subject (Publisher) class
class Publisher {
private:
    // List of observers
    vector<Observer*> observers; 

public:
    // Attach an observer to the publisher
    void subscribe(Observer* observer) {
        observers.push_back(observer);
    }

    // Detach an observer from the publisher
    void unsubscribe(Observer* observer) {
        for(auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }

    void notify(const string& message) {
        // Notify all observers with the message
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};

int main() {
    Publisher publisher;

    // Create observers
    ConcreteObserver observer1;
    ConcreteObserver observer2;

    // Attach observers to the publisher
    publisher.subscribe(&observer1);
    publisher.subscribe(&observer2);

    // Publish a messages
    publisher.notify("Message 1");
    publisher.notify("Message 2");

    return 0;
}


