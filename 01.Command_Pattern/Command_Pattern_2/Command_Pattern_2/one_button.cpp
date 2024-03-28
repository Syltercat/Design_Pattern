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
// Light �Ѵ� �۾��� �����Ѵ�.
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

// ��ư�� ������ �ش� ��ü�� �ൿ�� �����ϵ�����
class RemoteControl {
public:
	RemoteControl() = default;
	void setCommand(Command* command) { button = command; }
	void pressButton() { button->execute(); }
private:
	Command* button;
};

///////////////////////////////////////////////////////////////////////////////////////////

// �������� ConcreteCommand�� �Ҵ� ���� �� pressButten���� ��⸦ ���� �� �� �ִ�.
int main() {
	RemoteControl* remote = new RemoteControl(); // Invoker(ȣ����)

	Light* light = new Light();					 // Receiver(������)
	LightOnCommand* lightOn = new LightOnCommand(light);	// ConcreteCommand
	remote->setCommand(lightOn);
	remote->pressButton();

	Television* television = new Television();
	TelevisionSubtitleOn* tvsub = new TelevisionSubtitleOn(television);
	remote->setCommand(tvsub);
	remote->pressButton();
}

// RemoteControl�� ��ȸ�Ͽ� ������ �����Ų��. 
// setCommand�� �ٲٸ� �۵��ϴ� pressButton�� ���ϱ� ������ Actor�� ��ȭ��Ų ���̴�.