// Lights, Lights, More Lights
#include <iostream>
#include <math.h>

using namespace std;

int main()
{ 
	long long n;
	cin >> n;
	while (n != 0)
	{
		unsigned int floored_sqrt_n = sqrt(n);
		cout << ((unsigned long long)floored_sqrt_n * floored_sqrt_n == n ? "yes" : "no") << endl;
		cin >> n;
	}

	return 0;
}
