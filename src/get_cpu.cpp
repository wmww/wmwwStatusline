
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "statusline.h"

#include <fstream>

#include "number_conversion_utils.h"

unsigned long long lastCpuTotal = 0;
unsigned long long lastCpuUsed = 0;

vector<unsigned long long> lastCpusTotal;
vector<unsigned long long> lastCpusUsed;

void getCpu(vector<double>& cpus)
{
	std::ifstream procStat;
	procStat.open("/proc/stat");
	
	if (!procStat.is_open())
	{
		return;
	}
	
	while (true)
	{
		//cout << "line is " << lineStr << endl << 
		//endl << endl;
		
		string start;
		
		procStat >> start;
		
		if (!wmstr::startsWith(start, "cpu"))
		{
			break;
		}
		
		if (start == "cpu")
		{
			string lineStr;
			
			if (!getline(procStat, lineStr))
				return;
		}
		else
		{
			string lineStr;
			
			if (!getline(procStat, lineStr))
				return;
			
			vector<string> line;
			
			wmstr::splitBy(line, lineStr, " ");
			
			unsigned long long int user = 0, unice = 0, usystem = 0, idle = 0, iowait = 0, irq = 0, softirq = 0, guest = 0;
			
			#define TRY_INDEX(array, index, default) ((index >= array.size()) ? default : stringToUnsignedLongLong(array[index]))
			
			int index = stringToInt(start);
			
			user = TRY_INDEX(line, 0, 0);
			unice = TRY_INDEX(line, 1, 0);
			usystem = TRY_INDEX(line, 2, 0);
			idle = TRY_INDEX(line, 3, 0);
			iowait = TRY_INDEX(line, 4, 0);
			irq = TRY_INDEX(line, 5, 0);
			softirq = TRY_INDEX(line, 6, 0);
			guest = TRY_INDEX(line, 7, 0);
			
			while ((int)lastCpusUsed.size() <= index)
				lastCpusUsed.push_back(0);
			
			while ((int)lastCpusTotal.size() <= index)
				lastCpusTotal.push_back(0);
			
			while ((int)cpus.size() <= index)
				cpus.push_back(0);
			
			unsigned long long used = user + unice + usystem + irq + softirq + guest;
			unsigned long long total = used + idle + iowait;
			
			double ratioUsed = 0;
			
			if (total - lastCpusTotal[index] > 0)
			{
				ratioUsed = (double)(used - lastCpusUsed[index]) / (double)(total - lastCpusTotal[index]);
			}
			
			cpus[index] = ratioUsed;
			lastCpusUsed[index] = used;
			lastCpusTotal[index] = total;
		}
	}
	
	return;
}

/*

double getCpu0()
{
    FILE *fd;
    unsigned long long int user, unice, usystem, idle, iowait, irq, softirq, guest;
    long used, total;
    int nb_read;

    fd = fopen("/proc/stat", "r");
    if (!fd) {
        //g_warning(_("File /proc/stat not found!"));
        return 0;
    }

    // Don't count steal time. It is not busy or free time.
    nb_read = fscanf (fd, "%*s %llu %llu %llu %llu %llu %llu %llu %*u %llu",
	    &user, &unice, &usystem, &idle, &iowait, &irq, &softirq, &guest);
    
    fclose(fd);
    
    switch (nb_read) // fall through intentional
    {
	case 4:
		iowait = 0;
	case 5:
		irq = 0;
	case 6:
		softirq = 0;
	case 7:
		guest = 0;
    }
	
    used = user + unice + usystem + irq + softirq + guest;
    total = used + idle + iowait;
	
	double cpu_used = 0;
	
	long oldtotal = lastCpuTotal;
	long oldused = lastCpuUsed;
	
    if ((total - oldtotal) != 0)
    {
        cpu_used = (double)(used - oldused) / (double)(total - oldtotal);
    }
    
	lastCpuTotal = total;
	lastCpuUsed = used;
    
    return cpu_used;
}

*/
