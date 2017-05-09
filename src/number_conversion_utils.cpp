#include "number_conversion_utils.h"

string intToString(int in)
{
	string out;
	bool negative = false;
	
	if (in < 0)
	{
		negative = true;
		in *= -1;
	}
	
	while (in > 0)
	{
		out = (char)((in % 10) + '0') + out;
		in /= 10;
	}
	
	if (negative)
		out = "-" + out;
	
	return out;
}

string doubleToString(double in)
{
	long long a=in;
	long long b=(in-a)*10000000000;
	if (b<0)
		b*=-1;
	if (b%10==9)
		b+=1;
	while (b>0 && !(b%10))
		b/=10;
	return intToString(a)+"."+intToString(b);
}

int stringToInt(string in)
{
	int out = 0;
	
	for (int i = 0; i < (int)in.size(); i++)
	{
		if (in[i] >= '0' && in[i] <= '9')
		{
			out = out * 10 + in[i] - '0';
		}
		else if (in[i] == '.')
			break;
	}
	
	if (in.size() > 0 && in[0] == '-')
		out *= -1;
	
	return out;
}

double stringToDouble(string in)
{
	double out = 0;
	int divider = 1;
	
	for (int i = 0; i < (int)in.size(); i++)
	{
		if (divider == 1)
		{
			if (in[i] >= '0' && in[i] <= '9')
				out = out * 10 + in[i] - '0';
			else if (in[i] == '.')
				divider = 10;
		}
		else
		{
			if (in[i] >= '0' && in[i] <= '9')
			{
				out += (double)(in[i] - '0') / divider;
				divider *= 10;
			}
		}
	}
	
	if (in.size() > 0 && in[0] == '-')
		out *= -1;
	
	return out;
}

