#include "Plugin.h"

class CpuPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		text.push_back(intToString(getCpu()*100) + "%");
		return 0.5;
	}
};

Plugin cpuPlugin()
{
	auto out = shared_ptr<CpuPlugin>(new CpuPlugin);
	
	return out;
}

