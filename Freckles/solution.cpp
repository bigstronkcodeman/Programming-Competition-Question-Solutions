// Freckles
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#define MAX_VERTS 100
#define MAX_EDGES 5050

using namespace std;

struct RealsPair
{
	double x;
	double y;

	bool operator==(const RealsPair& other) const
	{
		return x == other.x && y == other.y;
	}
};

struct Edge
{
	RealsPair p1;
	RealsPair p2;
	double w;

	bool operator<(const Edge& other) const
	{
		return w < other.w;
	}
};

struct MyHash
{
	int operator()(const RealsPair& rp) const
	{
		return (rp.x * rp.y) + rp.x;
	}
};

template<typename T>
void clear(T arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = T();
	}
}

int sumNaturals(int upto)
{
	return (upto * (upto + 1)) / 2;
}

RealsPair find(unordered_map<RealsPair, RealsPair, MyHash>& parents, RealsPair key)
{
	if (!(parents[key] == key))
	{
		parents[key] = find(parents, parents[key]);
	}
	return parents[key];
}

bool done(unordered_map<RealsPair, RealsPair, MyHash>& parents, RealsPair pairs[MAX_VERTS], int n)
{
	RealsPair rep = parents[pairs[0]];
	for (int i = 1; i < n; ++i)
	{
		if (!(parents[pairs[i]] == rep))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	RealsPair pairs[MAX_VERTS];
	Edge edges[MAX_EDGES];
	int t;
	int n;

	clear(pairs, MAX_VERTS);
	clear(edges, MAX_EDGES);

	cin >> t;

	double* results = new double[t];
	int ri = 0;

	for (int i = 0; i < t; ++i)
	{
		string dummy;
		getline(cin, dummy);

		cin >> n;
		for (int j = 0; j < n; ++j)
		{
			cin >> pairs[j].x >> pairs[j].y;
		}

		int cnt = 0;
		for (int j = 0; j < n; ++j)
		{
			for (int k = j + 1; k < n; ++k)
			{
				if (k != j)
				{
					Edge e;
					e.p1 = pairs[j];
					e.p2 = pairs[k];
					e.w = sqrt(((e.p2.x - e.p1.x) * (e.p2.x - e.p1.x)) 
						+ ((e.p2.y - e.p1.y) * (e.p2.y - e.p1.y)));
					edges[cnt++] = e;
				}
			}
		}

		int esize = sumNaturals(n - 1);
		sort(begin(edges), begin(edges) + esize);

		unordered_map<RealsPair, RealsPair, MyHash> parents;
		parents.reserve(n);
		for (int i = 0; i < n; ++i)
		{
			parents[pairs[i]] = pairs[i];
		}

		double sum = 0;
		for (int i = 0; i < esize; ++i)
		{
			Edge e = edges[i];
			RealsPair p1 = find(parents, e.p1);
			RealsPair p2 = find(parents, e.p2);
			if (!(p1 == p2))
			{
				parents[p1] = p2;
				sum += e.w;
			}

			if (done(parents, pairs, n))
			{
				break;
			}
		}

		results[ri++] = roundf(sum * 100) / 100.0;

		clear(pairs, n);
		clear(edges, esize);
	}

	for (int i = 0; i < t; ++i)
	{
		cout << fixed << setprecision(2) << results[i] << endl;
		if (i != t - 1) cout << endl;
	}

	delete[] results;
	
	return 0;
}
