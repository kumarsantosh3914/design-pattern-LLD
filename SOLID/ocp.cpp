/**
 * Open/Closed Principle (OCP):
 * Software entities (classes, modules, functions, etc.) should be open for extension but closed for modification.
 */

#include <iostream>

/**
 * If we want to add suport for new shapes, like a Triangle, 
 * we would have to modify the existing code, which violates the OCP.
 */
class ShapeCalculator {
public:
    double calculateArea(const Shape& shape) {
        // Logic to calculate area based on the type of shape
        if (shape.type == "Circle") {
            return 3.14 * shape.radius * shape.radius;
        } else if (shape.type == "Rectangle") {
            return shape.length * shape.width;
        }
        // Add more shapes as needed without modifying existing code
        return 0.0;
    }

    double calculatePerimeter(const Shape& shape) {
        // Logic to calculate perimeter based on the type of shape
        if (shape.type == "Circle") {
            return 2 * 3.14 * shape.radius;
        } else if (shape.type == "Rectangle") {
            return 2 * (shape.length + shape.width);
        }
        // Add more shapes as needed without modifying existing code
        return 0.0;
    }
};


/**
 * To adhere to the OCP, we can use polymorphism and interfaces.
 * This way, we can extend the functionality by adding new shape classes without modifying the existing code
 */

class Shape {
public:
    virtual double calculateArea() const = 0; // Pure virtual function for area calculation
    virtual double calculatePerimeter() const = 0; // Pure virtual function for perimeter calculation
    virtual ~Shape() {} // Virtual destructor for proper cleanup
};

class Rectangle : public Shape {
private:
    double length;
    double width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double calculateArea() const override {
        return length * width;
    }

    double calculatePerimeter() const override {
        return 2 * (length + width);
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double calculateArea() const override {
        return 3.14 * radius * radius;
    }

    double calculatePerimeter() const override {
        return 2 * 3.14 * radius;
    }
};

class Triangle : public Shape {
// Implementation for Triangle can go here
};

int main() {
    Rectangle rect(10, 5);
    Circle circ(7);

    cout << "Rectangle Area: " << rect.calculateArea() << endl;
    cout << "Rectangle Perimeter: " << rect.calculatePerimeter() << endl;

    cout << "Circle Area: " << circ.calculateArea() << endl;
    cout << "Circle Perimeter: " << circ.calculatePerimeter() << endl;

    return 0;
}