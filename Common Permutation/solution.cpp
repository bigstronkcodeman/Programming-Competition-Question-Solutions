// Common Permutation
#include <iostream>
#include <vector>
#include <array>
#include <string>

#define NUMLETTERS 26

using namespace std;

void initLetterMap(array<int, NUMLETTERS>& letterMap)
{
	for (int i = 0; i < NUMLETTERS; i++)
	{
		letterMap[i] = 0;
	}
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int asciiMap(char c)
{
	if (c <= 122 && c >= 97)
	{
		return c - 97;
	}
	return -1;
}

char character(int map)
{
	map += 97;
	if (map <= 122 && map >= 97)
	{
		return (char)map;
	}
	return (char)0;
}

string commonPermutation(string a, string b)
{
	array<int, NUMLETTERS> amap;
	array<int, NUMLETTERS> bmap;
	initLetterMap(amap);
	initLetterMap(bmap);

	for (int i = 0; i < a.length(); i++)
	{
		amap[asciiMap(a[i])]++;
	}

	for (int i = 0; i < b.length(); i++)
	{
		bmap[asciiMap(b[i])]++;
	}
	
	string result = "";
	for (int i = 0; i < NUMLETTERS; i++)
	{
		if (amap[i] > 0 && bmap[i] > 0)
		{
			for (int j = 0; j < min(amap[i], bmap[i]); j++)
			{
				result += character(i);
			}
		}
	}

	return result;
}

int main()
{
	vector<string> strings;
	string s1;
	string s2;
	while (getline(cin, s1) && getline(cin, s2))
	{
		strings.push_back(s1);
		strings.push_back(s2);
	}

	for (int i = 0; i < strings.size() - 1; i += 2)
	{
		cout << commonPermutation(strings[i], strings[i + 1]) << endl;
	}

	return 0;
}
