#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

/////////////////////////////////Command/////////////////////////////////

class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class EmptyCommand:public Command {
public:
	void execute() { cout << "This command is empty\n"; }
};

/////////////////////////////////Light/////////////////////////////////

class Light {
public:
	void on() { cout << "on\n"; }
	void off() { cout << "off\n"; }

};

class LightOn : public Command {
public:
	LightOn(Light* l): light(l) { }
	void execute() { light->on(); }
private:
	Light* light;
};

class LightOff : public Command {
public:
	LightOff(Light* l) : light(l) { }
	void execute() { light->off(); }
private:
	Light* light;
};

/////////////////////////////////Television/////////////////////////////////

class Television {
public:
	void channel_Up() { cout << "up\n"; }
	void channel_Down() { cout << "Down\n"; }
	void subtitle_On() { cout << "subtitle On\n"; }
	void subtitle_Off() { cout << "subtitle Off\n"; }
};

class TelevisionChannelUp :public Command {
public:
	TelevisionChannelUp(Television* tv) :television(tv) {}
	void execute() { television->channel_Up(); }

private:
	Television* television;
};

class TelevisionChannelDown :public Command {
public:
	TelevisionChannelDown(Television* tv) :television(tv) {}
	void execute() { television->channel_Down(); }

private:
	Television* television;
};

class TelevisionSubtitleOn :public Command {
public:
	TelevisionSubtitleOn(Television* tv) :television(tv) {}
	void execute() { television->subtitle_On(); }

private:
	Television* television;
};

class TelevisionSubtitleOff :public Command {
public:
	TelevisionSubtitleOff(Television* tv) :television(tv) {}
	void execute() { television->subtitle_Off(); }

private:
	Television* television;
};

/////////////////////////////////RemoteControl/////////////////////////////////

class RemoteControl {
public:
	RemoteControl() = default;
	void setCommand(Command* upCommand, Command* downCommand, int num) {
		upCommands[num] = upCommand;
		downCommands[num] = downCommand;
	}
	void pressUpButton(int num) { 
		if (upCommands[num] != nullptr) {
			upCommands[num]->execute();
		}
	}

	void pressDownButton(int num) {
		if (downCommands[num] != nullptr) {
			downCommands[num]->execute();
		}
	}
private:
	// constexpr 해당 객체나 함수의 리턴값을 컴파일 타임에 값을 계산하여 알 수 있다. const와 비슷하게 변경을 할 수 없다.
	constexpr static int COMMAND_SIZE = 5; // 5개 버튼
	// shared_ptr: 스마트 포인터 클래스 중 하나로 포인터를 더이상 사용하지 않는 경우 메모리를 자동 해제시킨다. 
	//			   vector나 map의 원소로 많이 사용한다. 멤버함수인 get()을 사용해서 shared_ptr이 가리키고 있는 내부 포인터에 접근할 수 있다.
	shared_ptr<EmptyCommand> empty = make_shared<EmptyCommand>();
	vector<Command*> upCommands = vector<Command*>(COMMAND_SIZE, empty.get());
	vector<Command*> downCommands = vector<Command*>(COMMAND_SIZE, empty.get());
};

/////////////////////////////////main/////////////////////////////////

int main() {
	RemoteControl* remote = new RemoteControl();	// Invoker

	Light* light = new Light(); // Receiver
	LightOn* lightOn = new LightOn(light); // Concrete Command
	LightOff* lightoff = new LightOff(light);

	Television* television = new Television();
	TelevisionChannelUp* tvChannelUp = new TelevisionChannelUp(television);
	TelevisionChannelDown* tvChannelDown = new TelevisionChannelDown(television);
	TelevisionSubtitleOn* tvSubtitleOn = new TelevisionSubtitleOn(television);
	TelevisionSubtitleOff* tvSubtitleOff = new TelevisionSubtitleOff(television);

	remote->setCommand(lightOn, lightoff, 0);
	remote->setCommand(tvChannelUp, tvChannelDown, 1);
	remote->setCommand(tvSubtitleOn, tvSubtitleOff, 2);

	for (int i = 0; i < 5; i++)
	{
		cout << i << "> up   / on  command : "; remote->pressUpButton(i);
		cout << i << "> down / off command : "; remote->pressDownButton(i);
	}
}
// setCommand로 각 벡터의 원소로 저장되어있는 명령을 출력한다.
// num에 따라 Actor를 바꿔가며 동작시킬 수 있다.