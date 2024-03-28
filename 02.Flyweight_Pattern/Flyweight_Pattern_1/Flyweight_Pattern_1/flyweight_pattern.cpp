// 경량 패턴 사용
#include <map>
using namespace std;
#define Vector map<int,int>
#define HEIGHT 100
#define WIDTH 100

class Mesh {
	// 표면이나 솔리드 형상을 나타내는 사각형과 삼각형의 모음
};

class Texture {
	// 세부적인 질감을 표현하거나 색을 칠하는 기법 (텍스쳐 맵핑)
};

struct Color {
	int R;
	int G;
	int B;
};

// 모든 나무가 다같이 사용하는 데이터를 뽑음
class TreeModel {
	Mesh mesh;
	Texture bark;
	Texture leaves;
};

// 동일하게 사용하는 데이터를 하나의 변수로 묶어서 선언한다.
class Tree {
public:
private:
	TreeModel Tree;

	// 데이터 별로 다른 값을 가지는 변수는 따로 선언해준다.
	Vector position;
	double thickness;
	Color barkTint;
	Color leafTint;
};
