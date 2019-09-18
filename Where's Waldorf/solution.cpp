// Where's Waldorf
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

using namespace std;

bool inBounds(int rows, int cols, int i, int j)
{
	return (i >= 0 && j >= 0) && (i < rows && j < cols);
}

array<int, 2> search(vector<string> ws, string word)
{
	for (int i = 0; i < ws.size(); i++)
	{
		for (int j = 0; j < ws[i].size(); j++)
		{
			if (ws[i][j] == word[0])
			{
				if (word.length() == 1)
				{
					return { i + 1, j + 1 };
				}

				for (int k = -1; k <= 1; k++)
				{
					for (int l = -1; l <= 1; l++)
					{
						if (k != 0 || l != 0);
						{
							int m = i + k;
							int n = j + l;
							int wordi = 1;
							while (inBounds(ws.size(), ws[i].size(), m, n) && ws[m][n] == word[wordi])
							{
								if (wordi == word.length() - 1)
								{
									return { i + 1, j + 1 };
								}
								m += k;
								n += l;
								wordi++;
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	vector<vector<string>> instances;
	vector<vector<string>> searchList;
	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		string line;
		getline(cin, line);

		int m, n;
		cin >> m >> n;

		vector<string> ws;
		ws.reserve(m);

		for (int j = 0; j < m; j++)
		{
			cin >> line;
			transform(line.begin(), line.end(), line.begin(), ::toupper);
			ws.push_back(line);
		}

		instances.push_back(ws);

		int k;
		cin >> k;

		vector<string> search;
		search.reserve(k);

		for (int j = 0; j < k; j++)
		{
			cin >> line;
			transform(line.begin(), line.end(), line.begin(), ::toupper);
			search.push_back(line);
		}

		searchList.push_back(search);
	}

	for (int i = 0; i < instances.size(); i++)
	{
		for (int j = 0; j < searchList[i].size(); j++)
		{
			array<int, 2> wordIndices = search(instances[i], searchList[i][j]);
			cout << wordIndices[0] << " " << wordIndices[1] << endl;
		}
		cout << (i != instances.size() - 1 ? "\n" : "");
	}

	return 0;
}
