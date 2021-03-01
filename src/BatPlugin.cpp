
#include "Plugin.h"

double getNumberFromFile(string const&);
unsigned int getEnumFromFile(std::vector<std::pair<unsigned int, string>> const&, string const&);

enum BatState
{
    BAT_STATE_INVALID = 0,
    BAT_STATE_UNKNOWN,
    BAT_STATE_DISCHARGING,
    BAT_STATE_CHARGING,
    BAT_STATE_FULL,
};

const std::vector<std::pair<unsigned int, string>> batStates = {
    {BAT_STATE_UNKNOWN, "Unknown\n"},
    {BAT_STATE_DISCHARGING, "Discharging\n"},
    {BAT_STATE_CHARGING, "Charging\n"},
    {BAT_STATE_FULL, "Full\n"},
};

class BatPlugin: public PluginBase
{
public:
	double refresh(double delta)
    try
	{
        if (chargeFull == 0)
        {
            chargeFull = getNumberFromFile(prefix + "charge_full");
        }
        double chargeNow = getNumberFromFile(prefix + "charge_now");
        double bat = chargeNow / chargeFull;
        BatState state = (BatState)getEnumFromFile(batStates, prefix + "status");

		string color = "";
        string labelColor = "";

        switch (state)
        {
            case BAT_STATE_INVALID:
                color = "#FFa000";
                break;
            case BAT_STATE_UNKNOWN:
            case BAT_STATE_DISCHARGING:
                if (bat <= warningLevel)
                {
                    color = "#ff0000";
                    labelColor = "#ff0000";
                    bat = warningLevel / bat;
                }
                else
                {
                    color = "";
                }
                break;
            case BAT_STATE_CHARGING:
                color = "#00ff00";
                break;
            case BAT_STATE_FULL:
                color = "#b0b0b0";
                break;
        }

		sections.push_back(Section("BAT ", labelColor));
		sections.push_back(Section(conversionLambda(bat), color, "#000000"));

		return refreshRate;
	}
	catch (const std::exception& e)
    {
        sections.push_back(Section("ERROR: " + string(e.what()), "#FF0000"));
        return refreshRate;
    }

    string prefix = "/sys/class/power_supply/BAT0/";
	double refreshRate = 1;
	double warningLevel = 0.1;
    double chargeFull = 0;
	std::function<string(double)> conversionLambda;
};

Plugin batPlugin(ConfigData * config)
{
	auto out = shared_ptr<BatPlugin>(new BatPlugin);

	out->refreshRate = config->get("refresh_rate").asNum(1);
	out->warningLevel = config->get("warning_level").asNum(0.1);
	out->conversionLambda = getDoubleToStringFunc(config);

	return out;
}

