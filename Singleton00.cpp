#include <iostream>

class Singleton
{
public:
	// 정적으로 객체를 가져오는 함수
	static Singleton& getInstance()
	{
		// 객체가 이미 생성되었는지 확인하고, 아니면 생성
		static Singleton instance;
		return instance;
	}
	// 삭제하는 연산자 오버로딩을 삭제하며 복사 생성자와 할당 연산자를 막음
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;

	int show();
private:
	// 생성자를 private로 선언하며 외부에서 호출할 수 없게 함
	Singleton() {}

	int cnt = 0;
};

int Singleton::show() {
	std::cout << "Hello " << ++cnt << "\n";

	return cnt;
}


void otherFunc()
{
	Singleton& other = Singleton::getInstance();
	other.show();
}

int main()
{
	Singleton& singleton = Singleton::getInstance();
	singleton.show();

	// compile error
	// Singleton& singleton2 = singleton;
	// Singleton singleton3;
	// singleton3 = singleton;

	otherFunc();
	singleton.show();

	return 0;
}
