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
	// constexpr �ش� ��ü�� �Լ��� ���ϰ��� ������ Ÿ�ӿ� ���� ����Ͽ� �� �� �ִ�. const�� ����ϰ� ������ �� �� ����.
	constexpr static int COMMAND_SIZE = 5; // 5�� ��ư
	// shared_ptr: ����Ʈ ������ Ŭ���� �� �ϳ��� �����͸� ���̻� ������� �ʴ� ��� �޸𸮸� �ڵ� ������Ų��. 
	//			   vector�� map�� ���ҷ� ���� ����Ѵ�. ����Լ��� get()�� ����ؼ� shared_ptr�� ����Ű�� �ִ� ���� �����Ϳ� ������ �� �ִ�.
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
// setCommand�� �� ������ ���ҷ� ����Ǿ��ִ� ����� ����Ѵ�.
// num�� ���� Actor�� �ٲ㰡�� ���۽�ų �� �ִ�.