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

// 방금 떨어지기 시작했으니 누군지는 몰라도 알아서 하시오라고 알림을 보내는게 전부이다.
void Physics::updateEntity(Entity& entity) {
	bool wasOnSurface = entity.isOnSurface();
	entity.accelerate(GRAVITY);
	entity.update();

	if (wasOnSurface && !entity.isOnSurface()) {
		notify(entity, EVENT_START_FALL);
	}
}
// 이러면 물리 엔진 코드는 전혀 건드리지 않은 채로 업적 목록을 바꾸거나 업적 시스템을 떼어낼 수도 있다.
// 물리 코드는 누가 받든 말든 계속 알림을 보낸다.