#include <random>
#define WIDTH 10
#define HEIGHT 10
using namespace std;

class Texture{

};

Texture GRASS_TEXTURE;
Texture HILL_TEXTURE;
Texture RIVER_TEXTURE;

// ĸ��ȭ�� ���ؼ� ���� Ŭ������ ���� �������.
class Terrain {
public:
	Terrain(int movementCost, bool isWater, Texture texture)
		: movementCost_(movementCost),
		  isWater_(isWater),
		  texture_(texture) { }

	// �޸𸮸� ���̰ڴٰ� �޸𸮸� �����ϵ��� �ߴµ� �� ������ �ٲ� ���� ���� ������ ���ÿ� ��Ÿ���� ������ ���� �� �ִ�
	// �� ������ �淮 ��ü�� ���� �Ұ����� ���·� ����� ���� �Ϲ����̴�.
	// ������ �б� ���� �Լ��� ����� ���� const�� ���δ�.
	int getMovementCost() const { return movementCost_; }
	bool isWater() const { return isWater_; }
	const Texture& getTextrue() const { return texture_; }

private:
	int movementCost_;
	bool isWater_;
	Texture texture_;
};

// ���� Terrain Ŭ�������� Ÿ���� ��ġ�� ���õ� ������ ���� ����. �淮 ���Ͻ����� ���� ��� ���� ���´� �����ϴ�.
// �� ���� ����(���� ����)�� �ش��Ѵ�.
// ���� ���� �������� Terrain ��ü�� ������ ���� �ʿ䰡 ����.

// ������ ���� ��� Ǯ�� Ÿ���� ���� �����ϹǷ� 
// World Ŭ���� ���� ��� ������ �������̳� Terrain ��ü ��� Terrain ��ü�� �����͸� ���� �� �ִ�.

// �Ʒ��� ������ ��� ������ �޶��� World ��ü�̴�.
/*
class World {
private:
	Terrain* tiles[WIDTH][HEIGHT];
};
*/
// ���� ������ ���� Ÿ�ϵ��� ��� ���� Terrain �ν��Ͻ� �����͸� ���´�.
// Ǯ���� �ʿ��� ��ŭ ������ �Ͱ��� �ٸ��� Ǯ�� ���� ������ ����� �ּҸ� ����ϱ� ������(�ν��Ͻ� ����)
// �޸� ��뷮�� �پ��� ���̴�.

// �׷��� ��ó�� �ּҸ� �����ϸ� Terrain �ν��Ͻ��� ���� ������ ���Ǵ� ����, �������� �Ҵ��ϸ� �����ֱ⸦ �����ϱ� ���������.
// ���� World Ŭ������ �����Ѵ�. 

// World: ������ �� ��ü�� ��Ÿ���� class�� WIDTH��, HEIGHT�� ���� Ÿ���� �׸��带 �����Ѵ�.
class World {
public:
	World() : grassTerrain_(1, false, GRASS_TEXTURE),
		hillTerrain_(3, false, HILL_TEXTURE),
		riverTerrain_(2, true, RIVER_TEXTURE) { }

	void generateTerrain();
	const Terrain& getTile(int, int)const;

private:
	// �� Ÿ���� Ư�� Terrain ��ü�� �����Ѵ�. (� Ÿ���� Ǯ���̸� �� Ÿ���� grassTerrain_ �ν��Ͻ��� ����)
	Terrain* tiles[WIDTH][HEIGHT];

	// �Ʒ� ��ü�� �̸� �����ǰ� �ʱ�ȭ �Ǹ�, World�� ���� �⵿ֱ�� ���������� �����ϸ� ��� Ÿ�Ͽ��� �����ȴ�.
	// �ش� ��ü���� ���� �ֱ⸦ World Ŭ������ ���߾� �����ϱ� �����ϵ��� World Ŭ���� ���� Terrain ��ü�� �����Ѵ�.
	// (World ��ü�� ������ ��, �� Terrain ��ü�鵵 �Բ� �����ǰ�, World ��ü�� �Ҹ�� �� �Բ� �Ҹ�)
	Terrain grassTerrain_;
	Terrain hillTerrain_;
	Terrain riverTerrain_;

};

// ��� �Լ��� �Ʒ��� ���� ���� ä�� �� �ִ�.
void World::generateTerrain() {
	// ���� Ǯ�� ä��
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			// ����� � �д�.
			if (rand() % 10 == 0) {
				tiles[x][y] = &hillTerrain_;
			}
			else {
				tiles[x][y] = &grassTerrain_;
			}
		}
	}
	// ���� ���´�.
	int x = rand() % WIDTH;
	for (int y = 0; y < HEIGHT; y++) {
		tiles[x][y] = &riverTerrain_;
	}
}

// ���� ���� �Ӽ� ���� World�� �޼��� ��ſ� Terrain ��ü���� �ٷ� ���� �� �ִ�.
const Terrain& World::getTile(int x, int y)const {
	return *tiles[x][y];
}

// World Ŭ������ �� �̻� ������ ���� ������ Ŀ�ø����� �ʴ´�. Ÿ�� �Ӽ��� Terrain ��ü���� �ٷ� ���� �� �ֱ� �����̴�.
int main() {
	World world;
	int cost = world.getTile(2, 3).getMovementCost();
}

/*
���� �����͸� �����ͷ� �����Ѵٴ� ���� ������ȸ�Ѵٴ� �ǹ��̴�.
�̵� ��배�� ���� ������ ���� �������� ���� ���� �����ͷκ��� ���� ��ü �����͸� ���� ��, 
�����͸� ���ؼ� �̵� ��� ���� ���� �Ѵ�.
�̷��� �����͸� ���󰡸� ĳ�� �̽��� �߻��� �� �־� ������ ���������ٴ� ���� ������ �� �ִ�.

�׷��� ��ü�� �޸𸮿� � ������ ��ġ�Ǵ��Ŀ� ���� �޶�����. (�淮������ enum���� ���� ��쵵 �ֱ���)
*/

// �������� ������ ������ ���� ���ù��� ���� �����̶�� �淮������ ���� ����غ���.