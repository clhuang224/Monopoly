#pragma once
#include"Console.h"
#include<vector>
#include<string>
#include<iostream>
using namespace std;
using std::cout;

extern class Game;

class Option
{
public:
    Option(Game *, vector<string> = { "½T©w" }, vector<string> = {});
    void clearOption();
private:
	Game *game;
    vector<string> messages;
	vector<string> options;
	void PrintOption(int choosen);
	void PrintMenu(int choosen);
};