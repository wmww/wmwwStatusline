#include "Plugin.h"

const string PluginBase::plaintextSeparator = " | ";

string PluginBase::getJson()
{
	if (jsonCache.empty())
	{
		for (int i = 0; i < (int)sections.size(); i++)
		{
			if (i)
				jsonCache += ",";
			
			jsonCache += "{";
			
			jsonCache += "\"full_text\":\"" + sections[i].text + "\"";
			
			if (!sections[i].color.empty())
			{
				jsonCache += ",\"color\":\"" + sections[i].color + "\"";
			}
			
			if (!sections[i].bknd.empty())
			{
				jsonCache += ",\"background\":\"" + sections[i].bknd + "\"";
			}
			
			if (i != (int)sections.size() - 1)
			{
				jsonCache += ",\"separator\":true,\"separator_block_width\":0";
			}
			
			jsonCache += "}";
		}
	}
	
	return jsonCache;
}

string PluginBase::getPlaintext()
{
	if (plaintextCache.empty())
	{
		for (int i = 0; i < (int)sections.size(); i++)
		{
			if (i)
				plaintextCache += plaintextSeparator;
			
			plaintextCache += sections[i].text;
		}
	}
	
	return plaintextCache;
}

double PluginBase::update(double delta)
{
	jsonCache = "";
	plaintextCache = "";
	
	sections.clear();
	
	return refresh(delta);
}

Plugin cpuPlugin(ConfigData * config);
Plugin labelPlugin(PluginBase::Section in);
Plugin labelPlugin(ConfigData * config);

Plugin PluginBase::make(ConfigData * config)
{
	string type = config->get("type").asString("missing");
	
	if (type == "missing")
	{
		return labelPlugin(PluginBase::Section("[section without type]", "#ffffff", "#ff0000"));
	}
	else if (type == "label")
	{
		return labelPlugin(config);
	}
	else if (type == "cpu")
	{
		return cpuPlugin(config);
	}
			
		//case "ram":
			
		//case "time":
			
	else
	{
		return labelPlugin(PluginBase::Section("[section with unknown type '" + type + "']", "#ffffff", "#ff0000"));
	}
}

