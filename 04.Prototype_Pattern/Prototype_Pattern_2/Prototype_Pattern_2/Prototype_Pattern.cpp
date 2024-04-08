// ���� ��ü ���� ����� ���� ���, ���縦 ���� ��ü�� ����� ���� ȿ�������� ���̴� �ڵ�
#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <string>
using namespace std;

class Prototype {
public:
	virtual Prototype* clone() = 0;
	virtual void print() = 0;
	virtual void setID(int value) = 0;
	virtual ~Prototype() {}
};

class ConcretePtototype :public Prototype {
public:
	ConcretePtototype(int value) :id(value) {
		cout << "Create Start" << endl;

		for (int i = 1; i < 4; i++) {
			cout << "Waiting " << i << "seconde.." << endl;
			this_thread::sleep_for(chrono::seconds(1));
		}
		cout << "Create End" << endl;
	}
	ConcretePtototype(ConcretePtototype& other) :id(other.id) {
		cout << "Copy" << endl;
	}

	Prototype* clone() override {
		return new ConcretePtototype(*this);
	}

	void print()override { cout << "ConcretePrototype " << id << endl; }
	void setID(int value)override { id = value; }
private:
	int id;
};

// ���� ���� ������Ÿ�� ��ü�� �����Ѵ�.
class PrototypeManager {
public:
	static void regisiterPrototype(string name, Prototype* prototype) {
		ptMap[name] = prototype;
	}
	static Prototype* getPrototype(string name) { return ptMap[name]->clone(); }

private:
	static map<string, Prototype*> ptMap;
};

map<string, Prototype*> PrototypeManager::ptMap;


// ó���� ������ ��ü�� ���� ����� �״�� ������ �ش� ��ü�� ����� ��� �̷������.
int main() {
	PrototypeManager::regisiterPrototype("Monster", new ConcretePtototype(1));
	PrototypeManager::regisiterPrototype("NPC", new ConcretePtototype(2));

	Prototype* prototypeA = PrototypeManager::getPrototype("Monster");
	Prototype* prototypeB = PrototypeManager::getPrototype("NPC");

	cout << "\nPrint " << endl;
	cout << "A: ";
	prototypeA->print(); 
	cout << "B: ";
	prototypeB->print();

	cout << "\nCreate" << endl;
	Prototype* prototypeC = PrototypeManager::getPrototype("Monster");
	Prototype* prototypeD = PrototypeManager::getPrototype("NPC");

	cout << "Set ID" << endl;
	prototypeC->setID(100);
	prototypeD->setID(200);

	cout << "\nPrint A,B,C,D \n";
	cout << "A: ";
	prototypeA->print();
	cout << "B: ";
	prototypeB->print();
	cout << "C: ";
	prototypeC->print();
	cout << "D: ";
	prototypeD->print();
	
}