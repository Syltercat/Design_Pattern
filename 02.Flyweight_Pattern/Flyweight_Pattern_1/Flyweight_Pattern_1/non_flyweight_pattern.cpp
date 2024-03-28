// 경량 패턴을 쓰지 않는 예제
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

struct Color{
	int R;
	int G;
	int B;
};

// 원래는 아래처럼 한그루의 나무 클래스를 만든 후 숲을 만들어야 한다.
class Tree {
public:
private:
	Mesh mesh;
	Texture bark;
	Texture leaves;
	Vector position;
	double thickness;
	Color barkTint;
	Color leafTint;
};

int main() {
	Tree forest[HEIGHT][WIDTH];
 }