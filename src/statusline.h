#pragma once

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include "persistent_data.h"

extern PersistentData data;

string getTime(string format="");

double getRam();

double getCpu();

