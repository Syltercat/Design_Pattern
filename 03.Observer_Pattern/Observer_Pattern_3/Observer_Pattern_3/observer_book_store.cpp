// observer는 상태 변경을 감지하고 처리하는 역할을 하므로 observer 인터페이스에 update 메서드가 있어야 하고, 각 observer는 update를 구현해야 한다.
#include <iostream>
#include <string>
#include <list>
using namespace std;

// observer 기본 구조
// 가상 소멸자 + 가상 함수(상태 변화에 관련한 함수)
class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(string name_, int price_) = 0;
};

// 대상 기본 구조
// 가상 소멸자 + 옵저버 추가 가상 함수 + 옵저버 소멸 가상 함수
class Subject {
public:
	Subject() = default;
	virtual ~Subject() = default;
	virtual void subscribe(Observer* o) = 0;
	virtual void unsubscribe(Observer* o) = 0;
	virtual void notify() = 0;
};

/////////////////////////////////////////////////////////////////////////

// 관찰 대상을 지정하여 Subject를 상속한 후 오버라이딩
// 옵저버를 관리할 list를 만든다.
class BookData :public Subject {
public:
	BookData() = default;
	// list에 옵저버 추가
	void subscribe(Observer* o) override {
		observers.push_back(o);
	}
	// list에서 옵저버 삭제
	void unsubscribe(Observer* o) override {
		if (!observers.empty()) {
			delete o;
			observers.remove(o);
		}
	}
	// setData에 의해 갱신되면 notify가 모든 옵저버에게 알림을 보내 update를 수행한다.
	void notify() override {
		for (auto o : observers) {
			o->update(name, price);
		}
	}
	void setData(const string& name_, int price_) {
		name = name_;
		price = price_;
		notify();
	}
private:
	string name;
	int price;
	// 옵저버를 관리하는 리스트
	list<Observer*> observers = {};
};

class BookStore :public Observer {
public:
	BookStore() = default;
	BookStore(Subject* bd) : bookData(bd) {
		bookData->subscribe(this);
	}
	void update(string name_, int price_) override {
		name = name_;
		price = price_;
		showPrice();
	}
	void showPrice() {
		cout << "BookStore: " << "Name(" << name << ") / " << "Price(" << price << ")" << endl;
		cout << endl;
	}
private:
	string name;
	int price;
	Subject* bookData = nullptr;
};

class Aladin :public Observer {
public:
	Aladin() = default;
	Aladin(Subject* bd) : bookData(bd) {
		bookData->subscribe(this);
	}
	void update(string name_, int price_) override {
		name = name_;
		price = price_;
		showPrice();
	}
	void showPrice() {
		cout << "Aladin: " << "Name(" << name << ") / " << "Price(" << price * 0.9 << ")" << endl;
		cout << endl;
	}
private:
	string name;
	int price;
	Subject* bookData = nullptr;
};
class Yes24 :public Observer {
public:
	Yes24() = default;
	Yes24(Subject* bd) : bookData(bd) {
		bookData->subscribe(this);
	}
	void update(string name_, int price_) override {
		name = name_;
		price = price_;
		showPrice();
	}
	void showPrice() {
		cout << "Yes24: " << "Name(" << name << ") / " << "Price(" << price - 1000 << ")" << endl;
		cout << endl;
	}
private:
	string name;
	int price;
	Subject* bookData = nullptr;
};

int main() {
	BookData* bookData = new BookData;

	BookStore* bookStore = new BookStore(bookData);
	Aladin* aladin = new Aladin(bookData);
	Yes24* yes24 = new Yes24(bookData);

	bookData->setData("harry-potter", 20000);

	cout << "unsubscribed yes24 observer" << endl;
	bookData->unsubscribe(yes24);

	cout << "update data" << endl << endl;
	bookData->setData("harry-potter", 30000);
}

// 옵저버를 해제한 Yes24를 제외하고는 모두 정상적으로 update한다.