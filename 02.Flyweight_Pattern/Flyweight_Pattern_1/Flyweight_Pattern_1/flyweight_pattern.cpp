// �淮 ���� ���
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

struct Color {
	int R;
	int G;
	int B;
};

// ��� ������ �ٰ��� ����ϴ� �����͸� ����
class TreeModel {
	Mesh mesh;
	Texture bark;
	Texture leaves;
};

// �����ϰ� ����ϴ� �����͸� �ϳ��� ������ ��� �����Ѵ�.
class Tree {
public:
private:
	TreeModel Tree;

	// ������ ���� �ٸ� ���� ������ ������ ���� �������ش�.
	Vector position;
	double thickness;
	Color barkTint;
	Color leafTint;
};
