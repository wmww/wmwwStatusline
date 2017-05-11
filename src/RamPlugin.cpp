
#include "Plugin.h"

double getRam();

class RamPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		sections.push_back(Section("RAM "));
		sections.push_back(Section(conversionLambda(getRam()), "", "#000000"));
		//sections.push_back(string() + "CPU");
		return refreshRate;
	}
	
	double refreshRate = 0.25;
	
	std::function<string(double)> conversionLambda;
};

Plugin ramPlugin(ConfigData * config)
{
	auto out = shared_ptr<RamPlugin>(new RamPlugin);
	
	out->refreshRate = config->get("refresh_rate").asNum(0.25);
	
	out->conversionLambda = getDoubleToStringFunc(config);
	
	return out;
}

