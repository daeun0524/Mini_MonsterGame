#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "Monster.h"

// hint (_getch(), _kbhit()) �Լ��� ������ �ִ� �������
#ifdef _WIN32
#include <conio.h>
#else
#include "Keyboard.h"
#endif

enum Direction
{
	Left = 97,    // a
	Right = 100,  // d
	Up = 119,     // w
	Down = 115    // s
};

// ����ڰ� ���� �� �� �ִ� Player
class Human : public Monster
{
public:
	Human(string n = "Player", string i = "H", int px = 0, int py = 0)
		: Monster(n, i, px, py) {}
	~Human() { cout << " Player"; }

	char getKey()
	{
		if (_kbhit())
		{
			return _getch();
		}
		return '\0';
	}

	// Ű���� �Է��� �ִ��� �����Ͽ� ����ڸ� �������ش�. �÷��̾��� ��쿡�� �����ʰ� ��� ������ �� �ִ�.
	void move(vector<vector<int> > &map, int maxx, int maxy)
	{
		int x1, y1, x2, y2;//x1,y1: ���� ��ġ
		x1 = p.operator[](0);
		y1 = p.operator[](1);

		char cselect = '\0';
		cselect = getKey();

		x2 = x1;//�̵� �� ��ġ
		y2 = y1;

		switch (cselect)
		{
		case Left:
			x2 -= 1;
			break;
		case Right:
			x2 += 1;
			break;
		case Up:
			y2 -= 1;
			break;
		case Down:
			y2 += 1;
			break;
		}

		if (x2 >= maxx || y2 >= maxy || x2 < 0 || y2 < 0)
		{
			if (x2 < 0)
				x2 = 0;
			if (x2 >= maxx)
				x2 = maxx - 1;
			if (y2 < 0)
				y2 = 0;
			if (y2 >= maxy)
				y2 = maxy - 1;
			eat(map, false);
		}
		else
		{
			eat(map, false);
		}
		q.operator[](0) = x1;
		q.operator[](1) = y1;

		p.operator[](0) = x2;
		p.operator[](1) = y2;
	}
};

#endif