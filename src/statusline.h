#pragma once

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include "ConfigData.h"

#include "number_conversion_utils.h"

string getTime(string format="");

double getRam();

double getCpu();

