
#include "Plugin.h"

double getRam();

class RamPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		double ram = getRam();
		
		string color = "";
		
		if (ram > warningLevel)
			color = "#ff0000";
		
		sections.push_back(Section("RAM ", color));
		
		sections.push_back(Section(conversionLambda(ram), color, "#000000"));
		
		//sections.push_back(string() + "CPU");
		return refreshRate;
	}
	
	double refreshRate = 0.25;
	
	double warningLevel = 1.5;
	
	std::function<string(double)> conversionLambda;
};

Plugin ramPlugin(ConfigData * config)
{
	auto out = shared_ptr<RamPlugin>(new RamPlugin);
	
	out->refreshRate = config->get("refresh_rate").asNum(0.25);
	
	out->warningLevel = config->get("warning_level").asNum(1.5);
	
	out->conversionLambda = getDoubleToStringFunc(config);
	
	return out;
}

