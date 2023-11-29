#include <iostream>
#include <string>
#include <vector>

// 옵저버 클래스
class Observer {
public:
	virtual void update(const std::string& message) = 0;
};

// 서버 클래스
class Server {
private:
	static Server* instance;
	std::vector<class Observer*> observers;

	Server() {}

public:
	static Server* getInstance() {
		if (!instance)
			instance = new Server;
		return instance;
	}

	void attach(Observer* observer) {
		observers.push_back(observer);
	}

	void notify(const std::string& message) {
		for (Observer* observer : observers) {
			observer->update(message);
		}
	}

	void receiveMessage(const std::string& message) {
		notify(message);
	}
};

Server* Server::instance = nullptr;

// 구체적인 사용자 클래스
class User : public Observer {
private:
	std::string name;

public:
	User(const std::string& name) : name(name) {
		Server::getInstance()->attach(this);
	}

	void update(const std::string& message) override {
		std::cout << name << " received: " << message << std::endl;
	}

	void sendMessage(const std::string& message) {
		std::cout << name << " send: " << message << "\n";
		Server::getInstance()->receiveMessage("(from:" + name + ") " + message);
	}
};

// 사용자 객체 생성 클래스
class UserFactory {
public:
	static Observer* createUser(const std::string& name) {
		return new User(name);
	}
};

// 메시지 빌더 클래스
class MessageBuilder {
private:
	std::string message;

public:
	MessageBuilder& addText(const std::string& text) {
		message += text;
		return *this;
	}

	std::string build() {
		return message;
	}
};

// 메인 함수
int main() {
	Observer* user1 = UserFactory::createUser("Alice");
	Observer* user2 = UserFactory::createUser("Bob");

	MessageBuilder builder;
	std::string message = builder.addText("Hello, ").addText("world!").build();

	static_cast<User*>(user1)->sendMessage(message);

	delete user1;
	delete user2;

	return 0;
}
