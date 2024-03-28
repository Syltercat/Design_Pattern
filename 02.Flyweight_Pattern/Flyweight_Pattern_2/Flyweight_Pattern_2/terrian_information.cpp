#include <random>
#define WIDTH 10
#define HEIGHT 10
using namespace std;

class Texture{

};

Texture GRASS_TEXTURE;
Texture HILL_TEXTURE;
Texture RIVER_TEXTURE;

// 캡슐화를 위해서 지형 클래스를 따로 만들었다.
class Terrain {
public:
	Terrain(int movementCost, bool isWater, Texture texture)
		: movementCost_(movementCost),
		  isWater_(isWater),
		  texture_(texture) { }

	// 메모리를 줄이겠다고 메모리를 공유하도록 했는데 한 곳에서 바꾼 값이 여러 곳에서 동시에 나타나는 문제가 생길 수 있다
	// 이 문제로 경량 객체는 변경 불가능한 상태로 만드는 것이 일반적이다.
	// 때문에 읽기 전용 함수로 만들기 위해 const를 붙인다.
	int getMovementCost() const { return movementCost_; }
	bool isWater() const { return isWater_; }
	const Texture& getTextrue() const { return texture_; }

private:
	int movementCost_;
	bool isWater_;
	Texture texture_;
};

// 현재 Terrain 클래스에는 타일의 위치와 관련된 내용은 전혀 없다. 경량 패턴식으로 보면 모든 지형 상태는 고유하다.
// 즉 고유 상태(자유 문맥)에 해당한다.
// 따라서 지형 종류별로 Terrain 객체가 여러개 있을 필요가 없다.

// 지형에 들어가는 모든 풀밭 타일은 전부 동일하므로 
// World 클래스 격자 멤버 변수에 열거형이나 Terrain 객체 대신 Terrain 객체의 포인터를 넣을 수 있다.

// 아래는 이전과 멤버 변수가 달라진 World 객체이다.
/*
class World {
private:
	Terrain* tiles[WIDTH][HEIGHT];
};
*/
// 지형 종류가 같은 타일들은 모두 같은 Terrain 인스턴스 포인터를 갖는다.
// 풀밭이 필요한 만큼 생성한 것과는 다르게 풀밭 지형 정보가 저장된 주소를 사용하기 때문에(인스턴스 재사용)
// 메모리 사용량이 줄어드는 것이다.

// 그러나 위처럼 주소를 공유하면 Terrain 인스턴스가 여러 곳에서 사용되다 보니, 동적으로 할당하면 생명주기를 관리하기 어려워진다.
// 따라서 World 클래스에 저장한다. 

// World: 게임의 맵 전체를 나타내는 class로 WIDTH와, HEIGHT를 가진 타일의 그리드를 관리한다.
class World {
public:
	World() : grassTerrain_(1, false, GRASS_TEXTURE),
		hillTerrain_(3, false, HILL_TEXTURE),
		riverTerrain_(2, true, RIVER_TEXTURE) { }

	void generateTerrain();
	const Terrain& getTile(int, int)const;

private:
	// 각 타일은 특정 Terrain 객체를 참조한다. (어떤 타일이 풀밭이면 그 타일은 grassTerrain_ 인스턴스를 참조)
	Terrain* tiles[WIDTH][HEIGHT];

	// 아래 객체는 미리 생성되고 초기화 되며, World의 생명 주기동안 지속적으로 존재하며 모든 타일에서 공유된다.
	// 해당 객체들의 생명 주기를 World 클래스에 맞추어 관리하기 용이하도록 World 클래스 내에 Terrain 객체를 저장한다.
	// (World 객체가 생성될 때, 이 Terrain 객체들도 함께 생성되고, World 객체가 소멸될 때 함께 소멸)
	Terrain grassTerrain_;
	Terrain hillTerrain_;
	Terrain riverTerrain_;

};

// 멤버 함수로 아래와 같이 땅을 채울 수 있다.
void World::generateTerrain() {
	// 땅에 풀을 채움
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			// 언덕을 몇개 둔다.
			if (rand() % 10 == 0) {
				tiles[x][y] = &hillTerrain_;
			}
			else {
				tiles[x][y] = &grassTerrain_;
			}
		}
	}
	// 강을 놓는다.
	int x = rand() % WIDTH;
	for (int y = 0; y < HEIGHT; y++) {
		tiles[x][y] = &riverTerrain_;
	}
}

// 또한 지형 속성 값을 World의 메서드 대신에 Terrain 객체에서 바로 얻을 수 있다.
const Terrain& World::getTile(int x, int y)const {
	return *tiles[x][y];
}

// World 클래스는 더 이상 지형의 세부 정보와 커플링되지 않는다. 타일 속성은 Terrain 객체에서 바로 얻을 수 있기 때문이다.
int main() {
	World world;
	int cost = world.getTile(2, 3).getMovementCost();
}

/*
지형 데이터를 포인터로 접근한다는 것은 간접조회한다는 의미이다.
이동 비용같은 지형 데이터 값을 얻으려면 먼저 격자 데이터로부터 지형 객체 포인터를 얻은 후, 
포인터를 통해서 이동 비용 값을 얻어야 한다.
이렇게 포인터를 따라가면 캐시 미스가 발생할 수 있어 성능이 열거형보다는 조금 떨어질 수 있다.

그러나 객체가 메모리에 어떤 식으로 배치되느냐에 따라 달라진다. (경량패턴이 enum보다 빠른 경우도 있긴함)
*/

// 열거형을 선언해 수많은 다중 선택문을 만들 생각이라면 경량패턴을 먼저 고려해보자.