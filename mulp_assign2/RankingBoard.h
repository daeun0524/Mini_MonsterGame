#ifndef __RANKING_BOARD_H__
#define __RANKING_BOARD_H__

#include<Windows.h>
#include <iostream>
#include <fstream>
#include "FileException.h"
using namespace std;
#define NUM_MVP 5 // 최대 랭킹 기록 수

struct PlayInfo
{						// 게임 정보 클래스
	string name;		// 게이머의 이름
	int nItem;			// 획득한 아이템의 수
	double itemPerMove; // 이동 거리당 아이템 수
	PlayInfo(string na = "NewPlayer", int ni = 0, double ipm = 0.0) // 등록 기록이 없을 경우의 초기 값을 입력
		: name(na), nItem(ni), itemPerMove(ipm) {}
};

class RankingBoard
{ // 랭킹 관리 클래스
	string filename;//파일 이름
	PlayInfo MVP[NUM_MVP];
	int nMVP = NUM_MVP;

public:
	RankingBoard(string filename) : filename(filename)
	{}//filename 생성자로 받아옴

	  // 주어진 파일의 데이터를 읽어온다. 파일이 없는 경우 예외 처리를 한다.
	void load()
	{
		//ifstream is(filename);//파일 읽어오기
		ifstream is(filename);
		int index = 0;
		char tmp[50], ttmp[50];

		if (is.is_open())//파일이 열렸는지 확인
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
				//이름, 아이템 수, 단위 거리당 아이템 수 
				index++;
			}
			is.close();
		}
		else//생성 password = daeun
		{
			FileException e(filename, true);
			throw e;
		}
	}

	// 랭킹 리스트를 저장한다.
	void store()//store는 잘 하는듯
	{
		ofstream os;//파일 쓰기
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

	// 랭킹 리스트를 1위부터 순서대로 출력한다.
	void print(string title = "Game Ranking")
	{
		cout << title << endl;
		for (int i = 0; i < NUM_MVP; i++)//기록 순으로 정렬
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

	// 게임이 끝난 후 플레이어의 기록을 입력한다.
	// nItem : 아이템 획득 수, ipm : 이동거리당 아이템 획득 비율 (아이템 획득 수 / 총 이동 거리)
	// 입력시 현재 기록과 비교하여 5위 이내인 경우 기록을 위한 이름을 받는다.
	void add(int nItem, double ipm)
	{
		int index;
		cout << endl;

		if (nItem > MVP[4].nItem&& nItem != 1)//5위 이내인 경우
		{
			MVP[4].nItem = nItem;//플레이어의 정보 입력
			MVP[4].itemPerMove = ipm;

			for (int i = 0; i < NUM_MVP; i++)//기록 순으로 정렬
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
			cin >> MVP[index].name;//플레이어 기록 MVP에 저장		

			cout << endl;
		}
	}
};

#endif