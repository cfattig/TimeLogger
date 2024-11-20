
#ifndef _LOGGER_H_
#define _LOGGER_H_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;


struct record
{
	char first[15], last[15], bdate[8]; // names and birthday
	double time = 0.0;
	bool edit = false;
};

void menu(vector<record> &p, double &goal);
record create();
void display(vector<record> p, int dtype, double goal);
void instructions();
void remove(vector<record> &p);
void timer(vector<record> &p, double goal);
void read(vector<record> &p, double &goal);
void write(vector<record> &p, double goal);
void swrite(vector<record> &p, double goal);
void pwrite(vector<record> &p, double goal);
void change(vector<record> &p, double goal);

#endif