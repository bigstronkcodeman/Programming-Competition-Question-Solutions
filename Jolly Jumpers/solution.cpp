// Jolly Jumpers
#include <iostream>
#include <vector>

using namespace std;

int absolute(int a)
{
	return a < 0 ? -a : a;
}

int sumNaturals(int upto)
{
	return (upto * (upto + 1)) / 2;
}

bool isJolly(vector<int> sequence)
{
	int diffSum = 0;
	for (int i = 0; i < sequence.size() - 1; i++)
	{
		int diff = absolute(sequence[i] - sequence[i + 1]);
		diffSum += diff;
		if (diff == 0)
		{
			return false;
		}
	}

	if (diffSum == sumNaturals(sequence.size() - 1))
	{
		return true;
	}
	return false;
}

int main()
{
	vector<vector<int>> sequenceList;
	int n;
	int index = 0;
	while (cin >> n)
	{
		vector<int> v;
		v.reserve(n);
		sequenceList.push_back(v);

		int term;
		for (int i = 0; i < n; i++)
		{
			cin >> term;
			sequenceList[index].push_back(term);
		}
		index++;
	}

	for (int i = 0; i < sequenceList.size(); i++)
	{
		cout << (isJolly(sequenceList[i]) ? "Jolly" : "Not jolly") << endl;
	}

	return 0;
}
