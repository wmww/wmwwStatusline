#ifndef WMSTR_H
#define WMSTR_H

#include <string>
using std::string;

#include <vector>
using std::vector;

// en.wikipedia.org/wiki/UTF-8

namespace wmstr
{

/*
inline int seekForward(const string& str, int startPos, int distance)
{
	while (startPos < (int)str.size() && distance != 0)
	{
		startPos++;
		
		if ((str[startPos] & 0xC0) != 0x80)
			distance--;
	}
	
	return startPos;
}
*/

struct Itr
{
	inline Itr(const string& strIn): str(strIn)
	{}
	
	int u = -1; // the unicode position
	int b = 0; // the byte position, aka what you can use as an index to a string
	int bNext = 0; // where the next chatacter starts
	const string& str; // the string
	
	// returns true until reaches the end
	inline bool onward()
	{
		if (!isEnd())
			u++;
		
		b = bNext;
		
		if (isEnd())
			return false;
		
		do
		{
			bNext++;
			
		} while (bNext < (int)str.size() && (str[bNext] & 0xC0) == 0x80);
		
		return true;
	}
	
	inline bool backItUp()
	{
		if (!isPreStart())
			u--;
		
		bNext = b;
		
		if (isPreStart())
			return false;
		
		do
		{
			b--;
			
		} while (b > 0 && (str[b] & 0xC0) == 0x80);
		
		return true;
	}
	
	inline bool onward(int distance)
	{
		if (distance<0)
		{
			while (distance < 0)
			{
				if (!backItUp())
					return false;
				
				distance++;
			}
		}
		else
		{
			while (distance > 0)
			{
				if (!onward())
					return false;
				
				distance--;
			}
		}
		
		return true;
	}
	
	inline bool backItUp(int distance)
	{
		return onward(-distance);
	}
	
	inline Itr next()
	{
		Itr out=*this;
		out.onward();
		return out;
	}
	
	inline Itr prev()
	{
		Itr out=*this;
		out.backItUp();
		return out;
	}
	
	inline void moveTo(const Itr& other)
	{
		u = other.u;
		b = other.b;
		bNext = other.bNext;
	}
	
	inline bool isPreStart()
	{
		return bNext == 0;
	}
	
	inline bool isEnd()
	{
		return b >= (int)str.size();
	}
	
	inline bool isValid()
	{
		return b != bNext;
	}
	
	inline string get()
	{
		if (!isValid()) // if it is at the end or start
			return "";
		else
			return str.substr(b, bNext-b);
	}
	
	inline bool subMatches(const string& pattern)
	{
		return isValid() && str.size()-b >= pattern.size() && str.substr(b, pattern.size()) == pattern;
	}
};

inline Itr endOf(const string& str)
{
	Itr itr = Itr(str);
	
	while (itr.onward()) {}
	
	return itr;
}

inline Itr startOf(const string& str)
{
	Itr itr(str);
	itr.onward();
	return itr;
}

inline bool startsWith(const string& str, const string& prefix)
{
	return str.size() >= prefix.size() && str.substr(0, prefix.size()) == prefix;
}

inline bool endsWith(const string& str, const string& suffix)
{
	return str.size() >= suffix.size() && str.substr(str.size() - suffix.size(), str.npos) == suffix;
}

inline Itr find(const string& str, const string& pattern, Itr startItr)
{
	for (; !startItr.isEnd(); startItr.onward())
	{
		if (startItr.subMatches(pattern))
			break;
	}
	
	return startItr;
}

inline Itr find(const string& str, const string& pattern)
{
	return find(str, pattern, Itr(str));
}

inline string sub(Itr start, Itr end)
{
	return start.str.substr(start.b, end.b - start.b);
}

inline void splitBy(vector<string>& out, const string& str, const string& splitter = " ", bool keepEmpties = false, bool keepSplitter=false)
{
	Itr i = startOf(str);
	Itr start = i;
	Itr splitterEnd = endOf(splitter);
	
	while (true)
	{
		if (i.isEnd() || i.subMatches(splitter))
		{
			string section = sub(start, i);
			
			if (keepSplitter && !i.isEnd())
				section += splitter;
			
			i.onward(splitterEnd.u);
			
			if (keepEmpties || !section.empty())
				out.push_back(section);
			
			if (i.isEnd())
				break;
			else
				start.moveTo(i);
		}
		else
		{
			i.onward();
		}
	}
}

inline void splitBy(vector<string>& out, const string& str, vector<string>& splitters, bool keepEmpties = false, bool keepSplitter=false)
{
	Itr i = startOf(str);
	Itr start = i;
	
	while (true)
	{
		bool split = false;
		string splitter = "";
		
		if (i.isEnd())
		{
			split = true;
		}
		else
		{
			for (auto j: splitters)
			{
				if (i.subMatches(j))
				{
					split = true;
					splitter = j;
					break;
				}
			}
		}
		
		if (split)
		{
			string section = sub(start, i);
			
			if (keepSplitter)
				section += splitter;
			
			i.onward(endOf(splitter).u);
			
			if (keepEmpties || !section.empty())
				out.push_back(section);
			
			if (i.isEnd())
				break;
			else
				start.moveTo(i);
		}
		else
		{
			i.onward();
		}
	}
}

}

#endif // WMSTR_H
