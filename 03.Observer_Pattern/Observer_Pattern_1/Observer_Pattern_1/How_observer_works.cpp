class Entity {
public:
	bool isHero() const { return true; }
};

enum Event {
	EVENT_ENTITY_FELL,
};

// 1. 관찰자
class Observer {
public:
	virtual ~Observer(){}
	virtual void onNotify(const Entity& entity, Event event) = 0;
};

Achievemnets ACHIEVMENT_FELL_OFF_BRIDGE;

class Achievemnets : public Observer {
public:
	virtual void onNotify(const Entity& entity, Event event) {
		switch (event)
		{
		case EVENT_ENTITY_FELL:
			if(entity.isHero() && heroIsOnBridgh){
				unlock(ACHIEVMENT_FELL_OFF_BRIDGE);
			}
			break;
			// 그 외의 다른 이벤트를 처리하고 ..
			// heroIsBridge의 값을 업데이트 한다.
		}
	}
private:
	void unlock(Achievemnets achievement) {
		// 아직 업적이 잠겨있다면 잠금 해제한다.
	}
	bool heroIsOnBridgh;
};

const int MAX_OBSERVERS = 10;

// 2. 대상 (Subject)
class Subject {
// 관찰자 목록을 밖에서 볼 수 있도록 public으로 API를 열어놨다.
public:
	void addObserver(Observer* observer_) {
		// 배열에 관찰자를 추가한다.
	}
	void removeObserver(Observer* observer_) {
		// 배열에서 관찰자를 제거한다.
	}

// 알림을 기다리는 관찰자 목록을 들고있어야 한다.
private:
	Observer* observers[MAX_OBSERVERS];
	int numObservers;

// 관찰자를 여러개 등록할 수 있게 하려면 관찰자들이 각자 독립적으로 다뤄지는 것을 보장할 수 있다.
protected:
	void notify(const Entity& entity, Event event) {
		for (int i = 0; i < numObservers; ++i) {
			observers[i]->onNotify(entity, event);
		}
	}
};
// => 대상은 관찰자와 상호작용 하지만, 커플링되어있지는 않다.

// 3. 물리 관찰
// 남은 작업은 물리 엔진에 훅을 걸어 알림을 보낼 수 있게 하는 것과 업적 시스템에서 알림을 받을 수 있도록 스스로를 등록하게 하는 일이다.
class Physics : public Subject {
public:
	void updateEntity(Entity& entity);
};

// 이렇게 하면 Subject 클래스의 notify() 메서드를 protected로 만들 수 있다. 
// Subject를 상속받은 Physics 클래스는 notify()를 통해 알림을 보낼 수 있지만,
// 밖에서는 notify()에 접글할 수 없다.
// 반면, addObserver()와 removeObserver()는 public이기 때문에 물리 시스템에 접근할 수만 있다면 어디서나 물리 시스템을 관찰할 수 있다.