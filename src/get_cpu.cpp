
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "statusline.h"

double getCpu()
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
	
	long cpu_used = 0;
	
	long oldtotal = data.get("last.cpu_total").asNum();
	long oldused = data.get("last.cpu_used").asNum();
	
    if ((total - oldtotal) != 0)
    {
        cpu_used = (100 * (double)(used - oldused)) / (double)(total - oldtotal);
    }
    
    data.set("last.cpu_total", (double)total);
    data.set("last.cpu_used", (double)used);
    
    return cpu_used;
}
