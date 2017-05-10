#include "Plugin.h"

class CpuPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		sections.push_back(intToString(getCpu()*100) + "%");
		return 0.25;
	}
};

Plugin cpuPlugin(ConfigData * config)
{
	auto out = shared_ptr<CpuPlugin>(new CpuPlugin);
	
	return out;
}

