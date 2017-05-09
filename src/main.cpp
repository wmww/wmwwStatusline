#include "statusline.h"
#include <unistd.h>

PersistentData data;

const string tempDataPath="/tmp/wmww_statusline_data.txt";
const string configPath="config.txt";

const string defaultConfig=
	"items: [CPU, RAM]"
	;

int main(int argc, char ** argv)
{
	if (!data.fromFile(tempDataPath, ""))
	{
		if (!data.fromFile(configPath, "config"))
		{
			data.fromString(defaultConfig, "config");
		}
	}
	
	while (true)
	{
		usleep(40000);
		cout << getCpu() << endl;
	}
	
	
	/*
	PersistentData data;
	
	if (!data.loadFrom("config.txt", "config"))
	{
		cout << "error loading file" << endl;
	}
	
	cout << data.getAsWmwwConfig() << endl;
	*/
	
	return 0;
}

