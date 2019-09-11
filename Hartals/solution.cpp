// Hartals
#include <iostream>
#include <vector>

#define DAYS_IN_WEEK 7

using namespace std;

int main()
{
	vector<int> results;

	int T;
	cin >> T;

	for (int k = 0; k < T; k++)
	{
		int N;
		cin >> N;

		int* days = new int[N];

		for (int i = 0; i < N; i++)
		{
			days[i] = 0;
		}

		int P;
		cin >> P;

		for (int i = 0; i < P; i++)
		{
			int h;
			cin >> h;

			for (int j = h - 1; j < N; j += h)
			{
				int weeksPast = j / DAYS_IN_WEEK;
				int dow = (j % DAYS_IN_WEEK);
				int date = (weeksPast * DAYS_IN_WEEK) + dow;
				if (dow != 5 && dow != 6)
				{
					days[date]++;
				}
			}
		}

		int daysLost = 0;
		for (int i = 0; i < N; i++)
		{
			if (days[i] > 0)
			{
				daysLost++;
			}
		}

		results.push_back(daysLost);

		delete[] days;
	}

	for (int i = 0; i < results.size(); i++)
	{
		cout << results[i] << endl;
	}

	return 0;
}
