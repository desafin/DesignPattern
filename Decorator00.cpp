#include <iostream>
#include <string>

// Component Interface
class Beverage {
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

// Concrete Component
class Espresso : public Beverage {
public:
    std::string getDescription() const override {
        return "Espresso";
    }

    double cost() const override {
        return 1.99;
    }
};

// Decorator
class CondimentDecorator : public Beverage {
public:
    virtual std::string getDescription() const = 0;
};

// Concrete Decorator
class Milk : public CondimentDecorator {
private:
    Beverage* beverage;

public:
    Milk(Beverage* beverage) : beverage(beverage) {}

    std::string getDescription() const override {
        return beverage->getDescription() + ", Milk";
    }

    double cost() const override {
        return 0.10 + beverage->cost();
    }
};

int main() {
    // 주문: 에스프레소에 우유 추가
    Beverage* espresso = new Espresso();
    std::cout << "Order: " << espresso->getDescription() << " $" << espresso->cost() << std::endl;

    // 우유 추가된 에스프레소
    Beverage* milkEspresso = new Milk(espresso);
    std::cout << "Order: " << milkEspresso->getDescription() << " $" << milkEspresso->cost() << std::endl;

    delete espresso;
    delete milkEspresso;

    return 0;
}
