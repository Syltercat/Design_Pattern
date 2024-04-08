// 각 서점이 한 권의 자율적으로 책을 원하는 가격에 판매한다고 가정
/*
* 판매 금액
오프라인 서점 = 원가
온라인 서점 = 각각 10%, 1000원 할인된 가격
*/
#include <iostream>
#include <string>
using namespace std;

// 책
class BookData {
public:
	BookData() = default;
	string getName() { return name; }
	int getPrice() { return price; }
	void setData(const string& name_, int price_) {
		name = name_;
		price = price_;
	}
private:
	string name;
	int price;
};

// 기본 상점 틀
class Store {
public:
	virtual void showPrice() = 0;
	void update(BookData* data) {
		name = data->getName();
		price = data->getPrice();
	}
protected:
	string name;
	int price;
};

// BookStore
class BookStore :public Store {
public:
	void showPrice() {
		cout << "BookStore: " << "Name(" << name << ") / " << "Price" << price << ")" << endl;
		cout << endl;
	}
};

// Aladin
class Aladin :public Store {
public:
	void showPrice() {
		cout << "Aladin: " << "Name(" << name << ") / " << "Price(" << price * 0.9 << ")"  << endl;
		cout << endl;
	}
};

// Yes24
class Yes24 :public Store {
public:
	void showPrice() {
		cout << "YES24: " << "Name(" << name << ") / " << "Price" << price - 1000 << ")" << endl;
		cout << endl;
	}
};

int main() {
	BookData* data = new BookData;
	data->setData("Herry-Potter", 20000);

	BookStore* bookStore = new BookStore;
	Aladin* aladin = new Aladin;
	Yes24* yes24 = new Yes24;

	bookStore->update(data);
	aladin->update(data);
	yes24->update(data);

	bookStore->showPrice();
	aladin->showPrice();
	yes24->showPrice();

	// 책 가격 변경 => data로 가격을 변경한 후 전부 update 해야한다.
	// update를 일일이 하지 않으려면 setData() 함수에 chage()라는 함수를 추가하면 되긴함.
	//void change()
	//{
	//		bookStore->update(&data);
	//	aladin->update(&data);
	//	yes24->update(&data);
	//}
	// 그러나 위의 방법은 새로운 서점이 추가되면 change 함수가 변경되어야 한다.
	data->setData("Herry-Potter", 30000);
	bookStore->update(data);
	aladin->update(data);
	yes24->update(data);

	bookStore->showPrice();
	aladin->showPrice();
	yes24->showPrice();
}