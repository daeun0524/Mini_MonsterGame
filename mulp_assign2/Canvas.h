#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <iostream>
#include <string>
#include "Point.h" // Point ����� ���� �߰�
#include <vector>
using namespace std;

#ifdef _WIN32
const char *COMMAND = "cls";
#else
const char *COMMAND = "clear";
#endif

// ȭ���� ��� �ϱ� �� �޸� Canvas
class Canvas
{
	vector<string> line; // ȭ�� ����� ���� ���� ��ü
	int xMax, yMax;

public:
	// ȭ���� ũ�⸦ �����ϰ� �������� �ʱ�ȭ �Ѵ�.
	Canvas(int nx = 10, int ny = 10) : line(ny), xMax(nx), yMax(ny)
	{
		for (int y = 0; y < yMax; y++)
			line[y] = string(xMax, ' ');
	}

	// �־��� x, y ��ǥ�� val �� �׷��ش�
	void draw(int x, int y, string val)
	{
		if (x >= 0 && y >= 0 && x < xMax && y < yMax)
			line[y].replace(x, 1, val);
	}

	// �־��� Point ��ǥ�� val �� �׷��ش�
	void draw(Point &p, string val) { draw(p.x, p.y, val); }

	// Canvas ��ü�� �������� �ʱ�ȭ ���ش� (Canvas�� �׷��� �׸��� �����)
	void clear(string val = " ")
	{
		for (int y = 0; y < yMax; y++)
			for (int x = 0; x < xMax; x++)
				draw(x, y, val);
	}

	// ���� ȭ���� ����� title �� �Բ� ���� Canvas �� ȭ�鿡 ����Ѵ�
	void print(const char *title = "<My Canvas>")
	{
		system(COMMAND);
		cout << title << endl;
		for (int y = 0; y < yMax; y++)
			cout << line[y] << endl;
		cout << endl;
	}
};

#endif