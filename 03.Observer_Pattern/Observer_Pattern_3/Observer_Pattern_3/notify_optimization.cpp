// å�� ������ �������� �������� ��� ������ å�� ������ �ݿ����� �ʴ´ٰ� ����
#include <iostream>
#include <string>
#include <list>
using namespace std;


class Observer {
public:
	virtual ~Observer() = default;
	virtual void update(string name_, int price_) = 0;
};

// ���� ������ ���� ������ �޼��带 �����Ѵ�.
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
	// �ٲ� ������ �� ū ��츸 changed�� true�� �����ϰ� notify�� changed�� ture�� ��츸 �����ϵ��� �����Ѵ�.
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
	BookData* bookData = new BookData();

	BookStore* bookStore = new BookStore(bookData);
	Aladin* aladin = new Aladin(bookData);
	Yes24* yes24 = new Yes24(bookData);

	bookData->setData("harry-potter", 20000);

	cout << "update data" << endl << endl;
	// ������ �ٲ��� �ʴ� ���� Ȯ���� �� �ִ�.
	bookData->setData("harry-potter", 10000);

}