#include <string>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


class Api{
	std::string KEY = "770597f0-e0a8-43fb-8b75-4a8f96bc2d74";
	std::string from ="c2";
	std::string to = "c25";
	std::string date = "";
	std::string URL = "";
	bool transfers = true;
	
	std::string get_today_date();	

	public:
	Api(std::string date, std::string from, std::string too);
	Api(std::string from, std::string to);
	Api();
	Api(std::string time);
	json get();	
	

};