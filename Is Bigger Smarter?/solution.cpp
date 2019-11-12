//Is Bigger Smarter?
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_ELES 1000

using namespace std;

struct Elephant
{
	int w;
	int iq;
	int id;
};

Elephant ele[MAX_ELES];

bool comparator(const Elephant& a, const Elephant& b)
{
	return a.iq > b.iq;
}

vector<Elephant> LIS(int n)
{
	sort(ele, ele + n, comparator);

	vector<Elephant> dp[MAX_ELES];
	dp[0] = { ele[0] };
	for (int i = 1; i < n; ++i)
	{
		int ind = -1;
		int maxlen = 0;
		int bestid = -1;
		for (int j = 0; j < i; ++j)
		{
			int dpjlen = dp[j].size();
			if (ele[j].w < ele[i].w && ele[j].iq > ele[i].iq && (dpjlen > maxlen || (dpjlen == maxlen && ele[j].id > bestid)))
			{
				ind = j;
				maxlen = dpjlen;
				bestid = ele[j].id;
			}
		}

		if (ind >= 0)
		{
			for (int j = 0; j < maxlen; ++j)
			{
				dp[i].push_back(dp[ind][j]);
			}
		}
		dp[i].push_back(ele[i]);
	}

	int resi = 0;
	int maxlen = dp[0].size();
	for (int i = 1; i < n; ++i)
	{
		int dpilen = dp[i].size();
		if (dpilen > maxlen)
		{
			resi = i;
			maxlen = dpilen;
		}
	}

	return dp[resi];
}

int main()
{
	int n = 0;
	while (cin >> ele[n].w >> ele[n].iq)
	{
		ele[n].id = n + 1;
		++n;
	}

	vector<Elephant> soln = LIS(n);
	cout << soln.size() << endl;
	for (int i = 0; i < soln.size(); ++i)
	{
		cout << soln[i].id << endl;
	}

	return 0;
}
