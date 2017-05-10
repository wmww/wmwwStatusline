#include "Plugin.h"

const string PluginBase::plaintextSeparator = " | ";

string PluginBase::getJson()
{
	if (jsonCache.empty())
	{
		for (int i = 0; i < (int)text.size(); i++)
		{
			if (i)
				jsonCache += ",";
			
			jsonCache += "{";
			
			jsonCache += "\"full_text\":\"" + text[i] + "\"";
			
			if (text.size() == color.size() && !color[i].empty())
			{
				jsonCache += ",\"color\":\"" + color[i] + "\"";
			}
			
			if (i != (int)text.size() - 1)
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
		for (int i = 0; i < (int)text.size(); i++)
		{
			if (i)
				plaintextCache += plaintextSeparator;
			
			plaintextCache += text[i];
		}
	}
	
	return plaintextCache;
}

double PluginBase::update(double delta)
{
	jsonCache = "";
	plaintextCache = "";
	
	return refresh(delta);
}
