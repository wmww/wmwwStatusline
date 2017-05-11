#include "Plugin.h"

class CpuPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		sections.push_back("CPU" + horizontalBar(getCpu(), 3));
		//sections.push_back(string() + "CPU");
		return refreshRate;
	}
	
	double refreshRate = 0.25;
};

Plugin cpuPlugin(ConfigData * config)
{
	auto out = shared_ptr<CpuPlugin>(new CpuPlugin);
	
	out->refreshRate = config->get("refresh_rate").asNum(0.25);
	
	return out;
}

