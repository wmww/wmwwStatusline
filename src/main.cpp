#include "statusline.h"
#include <unistd.h>

PersistentData data;

const string tempDataPath="/tmp/wmww_statusline_data.txt";
const string configPath="config.txt";

const string defaultConfig=
	"items: [CPU, RAM, TIME]"
	;

// returns true if program should abort
bool processArgs(int argc, char ** argv)
{
	vector<string> args;
	bool quit=false;
	
	for (int i=1; i<argc; i++)
	{
		args.push_back(string(argv[i]));
	}
	
	for (int i=0; i<(int)args.size(); i++)
	{
		if (args[i]=="-h")
		{
			cout << "WMWW Statusline" << endl;
			cout << "usage: wmww_status [OPTIONS]" << endl;
			cout << "options:" << endl;
			cout << "    -r, --reset: delete temp file, thus forcing a reload of config" << endl;
			quit = true;
			break;
		}
		else
		{
			cout << "ERROR: unrecognized option '" << args[i] << "'" << endl;
			cout << "run 'wmww_status -h' for help" << endl;
			quit = true;
			break;
		}
	}
	
	return quit;
}

void loadData()
{
	if (!data.fromFile(tempDataPath, ""))
	{
		if (!data.fromFile(configPath, "config"))
		{
			data.fromString(defaultConfig, "config");
		}
	}
}

void saveData()
{
	data.toFile(tempDataPath);
}

int main(int argc, char ** argv)
{
	if (processArgs(argc, argv))
		return 0;
	
	loadData();
	
	/*
	while (true)
	{
		usleep(40000);
		cout << getCpu() << endl;
	}
	*/
	
	/*
	PersistentData data;
	
	if (!data.loadFrom("config.txt", "config"))
	{
		cout << "error loading file" << endl;
	}
	*/
	
	cout << data.toString() << endl;
	
	saveData();
	
	return 0;
}

