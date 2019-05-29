#pragma once
#include"Console.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;

extern class Game;

class Option
{
public:
	Option(Game *, vector<string>);
	~Option();
private:
	Game *ptr;
	vector<string> options;
	void PrintOption(int choosen);
	void PrintMenu(int choosen);
};