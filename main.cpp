#include <iostream>
#include <string>
#include <fstream>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "Api.h"
#include "Cash.h"
#include "Parse_js.h"


using json = nlohmann::json;


std::string convert_to_iso8601(const std::string& date) {
	
    std::istringstream date_stream(date);
    int day, month, year;
    char dot1, dot2;
    if (date_stream >> day >> dot1 >> month >> dot2 >> year && dot1 == '.' && dot2 == '.') {
        std::ostringstream iso_date;
        iso_date << year << "-" 
                 << std::setw(2) << std::setfill('0') << month << "-" 
                 << std::setw(2) << std::setfill('0') << day;
        return iso_date.str();
    }
	std::cerr << "Invalid date format\n";
    return "Invalid date format";
}

int main() {

	
	std::system("chcp 65001");
	std::string time = "2021-06-01";

	
	while (true)
	{
		std::string time, from, too;
		
		std::cout<<"Input date (format <day.month.year>)\n city sity \nfinsh city\n(for exit <-1>): \n";
		std::cin>>time;
	
		if(time == "-1")
		{
			break;
		}
		std::cin>>from>>too;

		time=convert_to_iso8601(time);
		if(time == "Invalid date format\n") continue;
		
		Cash ch;
		json js;
		if(ch.is_new(time, from, too))
		{
			Api api(time, from, too);
			js = api.get();
			ch.save_js(js).record(time, from, too);
		}else
		{
			js = ch.read(time, from, too).js;
		}
		
		ch.record(time, from, too);
	
		Parse_js p(js);
		p.parse();
		p.print();
		
	}	

    return 0;
}






