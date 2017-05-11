#include "Plugin.h"

class CpuPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		sections.push_back("CPU:" + conversionLambda(getCpu()));
		//sections.push_back(string() + "CPU");
		return refreshRate;
	}
	
	double refreshRate = 0.25;
	
	std::function<string(double)> conversionLambda;
};

Plugin cpuPlugin(ConfigData * config)
{
	auto out = shared_ptr<CpuPlugin>(new CpuPlugin);
	
	out->refreshRate = config->get("refresh_rate").asNum(0.25);
	
	out->conversionLambda = getDoubleToStringFunc(config);
	
	return out;
}

