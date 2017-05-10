#include "Plugin.h"

class LabelPlugin: public PluginBase
{
public:
	double refresh(double delta)
	{
		sections.push_back(section);
		return 120;
	}
	
	Section section;
};

Plugin labelPlugin(PluginBase::Section in)
{
	auto out = shared_ptr<LabelPlugin>(new LabelPlugin());
	
	out->section = in;
	out->update(0);
	
	return out;
}

Plugin labelPlugin(ConfigData * config)
{
	auto out = shared_ptr<LabelPlugin>(new LabelPlugin());
	
	out->section.text = config->get("text").asString("[no text provided]");
	out->section.color = config->get("color").asString("");
	out->section.bknd = config->get("background").asString("");
	out->update(0);
	
	return out;
}


