#pragma once
#include "GameActor.h"
#include <stack>
using namespace std;

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(GameActor& actor) = 0;
};

class JumpCommand : public Command {
public:
	virtual void execute(GameActor& actor);
};

class FireCommand : public Command {
public:
	virtual void execute(GameActor& actor);
};

class inputHandler {
public:
	inputHandler();
	void undo();
	Command* handleInput(char command);

private:
	stack<Command*> cmd_stack;
	Command* c_ptr;
	char JumpKey;
	char FireKey;
};

