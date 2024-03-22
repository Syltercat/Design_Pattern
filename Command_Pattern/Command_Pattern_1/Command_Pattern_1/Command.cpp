#include "Command.h"
#include <iostream>
using namespace std;

void JumpCommand::execute(GameActor& actor) {
	actor.jump();
}

void FireCommand::execute(GameActor& actor) {
	actor.fire();
}

// 처음에 사용할 키 지정, 키를 변경하고 싶다면 JumpKey, FireKey 값만 새로 설정해주면 된다.
inputHandler::inputHandler() {
	JumpKey = 'x';
	FireKey = 'z';
	c_ptr = nullptr;
}

// 입력받은 key에 따라 c_ptr에 Command를 집어 넣는데 return을 바로 하지 않고 c_ptr에 넣어주는 이유는
// undo 기능을 추가할 때 실행된 Command를 저장할 변수가 필요하기 때문이다.
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

// 실행 취소 (stack에 이전 명령을 저장한 후 pop하는 형태로 구현한다.)
void inputHandler::undo() {
	if (!cmd_stack.empty()) {
		cout << "Undo address: " << cmd_stack.top() << endl;
		cmd_stack.pop();
	}
}