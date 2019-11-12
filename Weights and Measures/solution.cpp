// Weights and Measures
#include <iostream> 
#include <vector>
#include <algorithm>

#define INF 2147483647
#define MAX_TURTLES 5607

using namespace std;

int dp[MAX_TURTLES];

struct Turtle
{
	int w;
	int s;

	bool operator<(const Turtle& other) const
	{
		return s < other.s;
	}
};

int max(const int& a, const int& b)
{
	return a > b ? a : b;
}

int stackem(vector<Turtle>& turtles)
{
	sort(turtles.begin(), turtles.end());

	dp[0] = 0;
	for (int i = 1; i < MAX_TURTLES; ++i)
	{
		dp[i] = INF;
	}

	int result = 0;
	for (int i = 0; i < turtles.size(); ++i)
	{
		for (int j = result; j >= 0; --j)
		{
			if (turtles[i].s >= dp[j] + turtles[i].w && dp[j + 1] > turtles[i].w + dp[j])
			{
				dp[j + 1] = dp[j] + turtles[i].w;
				result = max(result, j + 1);
			}
		}
	}

	return result;
}

int main()
{
	vector<Turtle> turtles;
	Turtle t;
	while (cin >> t.w >> t.s)
	{
		turtles.push_back(t);
	}

	cout << stackem(turtles) << endl;

	return 0;
}
