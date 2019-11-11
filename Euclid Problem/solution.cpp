// Euclid Problem
#include <iostream>

using namespace std;

int gcdModified(int a, int b, int& x, int& y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}

	int _x;
	int _y;
	int d = gcdModified(b, a % b, _x, _y);

	x = _y;
	y = _x - _y * (a / b);

	return d;
}

int main()
{
	int a;
	int b;
	while (cin >> a >> b)
	{
		int x;
		int y;
		int d = gcdModified(a, b, x, y);
		cout << x << " " << y << " " << d << endl;
	}

	return 0;
}
