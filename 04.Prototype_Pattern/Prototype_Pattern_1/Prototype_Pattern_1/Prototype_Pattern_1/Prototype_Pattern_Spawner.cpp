class Monster {
public:
	virtual ~Monster(){}
	// �߻� �޼��� clone() �߰� -> �ڽ� class���� clone() ����
	virtual Monster* clone() = 0;
};

class Ghost : public Monster {
public:
	Ghost(int _healt, int _speed) : healt(_healt), speed(_speed){}
	virtual Monster* clone() {
		return new Ghost(healt, speed);
	}
private:
	int healt;
	int speed;
};
class Demon : public Monster {
public:
	Demon(int _healt, int _speed) : healt(_healt), speed(_speed) {}
	virtual Monster* clone() {
		return new Demon(healt, speed);
	}
private:
	int healt;
	int speed;
};
class Sorcerer : public Monster {
public:
	Sorcerer(int _healt, int _speed) : healt(_healt), speed(_speed) {}
	virtual Monster* clone() {
		return new Sorcerer(healt, speed);
	}
private:
	int healt;
	int speed;
};


// Monster�� ��ӹ޴� ��� class�� clone �޼��尡 �ִٸ� ������ Ŭ������ �������� ���� �ʿ䰡 ����.
class Spawner {
public:
	Spawner(Monster* _prototype): prototype(_prototype){}
	Monster* spawnMonster() {
		return prototype->clone();
	}
private:
	Monster* prototype;
};


int main() {
	// ���� �����ʸ� ������� �������� ����� ���� �ν��Ͻ��� ���� �Ŀ� �����ʿ� �����ϸ� �ȴ�.
	Monster* ghostPrototype = new Ghost(15, 3);
	Spawner* ghostSpawner = new Spawner(ghostPrototype);
}

// �׷��� �ڵ��� ���� ���� ���̳��� �ʴ� ���� Ȯ���� �� �ִ�.


// ���� �Լ�
/*
�տ����� ��� ���� ���� ������ ������ Ŭ������ �ʿ�������,
���� �Լ��� ����ϸ� ����ڵ尡 ����.

Monster* spawnGhost(){
	return new Ghost();
}

typedef Monster* (*SpawnCallback)();

class Spawner{
public:
	Spawner(SpawnCallback _spawn): spawn(_spawn){}
	Monster* spawnMonster(){ return spawn();}	
private:
	SpawnCallback spawn;
};

Spawner* ghostSpawner = new Spawner(spawnGhost);

���� ������ Ŭ�������� �Լ� ������ �ϳ��� �θ� �ȴ�.
*/

// ���ø�
/*
���� Ŭ������ ���ø� Ÿ�� �Ű������� ������ �� �ִ�.

class Spawner{
public:
	virtual ~Spawner(){}
	virtual Monster* spawnMonster() = 0;
};

template<class T>
class SpawnerFor:: public Spawner{
public:
	virtual Monster* spawnMonster(){
		return new T();
	}
};

Spawner* ghostSpawner = new SpawnerFor<Ghost>();
*/