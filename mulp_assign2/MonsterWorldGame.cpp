#include "MonsterWorld.h"
#include "Human.h"
#include "RankingBoard.h"
#include <time.h>

// ��ŷ ������ ������ �ҷ��´�.
void initRankingBoard(RankingBoard &rank)
{
	try
	{
		cout << "Loading Ranking Board..." << endl;
		rank.load();
	}
	catch (FileException e)
	{
		string passwd, correct = "daeun";
		cout << "Password: ";
		cin >> passwd;

		if (passwd != correct)
		{
			cout << "Incorrect password. Quit game.\n\n";
			exit(0);
		}
		// ��� ��ȣ�� ������ �⺻ ��ŷ���� ������ ��� ������.
	}
	rank.print("[Game Ranking: START]");
}

// ������ ���� ��ġ�� ���Ϳ� �÷��̾ ��ġ�Ѵ�.
Human *initGame(MonsterWorld &game, int width, int height)
{
	srand((unsigned int)time(NULL));

	game.add(new Zombie("Zombie", "Z", rand() % width, rand() % height));
	game.add(new Vampire("Vampire", "V", rand() % width, rand() % height));
	game.add(new KGhost("KGhost", "G", rand() % width, rand() % height));
	game.add(new Jiangshi("Jiangshi1", "A", rand() % width, rand() % height, true));
	game.add(new Jiangshi("Jiangshi2", "B", rand() % width, rand() % height, false));

	Human *human = new Human("Player", "H", rand() % width, rand() % height);
	game.add(human);
	return human;
}

// ������ ���� �� �� ��ŷ ���� ���� �� ������ ���� �Ѵ�.
void handleScore(RankingBoard &rank, Human *human)
{
	rank.add(human->nItem, human->nItem / human->total);
	rank.print("[Game Ranking: FINISH]");
	rank.store();
}

int main()
{
	RankingBoard rank("MonsterWorld.rnk");
	initRankingBoard(rank);

	int width = 32, height = 10;
	MonsterWorld game(width, height);
	Human *human = initGame(game, width, height);

#ifndef _WIN32
	init_keyboard();
#endif
	game.play(500, 10);
#ifndef _WIN32
	close_keyboard();
#endif
	printf("\n------------------- Game Finish -------------------\n");

	handleScore(rank, human);

	return 0;
}