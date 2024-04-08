// observer�� ���� ������ �����ϰ� ó���ϴ� ������ �ϹǷ� observer �������̽��� update �޼��尡 �־�� �ϰ�, �� observer�� update�� �����ؾ� �Ѵ�.
#include <iostream>
#include <string>
#include <list>
using namespace std;

// observer �⺻ ����
// ���� �Ҹ��� + ���� �Լ�(���� ��ȭ�� ������ �Լ�)
class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(string name_, int price_) = 0;
};

// ��� �⺻ ����
// ���� �Ҹ��� + ������ �߰� ���� �Լ� + ������ �Ҹ� ���� �Լ�
class Subject {
public:
	Subject() = default;
	virtual ~Subject() = default;
	virtual void subscribe(Observer* o) = 0;
	virtual void unsubscribe(Observer* o) = 0;
	virtual void notify() = 0;
};

/////////////////////////////////////////////////////////////////////////

// ���� ����� �����Ͽ� Subject�� ����� �� �������̵�
// �������� ������ list�� �����.
class BookData :public Subject {
public:
	BookData() = default;
	// list�� ������ �߰�
	void subscribe(Observer* o) override {
		observers.push_back(o);
	}
	// list���� ������ ����
	void unsubscribe(Observer* o) override {
		if (!observers.empty()) {
			delete o;
			observers.remove(o);
		}
	}
	// setData�� ���� ���ŵǸ� notify�� ��� ���������� �˸��� ���� update�� �����Ѵ�.
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
	// �������� �����ϴ� ����Ʈ
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

// �������� ������ Yes24�� �����ϰ�� ��� ���������� update�Ѵ�.