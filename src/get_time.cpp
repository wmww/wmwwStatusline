#include "statusline.h"
#include <ctime>
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */

string getTime(string format)
{
	if (format.empty())
		format = "%A";
		
	time_t rawtime;
	time (&rawtime);
	
	struct tm * timeinfo;
	timeinfo = localtime(&rawtime);	
	
	const int cStrBufferSize = 120;
	char cStr[cStrBufferSize];
	strftime(cStr, cStrBufferSize, format.c_str(), timeinfo);
	
	return string(cStr);
}
