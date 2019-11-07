#include <iostream>
#include <sstream>
#include <algorithm>

#define INF 9999999
#define MAX_INTERSECTIONS 501
#define MAX_FIRESTATIONS 101

using namespace std;

int distt[MAX_INTERSECTIONS][MAX_INTERSECTIONS];
int f_locs[MAX_FIRESTATIONS];

void initdistt(int size)
{
	for (int i = 1; i <= size; ++i) 
	{
		for (int j = 1; j <= size; ++j)
		{
			distt[i][j] = INF;
		}
		distt[i][i] = 0;
	}
}

void floydWarshall(int size)
{
	for (int k = 1; k <= size; ++k)
	{
		for (int i = 1; i <= size; ++i)
		{
			for (int j = 1; j <= size; ++j)
			{
				if (distt[i][k] + distt[k][j] < distt[i][j])
				{
					distt[i][j] = distt[i][k] + distt[k][j];
				}
			}
		}
	}
}

int main()
{
	int t;
	int f;
	int _i;

	cin >> t;
	for (int i = 0; i < t; ++i)
	{
		cin >> f >> _i;
		for (int j = 0; j < f; ++j)
		{
			cin >> f_locs[j];
		}

		initdistt(_i);

		string str; 
		getline(cin, str);
		while (getline(cin, str) && str != "") 
		{
			stringstream ss(str);
			int u; 
			int v;
			int w;
			ss >> u >> v >> w;
			distt[u][v] = w;
			distt[v][u] = w;
		}

		floydWarshall(_i);

		int shortest[MAX_INTERSECTIONS];
		int max_shortest = 0;
		for (int j = 1; j <= _i; ++j) 
		{
			shortest[j] = INF;
			for (int k = 0; k < f; ++k)
			{
				shortest[j] = min(shortest[j], distt[j][f_locs[k]]);
			}
			max_shortest = max(max_shortest, shortest[j]);
		}

		int res = 1;
		for (int j = 1; j <= _i; ++j) 
		{
			int new_length = 0;
			for (int k = 1; k <= _i; ++k) 
			{
				int shorter = min(distt[j][k], shortest[k]);
				new_length = max(new_length, shorter);
			}

			if (new_length < max_shortest)
			{
				max_shortest = new_length;
				res = j;
			}
		}
		cout << res << endl;
		if (i != t - 1) cout << endl;
	}

	return 0;
}
