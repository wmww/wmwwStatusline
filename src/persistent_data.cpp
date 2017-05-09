#include "statusline.h"

#include "file_utils.h"

#include "number_conversion_utils.h"

double DataVal::asNum()
{
	return stringToDouble(data);
}

string DataVal::asString()
{
	return data;
}

static string getNextToken(const string& data, int& i)
{
	string out;
	
	while (true)
	{
		if (i>=(int)data.size())
		{
			return out;
		}
		else if (data[i]==':')
		{
			if (out.empty())
			{
				i++;
				return string()+data[i-1];
			}
			else
			{
				return out;
			}
		}
		else if (data[i]=='\n' || data[i]=='\r' || data[i]==';')
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
		else if (data[i]==' ' || data[i]=='\t')
		{
			// do nothing
		}
		else
		{
			out+=data[i];
		}
		
		i++;
	}
}

bool PersistentData::fromFile(string path, string prefix)
{
	string contents;
	
	if (!loadFile(path, contents))
		return false;
	
	fromString(contents, prefix);
	
	return true;
}

void PersistentData::fromString(string contents, string prefix)
{
	int i=0;
	
	vector<string> tokens;
	
	while (i<(int)contents.size())
	{
		string token=getNextToken(contents, i);
		if (!token.empty())
		{
			tokens.push_back(token);
			//cout << "token [" << token << "]" << endl;
		}
	}
	
	for (int j=0; j<(int)tokens.size(); j++)
	{
		if (tokens[j] != ":")
		{
			string key;
			if (!prefix.empty())
				key += prefix + ".";
			key += tokens[j];
			string val = "";
			
			while (j+2<(int)tokens.size() && tokens[j+1]==":")
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
			
			addKeyVal(key, val);
		}
	}
}

string PersistentData::toString()
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

bool PersistentData::toFile(string path)
{
	return writeFile(path, toString());
}

DataVal PersistentData::get(string key)
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

void PersistentData::set(string key, string val)
{
	addKeyVal(key, val);
}

void PersistentData::set(string key, double val)
{
	addKeyVal(key, doubleToString(val));
}

void PersistentData::set(string key, bool val)
{
	addKeyVal(key, val ? "true" : "false");
}

void PersistentData::addKeyVal(string key, string val)
{
	if (data.find(key) == data.end())
		orderedKeys.push_back(key);
	
	data[key] = val;
	
}





