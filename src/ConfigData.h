#include <unordered_map>

class DataVal
{
public:
	DataVal(string in) {data = in;}
	
	double asNum();
	
	string asString();
	
	bool exists() {return !data.empty();}
	
private:
	
	string data;
};

class ConfigData
{
public:
	
	// returnes false if failed
	bool fromFile(string path, string prefix);
	void fromString(string contents, string prefix);
	string toString();
	bool toFile(string path);
	
	DataVal get(string key);
	void set(string key, string val);
	void set(string key, double val);
	void set(string key, bool val);
	
private:
	
	void addKeyVal(string key, string val);
	
	vector<string> orderedKeys;
	std::unordered_map<string, string> data;
};

