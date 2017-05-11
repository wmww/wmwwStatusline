#pragma once

#include <string>
using std::string;

// returns true if it worked, false if failed
bool loadFile(string filepath, string& contents);
bool writeFile(string filepath, const string& contents);
string getHomeDir();
