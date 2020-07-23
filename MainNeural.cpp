#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <windows.h>

using namespace std;

//Многослойный Персептрон (Нейросеть)
//Считает функцию "Исключающее ИЛИ"

const int entersSize = 2;
const int hiddensSize = 2;
const int patternsSize = 4;

double enters[entersSize];
double hiddens[hiddensSize];
double outer;
double wEH[entersSize][hiddensSize];
double wHO[hiddensSize];
double patterns[patternsSize][entersSize] =
{
	{ 0,0 }, { 0,1 }, { 1,0 }, { 1,1 }
};
double answers[patternsSize] =
{
	0, 1, 1, 0
};

void Restart()
{
	for (int i = 0; i<entersSize; i++)
	{
		for (int j = 0; j<hiddensSize; j++)
		{
			wEH[i][j] = rand() % 100 * 0.01 + 0.1;
		}
	}
	for (int i = 0; i<hiddensSize; i++)
	{
		wHO[i] = rand() % 100 * 0.01 + 0.1;
	}
}

void Work()
{
	outer = 0;
	for (int i = 0; i<hiddensSize; i++)
	{
		hiddens[i] = 0;
		for (int j = 0; j<entersSize; j++)
		{
			hiddens[i] += enters[j] * wEH[j][i];
		}
		if (hiddens[i]>0.5) hiddens[i] = 1;
		else hiddens[i] = 0;
	}
	for (int i = 0; i<hiddensSize; i++)
	{
		outer += hiddens[i] * wHO[i];
	}
	if (outer>0.5) outer = 1;
	else outer = 0;
}

void Study()
{
	double gError = 0;
	double errors[hiddensSize];
	do
	{
		gError = 0;
		for (int p = 0; p<patternsSize; p++)
		{
			for (int e = 0; e<entersSize; e++)
			{
				enters[e] = patterns[p][e];
			}
			Work();
			double lError = answers[p] - outer;
			gError += abs(lError);
			for (int i = 0; i<hiddensSize; i++)
			{
				errors[i] = lError*wHO[i];
			}
			for (int i = 0; i<entersSize; i++)
			{
				for (int j = 0; j<hiddensSize; j++)
				{
					wEH[i][j] += 0.1*errors[j]*enters[i];
				}
			}
			for (int i = 0; i<hiddensSize; i++)
			{
				wHO[i] += 0.1*lError*hiddens[i];
			}
		}
	} while (gError != 0);
}

void Test()
{
	for (int p = 0; p<patternsSize; p++)
	{
		for (int e = 0; e<entersSize; e++)
		{
			enters[e] = patterns[p][e];
		}
		Work();
		cout << outer << endl;
	}
}

int main() {
	Restart();
	cout << "Neural network is starting!" << endl;
	string s;
	while (true)
	{
		cin >> s;
		if (s == "/study")
		{
			Study();
			cout << "Neural network stadied!" << endl;
		}
		if (s == "/work")
		{
			for (int i = 0; i<entersSize; i++)
			{
				cin >> enters[i];
			}
			Work();
			cout << "Answer: " << outer << endl;
		}
		if (s == "/test")
		{
			Test();
		}
		if (s == "/restart")
		{
			Restart();
		}
		if (s == "/exit")
		{
			cout << "Neural network is finished!" << endl;
			return 0;
		}
	}

	return 0;
}
