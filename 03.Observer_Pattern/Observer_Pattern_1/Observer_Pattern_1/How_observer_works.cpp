class Entity {
public:
	bool isHero() const { return true; }
};

enum Event {
	EVENT_ENTITY_FELL,
};

// 1. ������
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
			// �� ���� �ٸ� �̺�Ʈ�� ó���ϰ� ..
			// heroIsBridge�� ���� ������Ʈ �Ѵ�.
		}
	}
private:
	void unlock(Achievemnets achievement) {
		// ���� ������ ����ִٸ� ��� �����Ѵ�.
	}
	bool heroIsOnBridgh;
};

const int MAX_OBSERVERS = 10;

// 2. ��� (Subject)
class Subject {
// ������ ����� �ۿ��� �� �� �ֵ��� public���� API�� �������.
public:
	void addObserver(Observer* observer_) {
		// �迭�� �����ڸ� �߰��Ѵ�.
	}
	void removeObserver(Observer* observer_) {
		// �迭���� �����ڸ� �����Ѵ�.
	}

// �˸��� ��ٸ��� ������ ����� ����־�� �Ѵ�.
private:
	Observer* observers[MAX_OBSERVERS];
	int numObservers;

// �����ڸ� ������ ����� �� �ְ� �Ϸ��� �����ڵ��� ���� ���������� �ٷ����� ���� ������ �� �ִ�.
protected:
	void notify(const Entity& entity, Event event) {
		for (int i = 0; i < numObservers; ++i) {
			observers[i]->onNotify(entity, event);
		}
	}
};
// => ����� �����ڿ� ��ȣ�ۿ� ������, Ŀ�ø��Ǿ������� �ʴ�.

// 3. ���� ����
// ���� �۾��� ���� ������ ���� �ɾ� �˸��� ���� �� �ְ� �ϴ� �Ͱ� ���� �ý��ۿ��� �˸��� ���� �� �ֵ��� �����θ� ����ϰ� �ϴ� ���̴�.
class Physics : public Subject {
public:
	void updateEntity(Entity& entity);
};

// �̷��� �ϸ� Subject Ŭ������ notify() �޼��带 protected�� ���� �� �ִ�. 
// Subject�� ��ӹ��� Physics Ŭ������ notify()�� ���� �˸��� ���� �� ������,
// �ۿ����� notify()�� ������ �� ����.
// �ݸ�, addObserver()�� removeObserver()�� public�̱� ������ ���� �ý��ۿ� ������ ���� �ִٸ� ��𼭳� ���� �ý����� ������ �� �ִ�.