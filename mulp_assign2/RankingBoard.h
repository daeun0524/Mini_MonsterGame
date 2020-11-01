#ifndef __RANKING_BOARD_H__
#define __RANKING_BOARD_H__

#include<Windows.h>
#include <iostream>
#include <fstream>
#include "FileException.h"
using namespace std;
#define NUM_MVP 5 // �ִ� ��ŷ ��� ��

struct PlayInfo
{						// ���� ���� Ŭ����
	string name;		// ���̸��� �̸�
	int nItem;			// ȹ���� �������� ��
	double itemPerMove; // �̵� �Ÿ��� ������ ��
	PlayInfo(string na = "NewPlayer", int ni = 0, double ipm = 0.0) // ��� ����� ���� ����� �ʱ� ���� �Է�
		: name(na), nItem(ni), itemPerMove(ipm) {}
};

class RankingBoard
{ // ��ŷ ���� Ŭ����
	string filename;//���� �̸�
	PlayInfo MVP[NUM_MVP];
	int nMVP = NUM_MVP;

public:
	RankingBoard(string filename) : filename(filename)
	{}//filename �����ڷ� �޾ƿ�

	  // �־��� ������ �����͸� �о�´�. ������ ���� ��� ���� ó���� �Ѵ�.
	void load()
	{
		//ifstream is(filename);//���� �о����
		ifstream is(filename);
		int index = 0;
		char tmp[50], ttmp[50];

		if (is.is_open())//������ ���ȴ��� Ȯ��
		{
			//FileException(filename, true);
			while (!is.eof())
			{
				string str;
				getline(is, str);
				MVP[index].name = str;
				bool b = false;

				if (b == false)
				{
					is.getline(tmp, 30);
					sscanf_s(tmp, "%d", &MVP[index].nItem);
					b = true;
					bool c = false;

					if (c == false)
					{
						is.getline(ttmp, 30);
						sscanf_s(ttmp, "%lf", &MVP[index].itemPerMove);
						c = true;
					}
				}
				//�̸�, ������ ��, ���� �Ÿ��� ������ �� 
				index++;
			}
			is.close();
		}
		else//���� password = daeun
		{
			FileException e(filename, true);
			throw e;
		}
	}

	// ��ŷ ����Ʈ�� �����Ѵ�.
	void store()//store�� �� �ϴµ�
	{
		ofstream os;//���� ����
		os.open(filename);
		for (int i = 0; i < 5; i++)
		{
			string s_nItem = to_string(MVP[i].nItem);
			string s_itemPerMove = to_string(MVP[i].itemPerMove);

			os.write(MVP[i].name.c_str(), MVP[i].name.size());
			os << endl;
			os.write(s_nItem.c_str(), s_nItem.size());
			os << endl;
			os.write(s_itemPerMove.c_str(), s_itemPerMove.size());
			os << endl;
		}
		os.close();
	}


	void swap(PlayInfo *first, PlayInfo *second)
	{
		PlayInfo temp;

		temp = *first;
		*first = *second;
		*second = temp;
	}

	// ��ŷ ����Ʈ�� 1������ ������� ����Ѵ�.
	void print(string title = "Game Ranking")
	{
		cout << title << endl;
		for (int i = 0; i < NUM_MVP; i++)//��� ������ ����
		{
			for (int j = i; j < NUM_MVP; j++)
			{
				if (MVP[i].nItem < MVP[j].nItem)
				{
					swap(&MVP[i], &MVP[j]);
				}
			}
		}
		cout << endl;

		for (int i = 0; i < 5; i++)
		{
			cout << " [Rank " << i + 1 << "] " << MVP[i].name << "\t\t" << MVP[i].nItem << "\t\t" << MVP[i].itemPerMove << endl;
		}

		cout << endl
			<< " Press [ENTER] key...";
		getchar();
		cout << endl;
	}

	// ������ ���� �� �÷��̾��� ����� �Է��Ѵ�.
	// nItem : ������ ȹ�� ��, ipm : �̵��Ÿ��� ������ ȹ�� ���� (������ ȹ�� �� / �� �̵� �Ÿ�)
	// �Է½� ���� ��ϰ� ���Ͽ� 5�� �̳��� ��� ����� ���� �̸��� �޴´�.
	void add(int nItem, double ipm)
	{
		int index;
		cout << endl;

		if (nItem > MVP[4].nItem&& nItem != 1)//5�� �̳��� ���
		{
			MVP[4].nItem = nItem;//�÷��̾��� ���� �Է�
			MVP[4].itemPerMove = ipm;

			for (int i = 0; i < NUM_MVP; i++)//��� ������ ����
			{
				for (int j = i; j < NUM_MVP; j++)
				{
					if (MVP[i].nItem < MVP[j].nItem)
					{
						swap(&MVP[i], &MVP[j]);
					}
				}
			}

			for (int i = 0; i < 5; i++)
			{

				if (MVP[i].nItem == nItem && MVP[i].itemPerMove == ipm)
				{
					index = i;
				}
			}

			cout << "[Rank " << index + 1 << "]" << " Instert Name:";
			cin >> MVP[index].name;//�÷��̾� ��� MVP�� ����		

			cout << endl;
		}
	}
};

#endif