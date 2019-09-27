// Longest Nap
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Time
{
	unsigned int hh;
	unsigned int mm;
};

void initTime(Time& t, unsigned int hh, unsigned int mm)
{
	t.hh = hh;
	t.mm = mm;
}

struct Appointment
{
	string desc;
	Time s;
	Time f;
	unsigned int len_minutes;
};

unsigned int len_between(const Time& a, const Time& b)
{
	return abs((int)(((a.hh * 60) + a.mm) - ((b.hh * 60) + b.mm)));
}

void initAppointment(Appointment& a, const string desc, const Time s, const Time f)
{
	a.desc = desc;
	a.s = s;
	a.f = f;
	a.len_minutes = len_between(a.s, a.f);
}

Appointment parseApptStr(const string str)
{
	unsigned int shh = stoi(str.substr(0, 2));
	unsigned int smm = stoi(str.substr(3, 2));
	unsigned int fhh = stoi(str.substr(6, 2));
	unsigned int fmm = stoi(str.substr(9, 2));
	Time s, f;
	initTime(s, shh, smm);
	initTime(f, fhh, fmm);
	
	string desc = "";
	if (str.size() >= 12) desc = str.substr(12, str.size() - 12);
	
	Appointment a;
	initAppointment(a, desc, s, f);
	return a;
}

bool compareAppt(const Appointment& a1, const Appointment& a2) //does a1 start before a2?
{
	if (a1.s.hh == a2.s.hh)
	{
		if (a1.s.mm < a2.s.mm)
		{
			return true;
		}
		return false;
	}
	else if (a1.s.hh < a2.s.hh)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& os, const Time& t)
{
	os << (t.hh < 10 ? "0" + to_string(t.hh) : to_string(t.hh))
		<< ":" << (t.mm < 10 ? "0" + to_string(t.mm) : to_string(t.mm));
	return os;
}

struct Nap
{
	Time s;
	unsigned int len;
};

Nap longestNap(vector<Appointment>& appts)
{
	if (appts.size() == 0)
	{
		Nap ln;
		Time s;
		initTime(s, 10, 0);
		ln.s = s;
		ln.len = 8 * 60;
		return ln;
	}
	sort(appts.begin(), appts.end(), compareAppt);

	Time beginningOfTimes, endOfTimes;
	initTime(beginningOfTimes, 10, 0);
	initTime(endOfTimes, 18, 0);
	Time ns = beginningOfTimes;
	unsigned int max = len_between(beginningOfTimes, appts[0].s);
	unsigned int potentialNap;
	for (int i = 0; i < appts.size() - 1; i++)
	{
		potentialNap = len_between(appts[i].f, appts[i + 1].s);
		if (potentialNap > max)
		{
			max = potentialNap;
			ns = appts[i].f;
		}
	}
	
	if (len_between(appts[appts.size() - 1].f, endOfTimes) > max)
	{
		max = len_between(appts[appts.size() - 1].f, endOfTimes);
		ns = appts[appts.size() - 1].f;
	}

	Nap ln;
	ln.s = ns;
	ln.len = max;
	return ln;
}


int main()
{
	unsigned int s;
	unsigned int day = 0;
	while (cin >> s)
	{
		vector<Appointment> appts;
		appts.reserve(s);

		string line;
		getline(cin, line);
		for (int i = 0; i < s; i++)
		{
			getline(cin, line);
			appts.push_back(parseApptStr(line));
		}

		Nap longest = longestNap(appts);
		cout << "Day #" << day + 1 << ": the longest nap starts at " << longest.s
			<< " and will last for ";
		if (longest.len >= 60)
		{
			cout << longest.len / 60 << " hours and " << longest.len % 60 << " minutes." << endl;
		}
		else
		{
			cout << longest.len << " minutes." << endl;
		}
		day++;
	}

	return 0;
}
