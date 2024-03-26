// Command Pattern으로 생성된 패턴을 이용하여 조합된 새로운 패턴을 생성할 수 있다.
#include "New_Pattern_base_header.h"

class RoutineCommand : public Command {
public:
	RoutineCommand(const vector<Command*> &c) : commands(c) { }
	void execute() {
		for (const auto& command : commands)
			command->execute();
	}
	void undo() {
		for (int i = commands.size() - 1; i >= 0; i--) {
			commands[i]->undo();
		}
	}
private:
	vector<Command*> commands;
};

int main()
{
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

	vector<Command*> ModeOn = { tvSubtitleEnglish, lightOff };
	vector<Command*> ModeOff = { tvSubtitleOff, lightOn };

	RoutineCommand* ModeOnCommand = new RoutineCommand(ModeOn);
	RoutineCommand* ModeOffCommand = new RoutineCommand(ModeOff);

	remote->setCommand(ModeOnCommand, ModeOffCommand, 4);

	cout << "Mode On\n";
	remote->pressUpButton(4);
	cout << "\nMode Off\n";
	remote->pressDownButton(4);
	cout << "\nMode Undo\n";
	remote->pressUndoButton();

	return 0;
}