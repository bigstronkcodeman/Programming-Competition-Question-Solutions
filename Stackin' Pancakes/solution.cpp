// Stacking Pancakes
#include<iostream>
#include<string>
#include <vector>
#include <array>

using namespace std; 

vector<int> tokenizeIntString(string line, char token)
{
	vector<int> results;
	string e = "";
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != token)
		{
			e += line[i];
		}
		else
		{
			results.push_back(stoi(e));
			e = "";
		}
	}
	if (e != "") results.push_back(stoi(e));
	return results;
}

int main() 
{
	array<int, 30> stack;

	string line;

	while (getline(cin, line))
	{
		int n = 0;

		vector<int> pancakes = tokenizeIntString(line, ' ');

		cout << line << endl;

		for (int i = 0; i < pancakes.size(); i++)
		{
			stack[n++] = pancakes[i];
		}

		for (int i = n - 1; i >= 0; i--) 
		{
			int max = -1;

			int index = -1;
			for (int j = 0; j <= i; j++)
			{
				if (max <= stack[j])
				{
					max = stack[j];
					index = j;
				}
			}

			if (index != i)
			{
				if (index != 0)
				{
					cout << n - index << " ";

					for (int j = 0; j <= index / 2; j++)
					{
						swap(stack[j], stack[index - j]);
					}
				}

				cout << n - i << " ";

				for (int j = 0; j <= i / 2; j++)
				{
					swap(stack[j], stack[i - j]);
				}
			}
		}
		cout << 0 << endl;
	}
	return 0;
}
