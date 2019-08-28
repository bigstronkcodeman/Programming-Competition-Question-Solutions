//The 3n+1 problem

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<vector<int>> getInput()
{
	vector<vector<int>> din;
	int i;
	int j;
	int index = 0;
	while (cin >> i >> j)
	{
		din.push_back(vector<int>());
		din[index].push_back(i);
		din[index].push_back(j);
		index++;
	}
	return din;
}

int sequence(int n, unordered_map<int, int>& savedResults)
{
	if (savedResults.find(n) != savedResults.end())
	{
		return savedResults[n] + (n != 1);
	}
	else
	{
		int count;
		if (n == 1)
		{
			count = 1;
			savedResults[n] = count;
			return count;
		}
		else if (n % 2 == 0)
		{
			count = sequence(n / 2, savedResults);
			savedResults[n] = count;
			return count + 1;
		}
		else
		{
			count = sequence((3 * n) + 1, savedResults);
			savedResults[n] = count;
			return count + 1;
		}
	}
}

int maxSequenceCycle(int i, int j, unordered_map<int, int>& savedResults)
{
	int max = 0;
	for (int k = i; k <= j; k++)
	{
		int cycleLength = sequence(k, savedResults);
		if (cycleLength > max)
		{
			max = cycleLength;
		}
	}
	return max;
}

int main()
{
	vector<vector<int>> data = getInput();
	unordered_map<int, int> savedResults;

	for (int i = 0; i < data.size(); i++)
	{
		int a = data[i][0];
		int b = data[i][1];
		if (data[i][0] > data[i][1])
		{
			int temp = data[i][0];
			data[i][0] = data[i][1];
			data[i][1] = temp;
		}
		cout << a << " " << b << " " << maxSequenceCycle(data[i][0], data[i][1], savedResults) << endl;
	}

	return 0;
}
