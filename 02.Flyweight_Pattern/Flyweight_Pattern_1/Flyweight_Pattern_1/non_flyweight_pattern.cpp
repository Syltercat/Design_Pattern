// �淮 ������ ���� �ʴ� ����
#include <map>
using namespace std;
#define Vector map<int,int>
#define HEIGHT 100
#define WIDTH 100

class Mesh {
	// ǥ���̳� �ָ��� ������ ��Ÿ���� �簢���� �ﰢ���� ����
};

class Texture {
	// �������� ������ ǥ���ϰų� ���� ĥ�ϴ� ��� (�ؽ��� ����)
};

struct Color{
	int R;
	int G;
	int B;
};

// ������ �Ʒ�ó�� �ѱ׷��� ���� Ŭ������ ���� �� ���� ������ �Ѵ�.
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