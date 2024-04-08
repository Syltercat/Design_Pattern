// 책의 가격이 기존보다 떨어지는 경우 서점은 책의 가격을 반영하지 않는다고 가정
#include <iostream>
#include <string>
#include <list>
using namespace std;


class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(string name_, int price_) = 0;
};

// 상태 관리를 위해 변수와 메서드를 제공한다.
class Subject {
public:
	Subject() = default;
	virtual ~Subject() = default;
	virtual void subscribe(Observer* o) = 0;
	virtual void unsubscribe(Observer* o) = 0;
	virtual void notify() = 0;
protected:
	void setChanged(bool value) { changed = value; }
	bool getChanged() { return changed; }
private:
	list<Observer*> observers;
	bool changed = false;
};

/////////////////////////////////////////////////////////////////////////

class BookData :public Subject {
public:
	BookData() = default;

	void subscribe(Observer* o) override {
		observers.push_back(o);
	}

	void unsubscribe(Observer* o) override {
		if (!observers.empty()) {
			delete o;
			observers.remove(o);
		}
	}
	// 바뀐 가격이 더 큰 경우만 changed를 true로 변경하고 notify는 changed가 ture인 경우만 실행하도록 구현한다.
	void notify() override {
		if (getChanged() == false) return;
		for (auto o : observers) {
			o->update(name, price);
		}
		setChanged(false);
	}
	void setData(const string& name_, int price_) {
		if (price_ > price) setChanged(true);
		
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
	BookData* bookData = new BookData();

	BookStore* bookStore = new BookStore(bookData);
	Aladin* aladin = new Aladin(bookData);
	Yes24* yes24 = new Yes24(bookData);

	bookData->setData("harry-potter", 20000);

	cout << "update data" << endl << endl;
	// 가격이 바뀌지 않는 것을 확인할 수 있다.
	bookData->setData("harry-potter", 10000);

}