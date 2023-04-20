#pragma once

class cell {
public:
	int val = 0;
	int res = 0;
	bool used = false;
	bool operator<(cell second)
	{
		return val < second.val;
	}
};
 



