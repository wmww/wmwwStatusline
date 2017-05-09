#include <unordered_map>

class PersistentData
{
public:
	
	// returnes false if failed
	bool fromFile(string path, string prefix);
	void fromString(string contents, string prefix);
	string toString();
	bool toFile(string path);
	
	string get(string key);
	void set(string key, string val);
	
private:
	
	vector<string> orderedKeys;
	std::unordered_map<string, string> data;
};

