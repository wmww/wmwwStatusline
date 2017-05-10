
#include "statusline.h"
#include <memory>
using std::shared_ptr;

class PluginBase;

typedef shared_ptr<PluginBase> Plugin;

class PluginBase
{
public:
	
	static Plugin make(ConfigData * config);
	
	string getJson();
	string getPlaintext();
	
	// returns requested time in seconds to next refresh (will not perfectly match delta)
	double update(double delta);
	
	struct Section
	{
		string text;
		string color;
		string bknd;
		
		Section(string textIn = "[no text]", string colorIn = "", string bkndIn = "")
		{
			text = textIn;
			color = colorIn;
			bknd = bkndIn;
		}
	};
	
public:
	
	virtual double refresh(double delta) = 0;
	
	vector<Section> sections;
	
	string jsonCache;
	string plaintextCache;
	
	static const string plaintextSeparator;
};

