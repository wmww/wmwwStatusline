
#include "statusline.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

double getRam()
{
	const int bufferSize = 2 * 1024;
	char ramDataBuffer[bufferSize];
	
	unsigned long totalRam = 0;
	unsigned long freeRam = 0;
	
	int ramFile;
	size_t n;

	if ((ramFile = open("/proc/meminfo", O_RDONLY)) < 0)
	{
		//printf("Cannot open \'/proc/meminfo\'");
		return -1;
	}
	if ((n = read(ramFile, ramDataBuffer, bufferSize - 1)) == bufferSize - 1)
	{
		//printf("Internal buffer too small to read \'/proc/mem\'");
		close(ramFile);
		return -1;
	}
	close(ramFile);

	ramDataBuffer[n] = '\0';
	
	char * i;
	
	i = strstr(ramDataBuffer, "MemTotal");
	if (!i || !sscanf(i + strlen("MemTotal"), ": %lu", &totalRam))
		return -1;
	
	i = strstr(ramDataBuffer, "MemAvailable");
	if (!i || !sscanf(i + strlen("MemAvailable"), ": %lu", &freeRam))
		return -1;
	
	unsigned long usedRam = totalRam - freeRam;
	
	return (double)usedRam / totalRam;
}

