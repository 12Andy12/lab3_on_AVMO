#pragma once
#include "Header.h"


class fogel {
public:
	fogel(int n, int m) {
		vector<vector <cell> > new_matrix(n, vector<cell>(m));
		matrix = new_matrix;
		horizontal.resize(n);
		vertical.resize(m);
		needs.resize(m);
		supply.resize(n);
	}
	vector<vector <cell> > matrix;
	vector<int> vertical;
	vector<int> horizontal;
	vector<int> needs;
	vector<int> supply;
	int idH;
	int idV;
	int idRow;
	int idCol;

	void calulateSN()
	{
		int need = needs[idCol];
		int have = supply[idRow];

		if (have >= need)
		{
			matrix[idRow][idCol].res = need;
			have -= need;
			need -= need; // = 0;
			for (int i = 0; i < matrix.size(); ++i)
				matrix[i][idCol].used = true;
		}
		else if (need > have)
		{
			matrix[idRow][idCol].res = have;
			for (int i = 0; i < matrix[0].size(); ++i)
				matrix[idRow][i].used = true;
			need -= have;
			have -= have; // = 0
		}

		needs[idCol] = need;
		supply[idRow] = have;

	}

	void calculateVH()
	{

		for (int i = 0; i < matrix.size(); ++i)
		{
			vector<cell> row;
			for (int j = 0; j < matrix[0].size(); ++j)
				if (!matrix[i][j].used)
					row.push_back(matrix[i][j]);
			sort(row.begin(), row.end());
			if (row.size()>=2)
				horizontal[i] = row[1].val - row[0].val;
			else 
				horizontal[i] = 0;
		}
		 
		for (int j = 0; j < matrix[0].size(); ++j)
		{
			vector<int> column;

			for (int i = 0; i < matrix.size(); ++i)
				if (!matrix[i][j].used)
					column.push_back(matrix[i][j].val);

			sort(column.begin(), column.end());
			if (column.size() >= 2)
				vertical[j] = column[1] - column[0];
			else 
				vertical[j] = 0;
		}

		idV = max_id(vertical);
		idH = max_id(horizontal);

		//cout << "\n horizontal id = " << idH << ";\n vertical id = " << idV << "\n";
		//cout << "\n horizontal[idH] = " << horizontal[idH] << ";\n vertical[idV] = " << vertical[idV] << "\n";

		if (horizontal[idH] > vertical[idV])
		{
			idRow = idH;
			idCol = min_id(matrix[idRow]);
		}
		else
		{
			vector<cell> column;

			for (int i = 0; i < matrix.size(); ++i)
				column.push_back(matrix[i][idV]);

			idRow = min_id(column);
			idCol = idV;
		}



	}
};
