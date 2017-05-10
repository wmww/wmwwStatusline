#include "Plugin.h"

class TimePlugin: public PluginBase
{
public:
	
	TimePlugin(ConfigData * config)
	{
		format = config->get("format").asString("%I:%M %p");
	}
	
	double refresh(double delta)
	{
		sections.push_back(getTime(format));
		return 1;
	}
	
	string format;
};

Plugin timePlugin(ConfigData * config)
{
	return Plugin(new TimePlugin(config));
}



