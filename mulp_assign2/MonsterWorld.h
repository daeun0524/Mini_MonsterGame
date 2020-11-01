#ifndef __WORLD_H__
#define __WORLD_H__

#include "Canvas.h"
#include "VariousMonsters.h"
#include "Human.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <algorithm> // STL�� �˰��� ���
inline bool compare(Monster *first, Monster *second)
{
	return first->nItem > second->nItem;
}

class MonsterWorld
{
	vector<vector<int> > world;
	int xMax, yMax, nMove;
	vector<Monster *> pMon;
	Canvas canvas;

	int &Map(int x, int y) { return world[y][x]; }
	bool isDone() { return countItems() == 0; }
	int countItems()
	{
		int nItems = 0;
		for (int y = 0; y < yMax; y++)
			nItems += count(world[y].begin(), world[y].end(), 1);
		return nItems;
	}
	void print()
	{
		canvas.clear();
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				if (Map(x, y) > 0)
					canvas.draw(x, y, ".");
		for (int i = 0; i < pMon.size(); i++)
			pMon[i]->draw(canvas);
		canvas.print("[ Monster World ]");

		cerr << " Total Move Count = " << nMove << endl;
		cerr << " Rest Items Count = " << countItems() << endl
			<< endl;

		// ���͵��� ������ ȹ�� ���ڿ� ���� ���� �ȴ�.
		sort(pMon.begin(), pMon.end(), compare);
		for (int i = 0; i < pMon.size(); i++)
		{
			cout << "  Rank " << i + 1;
			pMon[i]->print();
		}
	}

public:
	// ������ �ʱ�ȭ �Ѵ�. ������ ��� ĭ�� �������� �����ϴ�.
	// ������ ���� 1�̸� �������� �ְ� 0 �̸� �������� ���ٴ� �� �̴�.
	MonsterWorld(int w, int h) : world(h), canvas(w, h), xMax(w), yMax(h)
	{
		nMove = 0;
		for (int y = 0; y < yMax; y++)
		{
			world[y] = vector<int>(w, 1);
		}
	}
	// �߰� �� ��� ���� (�ΰ� ����)�� �޸𸮸� �����Ѵ�.
	~MonsterWorld()
	{
		for (int i = 0; i < pMon.size(); i++)
			delete pMon[i];
	}
	void add(Monster *m)
	{
		pMon.push_back(m);
	}

	// ������ �÷��� �Ѵ�. �������� ��� �������� �������ų�, �ִ� �̵� Ƚ���� ������ ���� ������ ���� �ȴ�.
	void play(int maxwalk, int wait)
	{
		print();
		cerr << endl
			<< " Press [ENTER] key...";
		getchar();
		// ���͵��� �� �̵��ϸ��� �̵��� �����Ѵ�.
		// ���� �� ������� �̵��� �ϰ� �̵� �� ������ �������� ȹ���Ѵ�.
		// ������ ȹ�� ���� ���� �ᱹ �� ��ġ�� ���� ���Ͱ� ���� �ϴ��� ������ ���� ���Ͱ� �������� ȹ���ϰ� �ȴ�.
		for (int i = 0; i < maxwalk; i++)
		{
			for (int k = 0; k < pMon.size(); k++)
				pMon[k]->move(world, xMax, yMax);

			nMove++;
			print();
			if (isDone())
				break;

			// ������� ���α׷� ȯ�濡 ���� ������ sleep ����� ȣ���մϴ�.
			// ���� �ֱ�� �� �̵� ���� ī��Ʈ �ϱ� ���� �����̴�.
#ifdef _WIN32
			Sleep(wait);
#else
			usleep(wait);
#endif
		}
	}
};

#endif