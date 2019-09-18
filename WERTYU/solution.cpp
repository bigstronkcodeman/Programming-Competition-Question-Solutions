// WERTYU
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<vector<char>> keyboard = { {'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=' },
					{  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']'    },
					{    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\''      },
					{      'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/'          } };

vector<int> keyboardi(char c)
{
	vector<int> indices;
	for (int i = 0; i < keyboard.size(); i++)
	{
		for (int j = 0; j < keyboard[i].size(); j++) 
		{
			if (keyboard[i][j] == c)
			{
				indices.push_back(i);
				indices.push_back(j);
				return indices;
			}
		}
	}
}

string QWERTYify(string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		vector<int> indices = keyboardi(s[i]);
		s[i] = indices.size() > 0 ? keyboard[indices[0]][indices[1] - 1] : s[i];
	}
	return s;
}

int main()
{
	vector<vector<string>> words;
	string line;
	int index = 0;
	while (getline(cin, line) && line != "")
	{
		words.push_back(vector<string>());
		string word = "";
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != ' ')
			{
				word += line[i];
			}
			else
			{
				words[index].push_back(word);
				word = "";
			}
		}
		words[index].push_back(word);
		index++;
	}

	for (int i = 0; i < words.size(); i++)
	{
		for (int j = 0; j < words[i].size(); j++)
		{
			cout << QWERTYify(words[i][j]) << (j != words[i].size() - 1 ? " " : "");
		}
		cout << endl;
	}

	return 0;
}
