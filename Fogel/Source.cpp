#include "Header.h"

int max_id(vector<int> v)
{
	int id = -1;
	int max = -1000000;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] > max)
		{
			max = v[i];
			id = i;
		}
	}
	return id;
}
 
int min_id(vector<cell> v)
{
	int id = -1;
	int min = 1000000;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i].used)
			continue;
		if (v[i].val < min)
		{
			min = v[i].val;
			id = i;
		}
	}
	return id;
}
