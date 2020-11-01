#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
#include <cmath>
using namespace std;

class Point
{
	int x, y;			  //  ���� x�� y ��ǥ ��
	friend class Monster; //  Monster�� ģ�� Ŭ������ ���
	friend class Canvas;  //  Canvas�� ģ�� Ŭ������ ���
public:
	Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
	int &operator[](int id)
	{ // �ε��� ������
		if (id == 0)
			return x;
		else if (id == 1)
			return y;
		else
			exit(0);
	}

	// sqrt�� �������� ���Ѵ�. �Ÿ��� ���Ҷ� ����ϸ� ���� �� ����.
	operator double() { return sqrt((double)x * x + y * y); }

	// Point �� ���� 0���� �۰ų� �ִ밪�� ���� �ʵ��� ���ִ� () ������
	void operator()(int maxx, int maxy)
	{
		if (x < 0)
			x = 0;
		if (x >= maxx)
			x = maxx - 1;
		if (y < 0)
			y = 0;
		if (y >= maxy)
			y = maxy - 1;
	}
	Point operator-() { return Point(-x, -y); }
	bool operator==(const Point &p) { return x == p.x && y == p.y; }
	bool operator!=(const Point &p) { return x != p.x || y != p.y; }
	Point operator-(const Point &p) { return Point(x - p.x, y - p.y); }
	Point operator+(const Point &p) { return Point(x + p.x, y + p.y); }
	void operator+=(const Point &p) { x += p.x, y += p.y; }
	void operator-=(const Point &p) { x -= p.x, y -= p.y; }
};

#endif