#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "Api.h"

using json = nlohmann::json;
std::string Api::get_today_date(){

	std::ostringstream oss;
	std::time_t t = std::time(nullptr);
	std::tm tm = *std::localtime(&t);
	oss << (tm.tm_year + 1900) << "-" 
		<< (tm.tm_mon + 1) << "-" 
		<< tm.tm_mday;
	return oss.str();
}

Api::Api(){
	from = "c2";
	to = "c25";
	date = get_today_date();
	std::string str_transfer = transfers ? "true" : "false";
	URL = "https://api.rasp.yandex.net/v3.0/search/?format=json&from="+from+"&to="+to+"&lang=ru_RU&page=1&date="+date+"&transfers="+str_transfer;
	
} 
Api::Api(std::string time){
	from = "c2";
	to = "c25";
	date = time;
	std::string str_transfer = transfers ? "true" : "false";
	URL = "https://api.rasp.yandex.net/v3.0/search/?format=json&from="+from+"&to="+to+"&lang=ru_RU&page=1&date="+date+"&transfers="+str_transfer;
	
}
Api::Api(std::string date, std::string from, std::string too){
	from = from;
	to = to;
	date = date;
	std::string str_transfer = transfers ? "true" : "false";
	URL = "https://api.rasp.yandex.net/v3.0/search/?format=json&from="+from+"&to="+to+"&lang=ru_RU&page=1&date="+date+"&transfers="+str_transfer;
	
}
json Api::get(){
	
    cpr::Response r = cpr::Get(cpr::Url{URL}
		,cpr::Header{{"Authorization", "13574721-be54-429e-98f0-e5cdb4afd430"}}
	);
	

	return json::parse(r.text);;
}