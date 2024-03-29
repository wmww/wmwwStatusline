
#include "Plugin.h"

bool pathExists(string const& path);
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
        if (prefix.empty())
        {
            for (const string& path : std::vector<string>{
                "/sys/class/power_supply/BAT0/", // default
                "/sys/class/power_supply/max170xx_battery/", // GPD pocket
                })
            {
                if (pathExists(path))
                {
                    prefix = path;
                    break;
                }
            }
            if (prefix.empty())
            {
                sections.push_back(Section("NO BAT", ""));
                return refreshRate;
            }
        }
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
                else if (bat <= alertLevel)
                {
                    color = "#a0a000";
                    labelColor = "#a0a000";
                }
                else
                {
                    color = "#00ff00";
                    labelColor = "#00ff00";
                }
                break;
            case BAT_STATE_CHARGING:
                color = "#ffffff";
                break;
            case BAT_STATE_FULL:
                color = "";
                break;
        }

		sections.push_back(Section("BAT ", labelColor));
		sections.push_back(Section(conversionLambda(bat), color, "#000000"));

		return refreshRate;
	}
	catch (const std::exception& e)
    {
        sections.push_back(Section("ERROR: " + string(e.what()), "#FF0000"));
        prefix = "";
        return refreshRate;
    }

    string prefix = "";
	double refreshRate = 1;
	double warningLevel = 0.1;
	double alertLevel = 0.5;
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

