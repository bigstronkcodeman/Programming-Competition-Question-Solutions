// Minesweeper

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printField(vector<vector<int>> in)
{
	for (int i = 0; i < in.size(); i++)
	{
		for (int j = 0; j < in[i].size(); j++)
		{
			if (in[i][j] >= 0)
			{
				cout << in[i][j];
			}
			else
			{
				cout << "*";
			}
		}
		if (i < in.size() - 1) cout << "\n";
	}
}

int main()
{
	vector<vector<vector<int>>> minefields;

	int i;
	int j;
	int currField = 0;
	while (cin >> i >> j)
	{
		cin.ignore();
		vector<vector<int>> field(i);
		for (int k = 0; k < i; k++)
		{
			field[k] = vector<int>(j);
		}
		minefields.push_back(field);
		for (int k = 0; k < i; k++)
		{
			string inp;
			getline(cin, inp);
			for (int l = 0; l < inp.size(); l++)
			{
				char c = inp[l];

				if (c == '*')
				{
					minefields[currField][k][l] -= 10;
					if (k - 1 >= 0)
					{
						if (l - 1 >= 0)
						{
							minefields[currField][k - 1][l - 1]++;
						}

						if (l + 1 < j)
						{
							minefields[currField][k - 1][l + 1]++;
						}

						minefields[currField][k - 1][l]++;
					}
					if (k + 1 < i)
					{
						if (l - 1 >= 0)
						{
							minefields[currField][k + 1][l - 1]++;
						}

						if (l + 1 < j)
						{
							minefields[currField][k + 1][l + 1]++;
						}

						minefields[currField][k + 1][l]++;
					}
					if (l - 1 >= 0)
					{
						minefields[currField][k][l - 1]++;
					}
					if (l + 1 < j)
					{
						minefields[currField][k][l + 1]++;
					}
				}
			}
		}
		currField++;
	}

	for (int i = 0; i < minefields.size(); i++)
	{
		if (i == 0)
		{
			cout << "Field #" << i + 1 << ":\n";
		}
		else if (minefields[i].size() > 0)
		{
			cout << "\nField #" << i + 1 << ":\n";
		}

		printField(minefields[i]);

		if (minefields[i].size() > 0)
		{
			cout << "\n";
		}
	}

	return 0;
}