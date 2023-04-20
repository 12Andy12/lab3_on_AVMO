#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include "Header.h"


using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

ostream& operator<< (ostream& out, fogel f)
{
	for (int i = 0; i < f.matrix.size(); ++i)
	{
		for (int j = 0; j < f.matrix[i].size(); ++j)
		{

			if (f.matrix[i][j].res!=0)
			{
				SetConsoleTextAttribute(h, 4);
				out << setw(3) << f.matrix[i][j].res;
			}
			else if (f.matrix[i][j].used == true)
			{
				SetConsoleTextAttribute(h, 0);
				out << setw(3) << f.matrix[i][j].val;
			}
			else
			{
				SetConsoleTextAttribute(h, 15);
				out << setw(3) << f.matrix[i][j].val;
			}
				
		}
		SetConsoleTextAttribute(h, 15);
		out << "|" << setw(5) << f.supply[i] << setw(5) << f.horizontal[i] << "\n";
	}

	SetConsoleTextAttribute(h, 15);
	for (int i = 0; i < f.matrix[0].size(); ++i)
		out << "---";
	out << "\n";

	for (auto i : f.needs)
		out << setw(3) << i;
	out << "\n";

	for (auto i : f.vertical)
		out << setw(3) << i;
	out << '\n';


	return out;
}

ostream& operator<< (ostream& out, vector<vector<int>> v)
{
	for (auto i : v) {
		for (auto j : i)
			out << j << ' ';
		cout << '\n';
	}
	return out;
}





fogel read(string fileName)
{
	ifstream file;
	file.open(fileName);
	int n, m;
	file >> n >> m;
	fogel table(n, m);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			file >> table.matrix[i][j].val;
		file >> table.supply[i];
	}

	for (int i = 0; i < m; ++i)
		file >> table.needs[i];

	return table;
}

bool complited(fogel table)
{
	for (auto i : table.needs)
		if (i != 0)
			return false;

	return true;
}

int allNeeds(fogel table)
{
	int sum = 0;
	for (auto i : table.needs)
		sum += i;
	return sum;
}

int allHaves(fogel table)
{
	int sum = 0;
	for (auto i : table.supply)
		sum += i;
	return sum;
}


int main()
{
	fogel table = read("1.txt");
	if (allNeeds(table) > allHaves(table))
	{
		vector<cell> fictitious_supplier(table.matrix[0].size());
		table.matrix.push_back(fictitious_supplier);
		table.supply.push_back(allNeeds(table) - allHaves(table));
		table.horizontal.push_back(0);
	}
	if (allNeeds(table) < allHaves(table))
	{
		for (int i = 0; i < table.matrix.size(); ++i) 
		{
			cell a;
			table.matrix[i].push_back(a);
		}
		table.vertical.push_back(0);
		table.needs.push_back(allHaves(table) - allNeeds(table));
	}
	while (!complited(table))
	{
		table.calculateVH();
		table.calulateSN();
		cout << table << "\n";
	}
	 
	
}
