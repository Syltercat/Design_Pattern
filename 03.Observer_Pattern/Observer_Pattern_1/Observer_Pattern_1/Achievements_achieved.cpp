#include <iostream>
using namespace std;

float GRAVITY = 10.0f;

enum SURFACE {
	NOTSURFACE,
	ISSURFACE
};
enum EVENT {
	EVENT_START_FALL,
	EVENT_END
};

class Entity {
public:
	bool isOnSurface() { return State; }
	float accelerate(float g) { return g * speed; }
	void update() { cout << "update" << endl; }
private:
	SURFACE State;
	float speed = 10.0f;
};

class Physics {
public:
	void notify(Entity, EVENT) { cout << "notify"; }
	void updateEntity(Entity&);
};

// ��� �������� ���������� �������� ���� �˾Ƽ� �Ͻÿ���� �˸��� �����°� �����̴�.
void Physics::updateEntity(Entity& entity) {
	bool wasOnSurface = entity.isOnSurface();
	entity.accelerate(GRAVITY);
	entity.update();

	if (wasOnSurface && !entity.isOnSurface()) {
		notify(entity, EVENT_START_FALL);
	}
}
// �̷��� ���� ���� �ڵ�� ���� �ǵ帮�� ���� ä�� ���� ����� �ٲٰų� ���� �ý����� ��� ���� �ִ�.
// ���� �ڵ�� ���� �޵� ���� ��� �˸��� ������.