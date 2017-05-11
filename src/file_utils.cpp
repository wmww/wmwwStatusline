
#include "statusline.h"

#include <fstream>
#include <sstream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

using std::stringstream;

bool loadFile(string filepath, string& contents)
{
	std::fstream inFile;
	
	inFile.open(filepath);
	
	if (!inFile.is_open())
	{
		return false;
	}
	else
	{
		stringstream strStream;
		strStream << inFile.rdbuf();//read the file
		contents = strStream.str();//str holds the content of the file
		inFile.close();
		return true;
	}
}

bool writeFile(string filepath, const string& contents)
{
	std::ofstream outFile;
	
	outFile.open(filepath);
	
	if (!outFile.is_open())
	{
		return false;
	}
	else
	{
		outFile << contents;
		
		outFile.close();
		
		return true;
	}
}

string getHomeDir()
{
	const char *homedir;
	
	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}
	
	return string(homedir);
}

