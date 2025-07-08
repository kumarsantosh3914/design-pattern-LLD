/**
 * Liskov Substitution Principle (LSP):
 * Objects of a superclass should be replaceable with
 * objects of a subclass without affecting the correctness of the program.
 * 
 *  - This means that if you have a base class and a drived class, you 
 *    should be able to use instaces of the derived class wherever the 
 *    base class are expected, without breaking the application.
 */

#include <iostream>

/**
 * In this example, the Bicycle class violates the LSP because it 
 * provides an implementation of the startEngine method, which 
 * doesn't make sense for a bicycle.
 */
class Vehicle {
public:
    void startEngine() {
        std::cout << "Starting engine of the vehicle." << std::endl;
    }
};

class Car : public Vehicle {
public:
    void startEngine() {
        std::cout << "Starting engine of the car." << std::endl;
    }
};

class Bicycle : public Vehicle {
public:
    void startEngine() {
        // Bicycles don't have engines, so we can throw an exception or handle it differently
        throw std::runtime_error("Bicycles do not have engines.");
    }
};


// To adhere to the LSP, we can restructure the classes
// we can acheive this by defining a pure virtual function in the base class
class Vehicle {
public:
    virtual void start() = 0; // Pure virtual function for starting the vehicle
    virtual ~Vehicle() {} // Virtual destructor for proper cleanup
};

class Car : public Vehicle {
public:
    void start() override {
        std::cout << "Starting car." << std::endl;
    }
};

class Bicycle : public Vehicle {
public:
    // Bicycles do not have an engine, so we can provide a different implementation
    void start() override {
        std::cout << "Bicycle does not have an engine to start." << std::endl;
        std::cout << "Start paedaling the bicycle." << std::endl;
    }
};