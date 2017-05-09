#include "graphics.h"
#include <math.h>
using std::max;
using std::min;

vector<string> verticalBarStrs = {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"};

string verticalBar(double val)
{
	int i=min(floor(val * verticalBarStrs.size()), (double)verticalBarStrs.size()-1);
	return verticalBarStrs[i];
}

