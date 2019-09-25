// Vito's Family
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int arr[500];
	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		int r;
		cin >> r;

		for (int j = 0; j < r; j++)
		{
			cin >> arr[j];
		}

		sort(arr, arr + r);

		int median = arr[r / 2];
		int sum = 0;
		for (int j = 0; j < r; j++)
		{
			sum += abs(median - arr[j]);
		}
		cout << sum << endl;
	}

	return 0;
}
