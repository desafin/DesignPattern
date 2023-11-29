#include <iostream>
#include <list>
#include <string>

class ConcreteObserver {
public:
	virtual ~ConcreteObserver() {};
	virtual void Update(const std::string& message_from_subject) = 0;
};

class ConcreteSubject {
public:
	virtual ~ConcreteSubject() {};
	virtual void Attach(ConcreteObserver* observer) = 0;
	virtual void Detach(ConcreteObserver* observer) = 0;
	virtual void Notify() = 0;
};

class Subject : public ConcreteSubject {
public:
	virtual ~Subject() {
		std::cout << "Subject destroyed.\n";
	}

	void Attach(ConcreteObserver* observer) override {
		list_observer_.push_back(observer);
	}
	void Detach(ConcreteObserver* observer) override {
		list_observer_.remove(observer);
	}
	void Notify() override {
		std::cout << "Notify to " << list_observer_.size() << " observers in the list.\n";

		std::list<ConcreteObserver*>::iterator iterator = list_observer_.begin();
		while (iterator != list_observer_.end()) {
			(*iterator)->Update(message_);
			++iterator;
		}
	}

	void CreateMessage(std::string message = "EmptyMsg") {
		this->message_ = message;
		Notify();
	}

private:
	std::list<ConcreteObserver*> list_observer_;
	std::string message_;
};

class Observer : public ConcreteObserver {
public:
	Observer(Subject& subject) : subject_(subject) {
		this->subject_.Attach(this);	// 생성자에서 자동으로 Subject에 등록함

		std::cout << "Observer" << ++Observer::cnt_for_id << " created.\n";
		this->id = Observer::cnt_for_id;
	}
	virtual ~Observer() {
		std::cout << "Observer " << this->id << " destroyed.\n";
	}

	void Update(const std::string& message_from_subject) override {
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}
	void RemoveMeFromTheList() {
		subject_.Detach(this);
		std::cout << "Observer \"" << id << "\" removed from the list.\n";
	}
	void PrintInfo() {
		std::cout << "Observer \"" << this->id << "\": a new message is available --> "
			<< this->message_from_subject_ << "\n";
	}

private:
	std::string message_from_subject_;
	Subject& subject_;
	static int cnt_for_id;
	int id;
};

int Observer::cnt_for_id = 0;

int main() {


	Subject* subject = new Subject; // overver들을 등록할 subject

	Observer* observer1 = new Observer(*subject);
	Observer* observer2 = new Observer(*subject);
	Observer* observer3 = new Observer(*subject);
	Observer* observer4;
	Observer* observer5;

	subject->CreateMessage("Hello World! :D");
	observer3->RemoveMeFromTheList();

	subject->CreateMessage("The weather is hot today! :p");
	observer4 = new Observer(*subject);

	observer2->RemoveMeFromTheList();
	observer5 = new Observer(*subject);

	subject->CreateMessage("My new car is great! ;)");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete subject;

	return 0;
}
