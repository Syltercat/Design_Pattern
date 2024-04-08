class Monster {
public:
	virtual ~Monster(){}
	// 추상 메서드 clone() 추가 -> 자식 class에서 clone() 구현
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


// Monster를 상속받는 모든 class에 clone 메서드가 있다면 스포터 클래스를 종류별로 만들 필요가 없다.
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
	// 유령 스포너를 만들려면 원형으로 사용할 유령 인스턴스를 만든 후에 스포너에 전달하면 된다.
	Monster* ghostPrototype = new Ghost(15, 3);
	Spawner* ghostSpawner = new Spawner(ghostPrototype);
}

// 그러나 코드의 양은 별반 차이나지 않는 것을 확인할 수 있다.


// 스폰 함수
/*
앞에서는 모든 몬스터 마다 별도의 스포너 클래스가 필요했으나,
스폰 함수를 사용하면 행사코드가 적다.

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

이제 스포너 클래스에는 함수 포인터 하나만 두면 된다.
*/

// 템플릿
/*
몬스터 클래스를 템플릿 타입 매개변수로 전달할 수 있다.

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