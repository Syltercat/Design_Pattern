#include "Command.h"
#include <iostream>
using namespace std;

void JumpCommand::execute(GameActor& actor) {
	actor.jump();
}

void FireCommand::execute(GameActor& actor) {
	actor.fire();
}

// ó���� ����� Ű ����, Ű�� �����ϰ� �ʹٸ� JumpKey, FireKey ���� ���� �������ָ� �ȴ�.
inputHandler::inputHandler() {
	JumpKey = 'x';
	FireKey = 'z';
	c_ptr = nullptr;
}

// �Է¹��� key�� ���� c_ptr�� Command�� ���� �ִµ� return�� �ٷ� ���� �ʰ� c_ptr�� �־��ִ� ������
// undo ����� �߰��� �� ����� Command�� ������ ������ �ʿ��ϱ� �����̴�.
Command* inputHandler::handleInput(char command) {
	if (command == FireKey) {
		c_ptr = new FireCommand();
	}
	else if (command == JumpKey) {
		c_ptr = new JumpCommand();
	}
	else 
		return nullptr;
	cmd_stack.push(c_ptr);
	return c_ptr;
}

// ���� ��� (stack�� ���� ����� ������ �� pop�ϴ� ���·� �����Ѵ�.)
void inputHandler::undo() {
	if (!cmd_stack.empty()) {
		cout << "Undo address: " << cmd_stack.top() << endl;
		cmd_stack.pop();
	}
}