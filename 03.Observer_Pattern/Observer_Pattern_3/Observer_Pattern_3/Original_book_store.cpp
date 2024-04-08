// �� ������ �� ���� ���������� å�� ���ϴ� ���ݿ� �Ǹ��Ѵٰ� ����
/*
* �Ǹ� �ݾ�
�������� ���� = ����
�¶��� ���� = ���� 10%, 1000�� ���ε� ����
*/
#include <iostream>
#include <string>
using namespace std;

// å
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

// �⺻ ���� Ʋ
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

	// å ���� ���� => data�� ������ ������ �� ���� update �ؾ��Ѵ�.
	// update�� ������ ���� �������� setData() �Լ��� chage()��� �Լ��� �߰��ϸ� �Ǳ���.
	//void change()
	//{
	//		bookStore->update(&data);
	//	aladin->update(&data);
	//	yes24->update(&data);
	//}
	// �׷��� ���� ����� ���ο� ������ �߰��Ǹ� change �Լ��� ����Ǿ�� �Ѵ�.
	data->setData("Herry-Potter", 30000);
	bookStore->update(data);
	aladin->update(data);
	yes24->update(data);

	bookStore->showPrice();
	aladin->showPrice();
	yes24->showPrice();
}