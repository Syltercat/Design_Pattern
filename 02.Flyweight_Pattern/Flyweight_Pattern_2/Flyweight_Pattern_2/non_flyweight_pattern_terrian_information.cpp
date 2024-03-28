// 지형 정보
/*
땅을 타일 기반으로 만든다고 가정하면, 땅은 작은 타일들이 모인 거대한 격자가 된다.
모든 타일은 지형 종류 중 하나로 덮여있을 때 지형 종류는 게임 플레이에 영향을 주는 속성이 들어있다.
ex.) 
플레이어가 얼마나 빠르게 이동할 수 있는지를 결정하는 이동 비용 값
강처럼 보트로 건널 수 있는 곳인지 여부
렌더링할 때 싸용할 텍스처
*/

#define WIDTH 10
#define HEIGHT 10

// 지형 속성을 구분하기 위해 열거형을 사용하여 분류한다.
enum Terrain {
	TERRAIN_GRASS,
	TERRAIN_HILL,
	TERRAIN_RIVER,
	// ...
};

// 월드는 지형을 거대한 격자로 관리한다.
class World {
public:
	int getMovementCost(int, int);
	bool isWater(int, int);
private:
	Terrain tiles[WIDTH][HEIGHT];
};

// 타일과 관련한 데이터는 아래 코드로 얻을 수 있다.
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
잘 동작하지만 이동 비용이나 물인지 땅인지의 여부는 지형에 관한 데이터인데
이 코드에서는 하드코딩 되어있다.
게다가 같은 지형 종류에 대한 데이터가 여러 메서드에 나뉘어 있는데 
이런 데이터는 하나로 합쳐서 캡슐화하는 게 좋다.
*/