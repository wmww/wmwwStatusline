#include "statusline.h"

#include "file_utils.h"

#include "number_conversion_utils.h"

using namespace wmstr;

double DataVal::asNum()
{
	return stringToDouble(data);
}

double DataVal::asNum(double defaultVal)
{
	if (data.empty())
		return defaultVal;
	else
		return asNum();
}

string DataVal::asString()
{
	return data;
}

string DataVal::asString(string defaultVal)
{
	return data.empty() ? defaultVal : data;
}

static string getNextToken(Itr& i)
{
	string out;
	
	bool hasWhitespace = false;
	
	while (true)
	{
		if (i.isEnd())
		{
			return out;
		}
		else if (i.get() == "\"")
		{
			if (out.empty())
			{
				i.onward();
				
				while (!i.isEnd() && i.get() != "\"")
				{
					out += i.get();
					i.onward();
				}
				
				i.onward();
			}
			
			return out;
		}
		else if (i.get() == ":" || i.get() == "{" || i.get() == "}")
		{
			if (out.empty())
			{
				out = i.get();
				i.onward();
			}
			
			return out;
		}
		else if (i.get() == "\n" || i.get() == "\r" || i.get() == ";")
		{
			if (out.empty())
			{
				// do nothing
			}
			else
			{
				return out;
			}
		}
		else if (i.get() == " " || i.get() == "\t")
		{
			if (!out.empty())
				hasWhitespace = true;
		}
		else
		{
			if (hasWhitespace)
			{
				out+= "_";
				hasWhitespace = false;
			}
			
			out += i.get();
		}
		
		i.onward();
	}
}

bool ConfigData::fromFile(string path, vector<ConfigData>& children)
{
	string contents;
	
	if (!loadFile(path, contents))
		return false;
	
	fromString(contents, children);
	
	return true;
}

void ConfigData::fromString(string contents, vector<ConfigData>& children)
{
	auto i = startOf(contents);
	
	vector<string> tokens;
	
	while (!i.isEnd())
	{
		string token=getNextToken(i);
		if (!token.empty())
		{
			tokens.push_back(token);
			//cout << "token [" << token << "]" << endl;
		}
	}
	
	int blockLevel = 0;
	
	ConfigData * block = this;
	
	for (int j=0; j<(int)tokens.size(); j++)
	{
		if (tokens[j] == "{")
		{
			if (blockLevel == 0)
			{
				children.push_back(ConfigData());
				block = &children.back();
			}
			
			blockLevel++;
		}
		else if (tokens[j] == "}")
		{
			blockLevel--;
			
			if (blockLevel <= 0)
			{
				blockLevel = 0;
				block = this;
			}
		}
		else if (tokens[j] != ":")
		{
			string key;
			key += tokens[j];
			string val = "";
			
			while (j+2 < (int)tokens.size() && tokens[j+1] == ":" && tokens[j+1] != "{" && tokens[j+1] != "}" )
			{
				if (!val.empty())
				{
					key += "." + val;
				}
				
				val = tokens[j + 2];
				
				j += 2;
			}
			
			if (val.empty())
				val = "null";
			
			if (!startsWith(key, "#"))
				block->addKeyVal(key, val);
		}
	}
}

string ConfigData::toString()
{
	string out;
	
	for (string key: orderedKeys)
	{
		out+=key;
		string val=data[key];
		
		if (!val.empty())
		{
			out+=": ";
			out+=val;
		}
		
		out+="\n";
	}
	
	return out;
}

bool ConfigData::toFile(string path)
{
	return writeFile(path, toString());
}

DataVal ConfigData::get(string key)
{
	auto result = data.find(key);
	
	if (result == data.end())
	{
		return DataVal("");
	}
	else
	{
		string out = result->second;
		
		if (out.empty())
			out = "null"; // this should never happen but I want to be sure
		
		return DataVal(out);
	}
}

void ConfigData::set(string key, string val)
{
	addKeyVal(key, val);
}

void ConfigData::set(string key, double val)
{
	addKeyVal(key, doubleToString(val));
}

void ConfigData::set(string key, bool val)
{
	addKeyVal(key, val ? "true" : "false");
}

void ConfigData::addKeyVal(string key, string val)
{
	if (data.find(key) == data.end())
		orderedKeys.push_back(key);
	
	data[key] = val;
	
}

void ConfigData::clear()
{
	orderedKeys.clear();
	data.clear();
}




