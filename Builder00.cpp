#include <iostream>

class ComplexObject {
public:
	int value;
	int position;
	std::string subject;
	std::string description;

public:
	ComplexObject(int param1, int param2, std::string param3, std::string param4)
		: value(param1), position(param2), subject(param3), description(param4) {
	}

	void display() {
		std::cout << "value : " << value << std::endl;
		std::cout << "position: " << position << std::endl;
		std::cout << "subject: " << subject << std::endl;
		std::cout << "description: " << description << std::endl;
	}
};

class Builder { // builder interface
public:
	virtual void buildInt1(int v = 0) = 0;
	virtual void buildInt2(int v = 0) = 0;
	virtual void buildStr3(std::string str = "") = 0;
	virtual void buildStr4(std::string str = "") = 0;
	virtual ComplexObject getResult() = 0;
};

class ConcreteBuilder : public Builder {
private:
	ComplexObject object;

public:
	ConcreteBuilder() : object(0, 0, "", "") {}

	void buildInt1(int v) override {
		object.value = v;
	}

	void buildInt2(int v) override {
		object.position = v;
	}

	void buildStr3(std::string str) override {
		object.subject = str;
	}

	void buildStr4(std::string str) override {
		object.description = str;
	}

	ComplexObject getResult() override {
		return this->object;
	}
};

class Director {
public:
	void construct(Builder* builder) {
		builder->buildInt1(123);
		builder->buildInt2(456);
		builder->buildStr3("sbj");
		builder->buildStr4("desc");
	}
};

int main()
{
	ConcreteBuilder builder; // ConcreteBuilder 객체 생성
	Director director; // Director 객체 생성

	ComplexObject object = builder.getResult(); // 빌더를 이용한 초기화 전 상태보기
	object.display();

	director.construct(&builder); // Director가 ConcreteBuilder를 통해 객체 생성 과정 제어

	object = builder.getResult(); // 완성된 객체 획득
	object.display();
}
