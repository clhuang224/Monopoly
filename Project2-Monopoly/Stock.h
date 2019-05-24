#pragma once
#include <string>
#include <vector>

using namespace std;

struct stockData
{
	string name;
	unsigned int value;
};

class Stock
{
private:
	vector<struct stockData> stockList;

public:
	Stock();
	~Stock();

	void getStockList();
	void valueChange();
};



