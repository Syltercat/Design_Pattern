// ���� ����
/*
���� Ÿ�� ������� ����ٰ� �����ϸ�, ���� ���� Ÿ�ϵ��� ���� �Ŵ��� ���ڰ� �ȴ�.
��� Ÿ���� ���� ���� �� �ϳ��� �������� �� ���� ������ ���� �÷��̿� ������ �ִ� �Ӽ��� ����ִ�.
ex.) 
�÷��̾ �󸶳� ������ �̵��� �� �ִ����� �����ϴ� �̵� ��� ��
��ó�� ��Ʈ�� �ǳ� �� �ִ� ������ ����
�������� �� �ο��� �ؽ�ó
*/

#define WIDTH 10
#define HEIGHT 10

// ���� �Ӽ��� �����ϱ� ���� �������� ����Ͽ� �з��Ѵ�.
enum Terrain {
	TERRAIN_GRASS,
	TERRAIN_HILL,
	TERRAIN_RIVER,
	// ...
};

// ����� ������ �Ŵ��� ���ڷ� �����Ѵ�.
class World {
public:
	int getMovementCost(int, int);
	bool isWater(int, int);
private:
	Terrain tiles[WIDTH][HEIGHT];
};

// Ÿ�ϰ� ������ �����ʹ� �Ʒ� �ڵ�� ���� �� �ִ�.
int World::getMovementCost(int x, int y) {
	switch (tiles[x][y])
	{
	case TERRAIN_GRASS: 
		return 1;
	case TERRAIN_HILL:
		return 2;
	case TERRAIN_RIVER:
		return 3;
	//...
	}
}

bool World::isWater(int x, int y) {
	switch (tiles[x][y])
	{
	case TERRAIN_GRASS:
		return false;
	case TERRAIN_HILL:
		return false;
	case TERRAIN_RIVER:
		return true;
		//...
	}
}

/* 
�� ���������� �̵� ����̳� ������ �������� ���δ� ������ ���� �������ε�
�� �ڵ忡���� �ϵ��ڵ� �Ǿ��ִ�.
�Դٰ� ���� ���� ������ ���� �����Ͱ� ���� �޼��忡 ������ �ִµ� 
�̷� �����ʹ� �ϳ��� ���ļ� ĸ��ȭ�ϴ� �� ����.
*/