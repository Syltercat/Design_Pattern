#include <iostream>
#include <string>
using namespace std;

class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class Light {
public:
	void on() { cout << "on\n"; }
	void off() { cout << "off\n"; }

};
// Light 켜는 작업을 구현한다.
class LightOnCommand :public Command {
public:
	LightOnCommand(Light* l) :light(l) {}
	void execute() { light->on(); }
private:
	Light* light;
};

class Television {
public:
	void channel_Up() { cout << "up\n"; }
	void channel_Down() { cout << "Down\n"; }
	void subtitle_On() { cout << "subtitle On\n"; }
	void subtitle_Off() { cout << "subtitle Off\n"; }
};

class TelevisionSubtitleOn : public Command {
public:
	TelevisionSubtitleOn(Television *tv):television(tv){}
	void execute() { television->subtitle_On(); }
private:
	Television* television;
};

// 버튼만 누르면 해당 객체가 행동을 실행하도록함
class RemoteControl {
public:
	RemoteControl() = default;
	void setCommand(Command* command) { button = command; }
	void pressButton() { button->execute(); }
private:
	Command* button;
};

///////////////////////////////////////////////////////////////////////////////////////////

// 리모컨은 ConcreteCommand를 할당 받은 후 pressButten으로 기기를 실행 할 수 있다.
int main() {
	RemoteControl* remote = new RemoteControl(); // Invoker(호출자)

	Light* light = new Light();					 // Receiver(수신자)
	LightOnCommand* lightOn = new LightOnCommand(light);	// ConcreteCommand
	remote->setCommand(lightOn);
	remote->pressButton();

	Television* television = new Television();
	TelevisionSubtitleOn* tvsub = new TelevisionSubtitleOn(television);
	remote->setCommand(tvsub);
	remote->pressButton();
}

// RemoteControl로 우회하여 동작을 실행시킨다. 
// setCommand를 바꾸면 작동하는 pressButton이 변하기 때문에 Actor를 변화시킨 것이다.