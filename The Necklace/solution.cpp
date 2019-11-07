// The Necklace
#include <iostream>
#include <stack>
#include <vector>

#define COLORS 51

using namespace std;

int graph[COLORS][COLORS];
int degree[COLORS];

void clear()
{
	for (int i = 0; i < COLORS; ++i)
	{
		degree[i] = 0;
		for (int j = 0; j < COLORS; ++j)
		{
			graph[i][j] = 0;
		}
	}
}

bool isEulerian()
{
	for (int j = 0; j < COLORS; ++j)
	{
		if (degree[j] % 2 != 0)
		{
			return false;
		}
	}
	return true;
}

void cycleHelper(vector<int>& path, int u)
{
	for (int v = 0; v < COLORS; ++v)
	{
		if (graph[u][v] > 0)
		{
			--graph[u][v];
			--graph[v][u];
			--degree[u];
			--degree[v];
			cycleHelper(path, v);
		}
	}
	path.push_back(u);
}

vector<int> eulerianCycle(int startNode)
{
	vector<int> path;
	cycleHelper(path, startNode);
	return path;
}

int main()
{
	vector<vector<int>> paths;
	int t;
	int n;

	cin >> t;
	for (int i = 0; i < t; ++i)
	{
		cin >> n;

		clear();
		int u;
		int v;
		for (int j = 0; j < n; ++j)
		{
			cin >> u >> v;
			++graph[u][v];
			++graph[v][u];
			++degree[u];
			++degree[v];
		}

		if (!isEulerian())
		{
			paths.push_back({});
		}
		else
		{
			paths.push_back(eulerianCycle(v));
		}
	}

	for (int i = 0; i < paths.size(); ++i)
	{
		cout << "Case #" << i + 1 << '\n';
		if (paths[i].size() > 0)
		{
			for (int j = 0; j < paths[i].size() - 1; ++j)
			{
				cout << paths[i][j] << ' ' << paths[i][j + 1] << '\n';
			}
		}
		else
		{
			cout << "some beads may be lost\n";
		}
		if (i != paths.size() - 1) cout << '\n';
	}

	return 0;
}
