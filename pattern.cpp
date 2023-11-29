#include <iostream>
#include <string>
#include <vector>
#include <list>


// Observer 인터페이스
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(const std::string& message) = 0;
};


class Server {
private:
    static Server* instance;
    std::list<Observer*> observers;

    Server() {} // private 생성자 싱글톤

public:
    // 삭제된 복사 생성자 및 할당 연산자
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    static Server* getInstance() {
        if (instance == nullptr) {
            instance = new Server();
        }
        return instance;
    }

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.remove(observer);
    }

    void notifyObservers(const std::string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};

// Server 인스턴스 초기화
Server* Server::instance = nullptr;


//유저클래스
class User : public Observer {
private:
    std::string name;
    Server* server;

public:
    User(const std::string& name, Server* server) : name(name), server(server) {}

    void sendMessage(const std::string& message) {
        server->notifyObservers(name + ": " + message);
    }
    //업데이트 부분을 구현해야한다
    void update(const std::string& message) override {
        std::cout << name << " received: " << message << std::endl;
    }

    std::string getName() const {
        return name;
    }
};







// UserFactory 클래스 정의
class UserFactory {
public:
    static User* createUser(const std::string& name, Server* server) {
        return new User(name, server);
    }
};




class MessageBuilder {
private:
    std::vector<std::string> messages;

public:
    MessageBuilder& addMessage(const std::string& sender, const std::string& message) {
        messages.push_back(sender + ": " + message);
        return *this;
    }

    std::string build() {
        std::string combinedMessage;
        for (const auto& msg : messages) {
            combinedMessage += msg + "\n";
        }
        return combinedMessage;
    }

    // 초기화 메서드 추가
    void clear() {
        messages.clear();
    }
};

int main() {
    // Server 인스턴스 생성
    Server* server = Server::getInstance();

    // UserFactory를 사용하여 User 객체 생성
    User* alice = UserFactory::createUser("Alice", server);
    User* bob = UserFactory::createUser("Bob", server);

    // Server에 User 객체 등록
    server->addObserver(alice);
    server->addObserver(bob);

    // MessageBuilder 인스턴스 생성 및 메시지 구성
    MessageBuilder messageBuilder;



    messageBuilder.addMessage("Alice", "Hello, everyone!")
                .addMessage("Bob", "Hi, Alice!");

    // Alice가 메시지를 보낸다
    alice->sendMessage(messageBuilder.build());

    // 메시지 빌더를 재사용하여 Bob의 메시지 구성

    messageBuilder.clear(); // 빌더 초기화

    messageBuilder.addMessage("Bob", "How are you, Alice?");

    bob->sendMessage(messageBuilder.build());

    // 동적으로 할당된 User 객체 메모리 해제
    delete alice;
    delete bob;

    return 0;
}
