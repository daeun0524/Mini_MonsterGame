#ifndef __VARIOUS_MONSTERS_H__
#define __VARIOUS_MONSTERS_H__

#include "Monster.h"

/*
* ��� ���ʹ� �̵� ��� ���̿� �����ϴ� �������� ȹ�� �� �� ����.
* ���� �ڽ��� �� �Ͽ� ���������� ������ ��ġ�� �����۸� ȹ�� �� �� �ִ�.
*/

// ������ �⺻ �̵� ������ ������. (9���� ����� �� �̵�)
class Zombie : public Monster
{
public:
	Zombie(string n = "Zombie", string i = "Z", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Zombie()
	{
		cout << " Zombie";
	}
};

// ���� �Ǵ� ���ηθ� �̵� �Ѵ� (4���� ����� �� �̵�)
class Vampire : public Monster
{
public:
	int x1, y1, x2, y2;//x1,y1:����
	Vampire(string n = "Vampire", string i = "V", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(vector<vector<int> > &map, int maxx, int maxy)
	{
		x1 = p.operator[](0);//�̵� ��
		y1 = p.operator[](1);

		while (nSleep > 0)
		{
			x1 = x1;
			y1 = y1;
			nSleep -= 1;
			dist = 0;
			return;
		}
		int n = 1 + (rand() % 4);
		x2 = x1;
		y2 = y1;

		switch (n)//1���� 9���� ���� ����
		{
		case 1:
			x2 += 1;
			break;
		case 2:
			y2 += 1;
			break;
		case 3:
			y2 -= 1;
			break;
		case 4:
			x2 -= 1;
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
			eat(map);
		}
		else
		{
			eat(map);
		}
		q.operator[](0) = x1;
		q.operator[](1) = y1;
		//�̵� �� ��ġ �Ѱ��ֱ�
		p.operator[](0) = x2;
		p.operator[](1) = y2;
	}
};

// �����̵��� �� �� �ִ�. �� �̵��� ���� ȭ�� ���� ������ �� �������� �̵� �Ѵ�. (���ڸ� ����)
class KGhost : public Monster
{
public:
	int x1, y1, x2, y2;
	KGhost(string n = "KGhost", string i = "G", int x = 0, int y = 0)
		: Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(vector<vector<int> > &map, int maxx, int maxy)
	{
		x1 = p.operator[](0);
		y1 = p.operator[](1);
		while (nSleep > 0)
		{
			x1 = x1;
			y1 = y1;
			nSleep -= 1;
			dist = 0;
			return;
		}
		x2 = x1;
		y2 = y1;

		x2 = rand() % 32;
		y2 = rand() % 10;


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
			eat(map);
		}
		else
		{
			eat(map);
		}
		q.operator[](0) = x1;
		q.operator[](1) = y1;
		p.operator[](0) = x2;
		p.operator[](1) = y2;
	}
};

// ���� �Ǵ� ���� �������θ� �̵� �� �� �ִ�.
// �� ĭ �Ǵ� �� ĭ�� �̵� �� �� �ִ�. (���ڸ��� �ӹ��� ���� ����.)
class Jiangshi : public Monster
{
	bool bHori;

public:
	int x1, y1, x2, y2;
	// bHori�� horizontal �̵� �����̴�.
	// �� ���� true �̸� ���ι������θ�, false �̸� ���ι������θ� �̵� �� �� �ִ�.
	Jiangshi(string n = "Jiangshi", string i = "J", int x = 0, int y = 0, bool bH = true)
		: Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(vector<vector<int> > &map, int maxx, int maxy)
	{
		while (nSleep > 0)
		{
			x1 = x1;
			y1 = y1;
			nSleep -= 1;
			dist = 0;
			return;
		}
		x1 = p.operator[](0);
		y1 = p.operator[](1);
		x2 = x1;
		y2 = y1;

		int n = 1 + (rand() % 4);
		if (bHori == true)//���ηθ�
		{

			switch (n)//1���� 9���� ���� ����
			{
			case 1:
				x2 += 1;
				break;
			case 2:
				x2 += 2;
				break;
			case 3:
				x2 -= 1;
				break;
			case 4:
				x2 -= 2;
				break;
			}
		}
		else if (bHori == false)//���ηθ�
		{
			switch (n)//1���� 9���� ���� ����
			{
			case 1:
				y2 += 1;
				break;
			case 2:
				y2 += 2;
				break;
			case 3:
				y2 -= 1;
				break;
			case 4:
				y2 -= 2;
				break;
			}
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
			eat(map);
		}
		else
		{
			eat(map);
		}
		q.operator[](0) = x1;
		q.operator[](1) = y1;
		p.operator[](0) = x2;
		p.operator[](1) = y2;
	}
};

#endif