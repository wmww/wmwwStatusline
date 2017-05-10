#include <unordered_map>

class DataVal
{
public:
	DataVal(string in) {data = in;}
	
	double asNum();
	double asNum(double defaultVal);
	
	string asString();
	string asString(string defaultVal);
	
	bool exists() {return !data.empty();}
	
private:
	
	string data;
};

class ConfigData
{
public:
	
	// returnes false if failed
	bool fromFile(string path, vector<ConfigData>& children);
	void fromString(string contents, vector<ConfigData>& children);
	string toString();
	bool toFile(string path);
	
	DataVal get(string key);
	void set(string key, string val);
	void set(string key, double val);
	void set(string key, bool val);
	
	void clear();
	
private:
	
	void addKeyVal(string key, string val);
	
	vector<string> orderedKeys;
	std::unordered_map<string, string> data;
};

