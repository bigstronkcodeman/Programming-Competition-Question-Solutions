// Stack 'em Up
#include <iostream>
#include <string>
#include <vector>

#define NUMSUITS 4
#define NUMVALS 13
#define NUMCARDS 52

using namespace std;

string suits[NUMSUITS] = { "Clubs", "Diamonds", "Hearts", "Spades" };
string vals[NUMVALS] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
string deck[NUMCARDS];

void initDeck()
{
	for (int i = 0; i < NUMSUITS; i++)
	{
		for (int j = 0; j < NUMVALS; j++)
		{
			deck[(i * NUMVALS) + j] = vals[j] + " of " + suits[i];
		}
	}
}

void printDeck()
{
	for (int i = 0; i < NUMCARDS; i++)
	{
		cout << deck[i] << endl;
	}
}

void applyShuffle(vector<int>& shuffle)
{
	string deck2[NUMCARDS];
	copy(deck, deck + NUMCARDS, deck2);

	for (int i = 0; i < shuffle.size(); i++)
	{
		deck[i] = deck2[shuffle[i] - 1];
	}
}

int main()
{
	string line;

	getline(cin, line);
	int T = stoi(line);

	vector<vector<vector<int>>> instances;
	getline(cin, line);
	for (int i = 0; i < T; i++)
	{
		getline(cin, line);
		int n = stoi(line);

		vector<vector<int>> shuffles;
		for (int j = 0; j < n; j++)
		{
			vector<int> shuffle;
			for (int k = 0; k < NUMCARDS; k++)
			{
				int card;
				cin >> card;
				shuffle.push_back(card);
			}
			if (j == n - 1)
				int x = 5;
			shuffles.push_back(shuffle);
		}

		getline(cin, line);

		vector<vector<int>> orderedShuffles;
		while (getline(cin, line) && !line.empty())
		{
			orderedShuffles.push_back(shuffles[stoi(line) - 1]);
		}

		instances.push_back(orderedShuffles);
	}

	for (int i = 0; i < instances.size(); i++)
	{
		initDeck();
		for (int j = 0; j < instances[i].size(); j++)
		{
			applyShuffle(instances[i][j]);
		}
		printDeck();
		if (i != instances.size() - 1)
		{
			cout << endl;
		}
	}

	return 0;
}
