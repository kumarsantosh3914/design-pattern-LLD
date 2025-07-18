#include <iostream>
#include <string>

// Product
class Computer {
private:
    std::string cpu;
    std::string ram;
    std::string storage;

public:
    Computer(std::string c, std::string r, std::string s) : cpu(c), ram(r), storage(s) {}

    void display() {
        std::cout << "CPU: " << cpu << ", RAM: " << ram << ", Storage: " << storage << std::endl;
    }
};

// Abstract Builder
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() {}
    virtual ComputerBuilder& setCpu(const std::string& c) = 0;
    virtual ComputerBuilder& setRam(const std::string& r) = 0;
    virtual ComputerBuilder& setStorage(const std::string& s) = 0;
    virtual Computer build() = 0;
};

// Concrete Builder
class GamingComputerBuilder : public ComputerBuilder {
private:
    std::string cpu = "Basic CPU";
    std::string ram = "8GB";
    std::string storage = "256GB SSD";

public:
    ComputerBuilder& setCpu(const std::string& c) override {
        cpu = c;
        return *this;
    }

    ComputerBuilder& setRam(const std::string& r) override {
        ram = r;
        return *this;
    }

    ComputerBuilder& setStorage(const std::string& s) override {
        storage = s;
        return *this;
    }

    Computer build() override {
        return Computer(cpu, ram, storage);
    }
};

// Director (Optional)
class ComputerDirector {
public:
    Computer buildGamingPc(ComputerBuilder& builder) {
        return builder.setCpu("High-End CPU")
                     .setRam("32GB")
                     .setStorage("1TB SSD")
                     .build();
    }
};

int main() {
    GamingComputerBuilder builder;
    ComputerDirector director;

    Computer gamingPc = director.buildGamingPc(builder);
    gamingPc.display();

    // Direct build with chaining
    Computer customPc = GamingComputerBuilder()
                        .setCpu("Mid-Range CPU")
                        .setRam("16GB")
                        .build();  // Storage defaults
    customPc.display();

    return 0;
}
