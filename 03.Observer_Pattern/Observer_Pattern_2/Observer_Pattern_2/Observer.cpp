// 옵저버 패턴으로 메세지의 변경을 알리는 예제
#include <iostream>
#include <list>
#include <string>
using namespace std;

class IObserver {
public:
	virtual ~IObserver() {};
	virtual void Update(const string& message_from_subject) = 0;
};

class ISubject {
public:
	virtual ~ISubject() {};
	virtual void Attach(IObserver* observer) = 0;
	virtual void Detach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};

class Subject :public ISubject {
public:
	virtual ~Subject() {
		cout << "Bye. i was the Subject.\n";
	}

	void Attach(IObserver* observer)override {
		list_Observer.push_back(observer);
	}

	void Detach(IObserver* observer)override {
		list_Observer.remove(observer);
	}

	void Notify() override {
		list<IObserver*>::iterator iter = list_Observer.begin();
		HowManyObserver();
		while (iter != list_Observer.end()) {
			(*iter)->Update(message);
			++iter;
		}
	}

	void CreateMessage(string message_ = "Empty") {
		this->message = message_;
		Notify();
	}

	void HowManyObserver() {
		cout << list_Observer.size() << " observers in list\n";
	}

	void SomeBusinessLogic() {
		this->message = "change message";
		Notify();
		cout << "I'm about to do some thing important\n";
	}

private:
	list<IObserver*> list_Observer;
	string message;
};

class Observer :public IObserver {
public:
	Observer(Subject& subject_) :subject(subject_) {
		this->subject.Attach(this);
		cout << "Hi, I'm the observer /" << ++Observer::static_number << "/ .\n";
		this->number = Observer::static_number;
	}

	virtual ~Observer() {
		cout << "Bye, I was the observer /" << this->number << "/ .\n";
	}

	void Update(const string& message_from_subject_)override{
		message_from_subject = message_from_subject_;
		PrintInfo();
	}

	void RemoveMeFromTheList() {
		subject.Detach(this);
		cout << "Observer /" << number << "/ remove from the list\n";
	}

	void PrintInfo() {
		cout << "Observer /" << this->number << "/ : a new message is available --> " << this->message_from_subject << "\n";
	}

private:
	string message_from_subject;
	Subject& subject;
	static int static_number;
	int number;
};

int Observer::static_number = 0;

void ClientCode() {
	Subject* subject = new Subject;
	Observer* observer1 = new Observer(*subject);
	Observer* observer2 = new Observer(*subject);
	Observer* observer3 = new Observer(*subject);
	Observer* observer4;
	Observer* observer5;

	subject->CreateMessage("Hello World!");
	observer3->RemoveMeFromTheList();

	subject->CreateMessage("The weather is hot");
	observer4 = new Observer(*subject);

	observer2->RemoveMeFromTheList();
	observer5 = new Observer(*subject);

	subject->CreateMessage("My new message");
	observer5->RemoveMeFromTheList();

	observer4->RemoveMeFromTheList();
	observer1->RemoveMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete subject;
}

void main() {
	ClientCode();
}