#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class fogel {
public:
	fogel(int n, int m) {
		vector<vector <int> > new_matrix1(n + 1, vector<int>(m + 1, 0));
		matrix = new_matrix1;
		vector<vector <bool> > new_matrix2(n + 1, vector<bool>(m + 1, false));
		deleted = new_matrix2;
		horizontal.resize(n + 1);
		vertical.resize(m + 1);
	}
	vector<vector <int> > matrix;
	vector<vector <bool> > deleted;
	vector<int> vertical;
	vector<int> horizontal;

	void calc()
	{

		for (int i = 0; i < matrix.size(); ++i)
		{
			vector<int> line = matrix[i];
			sort(line.begin(), line.end());
			horizontal[i] = line[1] - line[0];
		}

		for (int j = 0; j < matrix[0].size(); ++j)
		{
			vector<int> column;
			for (int i = 0; i < matrix.size(); ++i)
				column.push_back(matrix[i][j]);
			sort(column.begin(), column.end());
			vertical[j] = column[1] - column[0];
		}

	}
};



ostream& operator<< (ostream& out, vector<vector<int>> v)
{
	for (auto i : v) {
		for (auto j : i)
			out << j << ' ';
		cout << '\n';
	}
	return out;
}

ostream& operator<< (ostream& out, fogel f)
{
	for (int i = 0; i < f.matrix.size(); ++i)
	{
		for (int j = 0; j < f.matrix[i].size(); ++j)
		{
			if (f.deleted[i][j] == true)
				out << "- ";
			else
				out << f.matrix[i][j] << ' ';
		}

		out << f.horizontal[i] << "\n";
	}

	for (auto i : f.vertical)
		out << i << ' ';
	out << '\n';

	return out;
}



fogel read(string fileName)
{
	ifstream file;
	file.open(fileName);
	int n, m;
	file >> n >> m;
	fogel table(n, m);

	for (int i = 0; i < n + 1; ++i)
		for (int j = 0; j < m + 1; ++j)
			file >> table.matrix[i][j];

	table.calc();




	return table;
}


int main()
{
	cout << read("1.txt");
}
