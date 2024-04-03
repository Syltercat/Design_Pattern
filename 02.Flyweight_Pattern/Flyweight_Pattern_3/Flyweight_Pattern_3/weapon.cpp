#include <iostream>
using namespace std;

enum WEAPON {
	GUN,
	KNIFE,
	BOMB,
	WEAPON_END
};

class weapon {
public:
	weapon(float weapondamage, float weaponweight, int numofweapon)
		:damage(weapondamage), weight(weaponweight), number(numofweapon){}
	
	float getdamage() const { return damage; }
	float getweight() const { return weight; }
	int getnum() const { return number; }

private:
	float damage;
	float weight;
	int number;
};

class Player {
public:
	Player(): gun(3.0f, 5.0f, 1), knife(1.5f, 3.0f, 2), bomb(5.0f, 5.0f, 5){}
	
	weapon* weaponInventory[3];

	void setInventory() {
		weaponInventory[0] = &gun;
		weaponInventory[1] = &knife;
		weaponInventory[2] = &bomb;
	}
	const weapon& getweaponInfo(int i) {
		return *weaponInventory[i];
	}
private:
	weapon gun;
	weapon knife;
	weapon bomb;
};

int main() {
	Player P1;
	P1.setInventory();
	float gunweapondamage = P1.getweaponInfo(GUN).getdamage();
	cout << "총 데미지: " << gunweapondamage << endl;
}

// 플레이어가 소지하는 무기를 intrinsic으로 둔 예제