#pragma once
class GameActor
{
public:
	virtual ~GameActor() {};
	virtual void jump() = 0;
	virtual void fire() = 0;
private:

};

class Hero :public GameActor {
public:
	void jump();
	void fire();
};

class Enemy :public GameActor {
public:
	void jump();
	void fire();
};

