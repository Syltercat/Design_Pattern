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
	// ���� ��� -> Command�� �θ�� �ϴ� class�� ���� Undo �Լ� ����/����
	virtual void undo() = 0;
};

class EmptyCommand :public Command {
public:
	void execute() { cout << "This command is empty\n"; }
	void undo() { cout << "Can't undo. This command is empty\n"; }
};

/////////////////////////////////Light/////////////////////////////////

class Light {
public:
	void on() { cout << "on\n"; }
	void off() { cout << "off\n"; }

};

class LightOn : public Command {
public:
	LightOn(Light* l) : light(l) { }
	void execute() { light->on(); }
	void undo(){ light->off(); }
private:
	Light* light;
};

class LightOff : public Command {
public:
	LightOff(Light* l) : light(l) { }
	void execute() { light->off(); }
	void undo() { light->on(); }
private:
	Light* light;
};

/////////////////////////////////Television + �ڸ� ����ȭ/////////////////////////////////

class Television {
public:
	enum class Subtitle { OFF, KOREAN, ENGLISH };
	void channel_Up() { cout << "up\n"; }
	void channel_Down() { cout << "Down\n"; }
	void subtitleKorean()
	{
		cout << "Subtitle Korean" << endl;
		subtitle = Subtitle::KOREAN;
	}

	void subtitleEnglish()
	{
		cout << "Subtitle English" << endl;
		subtitle = Subtitle::ENGLISH;
	}

	void subtitleOff()
	{
		cout << "Subtitle Off" << endl;
		subtitle = Subtitle::OFF;
	}

	Subtitle getSubtitle() { return subtitle; }
private:
	Subtitle subtitle = Subtitle::OFF;
};

class TelevisionChannelUp :public Command {
public:
	TelevisionChannelUp(Television* tv) :television(tv) {}
	void execute() { television->channel_Up(); }
	void undo() { television->channel_Down(); }
	
private:
	Television* television;
};

class TelevisionChannelDown :public Command {
public:
	TelevisionChannelDown(Television* tv) :television(tv) {}
	void execute() { television->channel_Down(); }
	void undo() { television->channel_Up(); }

private:
	Television* television;
};

class TelevisionSubtitleKorean : public Command
{
public:
	TelevisionSubtitleKorean(Television* tv) : television(tv) { }

	void execute() {
		// undo�� ���� �� �ڸ� ���¸� ������ ������ �߰����־�� �Ѵ�.
		prevSubtitle = television->getSubtitle();
		television->subtitleKorean();
	}

	void undo() {
		// ���� ���¿� ���� ó���Ѵ�.
		switch (prevSubtitle)
		{
		case Television::Subtitle::KOREAN:
			television->subtitleKorean();
			break;
		case Television::Subtitle::ENGLISH:
			television->subtitleEnglish();
			break;
		case Television::Subtitle::OFF:
			television->subtitleOff();
			break;
		default:
			break;
		}
	}
private:
	Television* television;
	Television::Subtitle prevSubtitle;
};

class TelevisionSubtitleEnglish : public Command
{
public:
	TelevisionSubtitleEnglish(Television* tv) : television(tv) { }

	void execute() {
		prevSubtitle = television->getSubtitle();
		television->subtitleEnglish();
	}

	void undo() {
		switch (prevSubtitle)
		{
		case Television::Subtitle::KOREAN:
			television->subtitleKorean();
			break;
		case Television::Subtitle::ENGLISH:
			television->subtitleEnglish();
			break;
		case Television::Subtitle::OFF:
			television->subtitleOff();
			break;
		default:
			break;
		}
	}
private:
	Television* television;
	Television::Subtitle prevSubtitle;
};

class TelevisionSubtitleOff : public Command
{
public:
	TelevisionSubtitleOff(Television* tv) : television(tv) { }

	// On���� �ڸ� ���� �� ���� �Ȱ��� ����
	void execute() override
	{
		prevSubtitle = television->getSubtitle();
		television->subtitleOff();
	}

	void undo() override
	{
		switch (prevSubtitle)
		{
		case Television::Subtitle::KOREAN:
			television->subtitleKorean();
			break;
		case Television::Subtitle::ENGLISH:
			television->subtitleEnglish();
			break;
		case Television::Subtitle::OFF:
			television->subtitleOff();
			break;
		default:
			break;
		}
	}
private:
	Television* television;
	Television::Subtitle prevSubtitle;
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
			// ���� �� �ൿ�� ����ϱ� ���� ������ ������ undoCommand�� ������ �д�.
			undoCommand = upCommands[num];
		}
	}

	void pressDownButton(int num) {
		if (downCommands[num] != nullptr) {
			downCommands[num]->execute();
			undoCommand = downCommands[num];
		}
	}

	// undo�� ������ �� ó���� �Լ��� �߰��Ѵ�.
	void pressUndoButton() {
		undoCommand->undo();
	}
private:
	constexpr static int COMMAND_SIZE = 5; // 5�� ��ư
	shared_ptr<EmptyCommand> empty = make_shared<EmptyCommand>();
	vector<Command*> upCommands = vector<Command*>(COMMAND_SIZE, empty.get());
	vector<Command*> downCommands = vector<Command*>(COMMAND_SIZE, empty.get());
	Command* undoCommand = empty.get();
};

/////////////////////////////////main/////////////////////////////////

int main() {
	RemoteControl* remote = new RemoteControl(); // Invoker

	Light* light = new Light(); // Receiver
	LightOn* lightOn = new LightOn(light); // ConcreteCommand 
	LightOff* lightOff = new LightOff(light);

	Television* television = new Television();
	TelevisionChannelUp* tvChannelUp = new TelevisionChannelUp(television);
	TelevisionChannelDown* tvChannelDown = new TelevisionChannelDown(television);
	TelevisionSubtitleKorean* tvSubtitleKorean = new TelevisionSubtitleKorean(television);
	TelevisionSubtitleEnglish* tvSubtitleEnglish = new TelevisionSubtitleEnglish(television);
	TelevisionSubtitleOff* tvSubtitleOff = new TelevisionSubtitleOff(television);

	remote->setCommand(lightOn, lightOff, 0);
	remote->setCommand(tvChannelUp, tvChannelDown, 1);
	remote->setCommand(tvSubtitleKorean, tvSubtitleOff, 2);
	remote->setCommand(tvSubtitleEnglish, tvSubtitleOff, 3);

	// ������ ������ ����.

	cout << "UNDO TEST" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << i << "> up   / on  command : "; remote->pressUpButton(i);
		cout << i << "> undo               : "; remote->pressUndoButton();
		cout << i << "> down / off command : "; remote->pressDownButton(i);
		cout << i << "> undo               : "; remote->pressUndoButton();
	}

	// i=4�� ��� excute�� undo�� �ȵȴ�. (empty.get()�� ó���� ��ϵ� EmptyCoomand�̱� ���� �̱� ����)

	cout << endl;
	cout << "UNDO SUBTITLE TEST" << endl;
	remote->pressUpButton(2);
	remote->pressUpButton(3);
	remote->pressUndoButton();
}
