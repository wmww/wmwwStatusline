#include "Plugin.h"

void getCpu(vector<double>& cpus);

class CpuPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		sections.push_back(Section("CPU "));
		
		vector<double> cpus;
		getCpu(cpus);
		if (cpus.empty())
			sections.push_back(Section("failed", "#ff0000", "#000000"));
		
		if (separateCores)
		{
			string out;
			
			for (auto i: cpus)
			{
				out += conversionLambda(i);
			}
			
			sections.push_back(Section(out, "", "#000000"));
		}
		else
		{
			double avg=0;
			
			for (auto i: cpus)
			{
				avg += i;
			}
			
			sections.push_back(Section(conversionLambda(avg), "", "#000000"));
		}
		
		//sections.push_back(string() + "CPU");
		return refreshRate;
	}
	
	double refreshRate = 0.25;
	
	bool separateCores = false;
	
	std::function<string(double)> conversionLambda;
};

Plugin cpuPlugin(ConfigData * config)
{
	auto out = shared_ptr<CpuPlugin>(new CpuPlugin);
	
	out->refreshRate = config->get("refresh_rate").asNum(0.25);
	out->separateCores = config->get("separate_cores").exists();
	
	out->conversionLambda = getDoubleToStringFunc(config);
	
	return out;
}

