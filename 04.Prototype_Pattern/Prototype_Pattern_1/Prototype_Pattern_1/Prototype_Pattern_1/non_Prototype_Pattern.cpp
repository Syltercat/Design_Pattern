// Ŭ������ ����, ��� �ڵ嵵 ����, �ݺ� �ڵ嵵 ����.
// ������Ÿ�� �������� �ذ� �����ϴ�.
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