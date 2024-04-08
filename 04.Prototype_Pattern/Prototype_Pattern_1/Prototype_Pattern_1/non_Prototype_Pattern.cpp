// 클래스도 많고, 행사 코드도 많고, 반복 코드도 많다.
// 프로토타입 패턴으로 해결 가능하다.
class Monster {

};

class Ghost : public Monster {};
class Demon : public Monster {};
class Sorcerer : public Monster {};

class Spawner {
public:
	virtual ~Spawner() {};
	virtual Monster* spawnMonster() = 0;
};

class GhostSpawner :public Spawner {
public:
	virtual Monster* spawnMonster() {
		return new Ghost();
	}
};

class DemonSpawner :public Spawner {
public:
	virtual Monster* spawnMonster() {
		return new Demon();
	}
};

class SorcererSpawner :public Spawner {
public:
	virtual Monster* spawnMonster() {
		return new Sorcerer();
	}
};