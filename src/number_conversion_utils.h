#pragma once

#include <string>
using std::string;

#include <vector>
using std::vector;

string intToString(int in);
string doubleToString(double in);
int stringToInt(string in);
double stringToDouble(string in);

string verticalBar(double val);
string doubleAsPercent(double val);
string horizontalBar(double val, int charWidth);
