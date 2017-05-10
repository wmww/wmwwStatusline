
#include "statusline.h"
#include <memory>
using std::shared_ptr;

class PluginBase;

typedef shared_ptr<PluginBase> Plugin;

class PluginBase
{
public:
	
	string getJson();
	string getPlaintext();
	
	// returns requested time in seconds to next refresh (will not perfectly match delta)
	double update(double delta);
	
public:
	
	virtual double refresh(double delta) = 0;
	
	vector<string> text;
	vector<string> color; // must be the same length
	
	string jsonCache;
	string plaintextCache;
	
	static const string plaintextSeparator;
};
