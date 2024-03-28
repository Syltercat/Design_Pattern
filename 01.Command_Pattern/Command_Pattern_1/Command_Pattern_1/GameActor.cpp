#include "GameActor.h"
#include <iostream>
using namespace std;

void Hero::jump() {
	cout << "Hero is jumping" << endl;
}


void Hero::fire() {
	cout << "Hero is firing" << endl;
}

void Enemy::jump() {
	cout << "Enemy is jumping" << endl;
}

void Enemy::fire() {
	cout << "Enemy is firing" << endl;
}