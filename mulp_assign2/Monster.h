#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Canvas.h"
#include "Point.h"
#include <ctime>

class Monster
{
public:
	string name, icon; // ���� �̸��� ȭ�� ��¿� ������
	int nItem;         // ���� ������ ��
	Point q, p;        // ���� ��ġ(q)�� ���� ��ġ(p)
	int nSleep;        // ����� �ϴ� Ƚ��
	double dist;       // ���� �� ���� ������ �Ÿ�
	double total;      // �� ������ �Ÿ�

					   // �̵��� ȭ���� ����� ��� �̵� ó���� �����ش�
					   // hint : Point�� () �����ڰ� �����Ѵ�
	void clip(int maxx, int maxy)
	{
		p.operator()(maxx, maxy);
	}

	double distance(Point &p1, Point &p2)
	{
		double d;
		d = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
		return d;
	}
	// �ڽ��� ��ġ�� �������� �ִ°�� ������ �� �� ����.
	// ������ ��ǥ�� �ִ� ���� 1�ΰ�� ������ ����, 0 �ΰ�� �����̴�.
	// �̰����� ������ ȹ�� ���ο� �Ÿ� ���, �޽� ���θ� �����Ѵ�.
	// �÷��̾��� ��� �޽��� ���� �ʴ´�.
	void eat(vector<vector<int> > &map, bool isMonster = true)//world�� ���� ����
	{
		total += distance(p, q);
		dist += distance(p, q);

		if (map[p.y][p.x] == 1)//������ ����
		{
			map[p.y][p.x] = 0;
			nItem++;
		}

		if (isMonster == true && dist > 20)//�����̰� dist�� 20�̸�
		{
			nSleep = 10;
		}
	}

public:
	Monster(string n = "Monster", string i = "M", int x = 0, int y = 0)
		: name(n), icon(i), nItem(0),
		p(x, y), q(x, y), nSleep(0), dist(0.0), total(0.0)
	{}
	virtual ~Monster() {
		cout << " " << icon << "\t"
			<< "Item:" << nItem << "\t\t"
			<< "Distance:" << total << endl;
	}

	void draw(Canvas &canvas) { canvas.draw(p, icon); }

	// ������ ���� �Ÿ��� 20 �̻� �̵��ϰ� ���� 10���� �̵��� ���� ����� �Ѵ�.
	// ���ʹ� �� �̵� �� ���� �밢��, ����, ����, ���ڸ� �̷��� �� 9���� �̵��� �Ѱ��� �̵��� �ϴ� ���� �⺻ �������� �Ѵ�.
	// �⺻ ������ �̵� �Ÿ��� ���ϴ� �ִ� 1ĭ�̴�.
	virtual void move(vector<vector<int> > &map, int maxx, int maxy)
	{
		while (nSleep > 0)
		{
			p.x = q.x;
			p.y = q.y;
			nSleep -= 1;
			dist = 0;
			return;
		}
		int n = 1 + (rand() % 9);
		q.x = p.x;//������ �̵��� ��ġ �޾ƿ���
		q.y = p.y;
		switch (n)//1���� 9���� ���� ����
		{
		case 1:
			p.x += 1;
			break;
		case 2:
			p.y += 1;
			break;
		case 3:
			p.x += 1;
			p.y += 1;
			break;
		case 4:
			p.x -= 1;
			break;
		case 5:
			p.y -= 1;
			break;
		case 6:
			p.x -= 1;
			p.y -= 1;
			break;
		case 7:
			p.x += 1;
			p.y -= 1;
			break;
		case 8:
			p.x -= 1;
			p.y += 1;
			break;
		case 9://���ڸ�
			p.x = p.x;
			p.y = p.y;
			break;
		}
		if (p.x >= maxx || p.y >= maxy || p.x < 0 || p.y < 0)
		{
			clip(maxx, maxy);
			eat(map);
		}
		else
		{
			eat(map);
		}
	}
	void print() { cout << "\t" << name << " " << icon << "\t" << nItem << "\t" << nSleep << endl; }
};

#endif