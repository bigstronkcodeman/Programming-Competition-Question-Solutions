//The 3n+1 problem

#include <iostream>
#include <vector>
#include <chrono>

#define SIZE 1000000

using namespace std;

int store[SIZE];

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

int sequence(int n)
{
	if (n < SIZE && store[n] != 0)
	{
		return store[n];
	}

	long long int _n = n;
	int count = 1;

	while (_n != 1)
	{
		if (_n % 2 == 0)
		{
			_n /= 2;
		}
		else
		{
			_n = (3 * _n) + 1;
		}

		if (_n < SIZE && store[_n] != 0)
		{
			count += store[_n];
			break;
		}
		else
		{
			count++;
		}
	}

	if (n < SIZE)
	{
		store[n] = count;
	}

	return count;
}

int maxSequenceCycle(int i, int j)
{
	int max = 0;
	for (int k = i; k <= j; k++)
	{
		int cycleLength = sequence(k);
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
		cout << a << " " << b << " " << maxSequenceCycle(data[i][0], data[i][1]) << endl;
	}

	return 0;
}
