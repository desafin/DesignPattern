#include <iostream>

class Product {
public:
    virtual void use() = 0;
};

class ConcreteProductA : public Product {
public:
    void use() override { std::cout << "use() of ConcreteProductA\n"; }
};

class ConcreteProductB : public Product {
public:
    void use() override { std::cout << "use() of ConcreteProductB\n"; }
};

class Creator {
public:
    virtual Product* factoryMethod() = 0;
};

class ConcreteCreatorA : public Creator {
public:
    Product* factoryMethod() override {
        return new ConcreteProductA();
    }
};

class ConcreteCreatorB : public Creator {
public:
    Product* factoryMethod() override {
        return new ConcreteProductB();
    }
};

int main()
{
    ConcreteCreatorA A;
    ConcreteCreatorB B;

    Product* pResult_A = A.factoryMethod();
    Product* pResult_B = B.factoryMethod();

    pResult_A->use();
    pResult_B->use();
}