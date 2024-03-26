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
	// 실행 취소 -> Command를 부모로 하는 class에 전부 Undo 함수 선언/정의
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
	void undo() { light->off(); }
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

/////////////////////////////////Television + 자막 세분화/////////////////////////////////

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
		// undo를 위해 전 자막 상태를 저장할 변수를 추가해주어야 한다.
		prevSubtitle = television->getSubtitle();
		television->subtitleKorean();
	}

	void undo() {
		// 이전 상태에 따라 처리한다.
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

	// On에서 자막 종류 고를 때와 똑같은 로직
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
			// 실행 전 행동을 기억하기 위해 실행한 내용을 undoCommand에 저장해 둔다.
			undoCommand = upCommands[num];
		}
	}

	void pressDownButton(int num) {
		if (downCommands[num] != nullptr) {
			downCommands[num]->execute();
			undoCommand = downCommands[num];
		}
	}

	// undo를 눌렀을 때 처리할 함수를 추가한다.
	void pressUndoButton() {
		undoCommand->undo();
	}
private:
	constexpr static int COMMAND_SIZE = 5; // 5개 버튼
	shared_ptr<EmptyCommand> empty = make_shared<EmptyCommand>();
	vector<Command*> upCommands = vector<Command*>(COMMAND_SIZE, empty.get());
	vector<Command*> downCommands = vector<Command*>(COMMAND_SIZE, empty.get());
	Command* undoCommand = empty.get();
};