#include <iostream>
#include "Command.h"
#include "GameActor.h"
using namespace std;

int main() {
	inputHandler iH;
	Hero myH;

	iH.handleInput('z')->execute(myH);
	iH.handleInput('x')->execute(myH);
	iH.undo();
}