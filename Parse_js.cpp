#include "Parse_js.h" 

#include <iostream>

Parse_js::Parse_js(json& js): js(js){}

Parse_js::Parse_js(){}
Parse_js::~Parse_js(){}

void Parse_js::parse()
{
	if (!js.contains("segments") || js["segments"].empty()) {
        std::cerr << "В ответе отсутствуют сегменты!" << std::endl;
        return;
    }

	for (const auto&  segment : js["segments"])
	{
		thread t;
		
		if (segment["has_transfers"].get<bool>() == true){

			t.transfer = true;
			if (segment.contains("details") && segment["details"].is_array()) {
				
				for (const auto& detail : segment["details"]) {

					sub_thread st;
					if(detail.contains("arrival")){
						st.arrival_time = detail["arrival"];
					}
					if(detail.contains("departure")){
						st.departure_time = detail["departure"];
					}
					if(detail.contains("thread")){
						st.thread = detail["thread"]["title"];
						st.type = detail["thread"]["transport_type"];
					}

					st.time_in_way = st.calculate_travel_time(st);

					if(st.arrival_time != "" && st.departure_time != "" && st.thread != "" && st.type != ""){
						t.sub_threads.push_back(st);
					}
				
				}
			} else {
				std::cerr << "No 'details' field found or it is not an array" << std::endl;
			}
			

		} else {
			sub_thread st;	

			if(segment.contains("arrival")){
				st.arrival_time = segment["arrival"];
			}
			if(segment.contains("departure")){
				st.departure_time = segment["departure"];
			}
			if(segment.contains("thread")){
				st.thread = segment["thread"]["title"];
				st.type = segment["thread"]["transport_type"];
			}
			st.time_in_way = st.calculate_travel_time(st);

			t.sub_threads.push_back(st);
		}
		threads.push_back(t);

	}
}
void Parse_js::print(){
	
	for (size_t i = 0; i < threads.size(); i++) {
		std::cout << "==============================\n";
		std::cout << "Transfer " << i + 1 << ":\n";
		std::cout << "==============================\n";
		for (const auto& sub_item : threads[i].sub_threads) {
			std::cout << "🚆 Thread: " << sub_item.thread << "\n";
			std::cout << "⏳ Time in way: " << sub_item.time_in_way << "\n";
			std::cout << "📅 Departure: " << sub_item.departure_time << "\n";
			std::cout << "📅 Arrival: " << sub_item.arrival_time << "\n";
			std::cout << "------------------------------\n";
		}
		std::cout << std::endl;
	}
}

std::string sub_thread::calculate_travel_time(sub_thread& train) {
    if (!train.time_in_way.empty()) {
        return train.time_in_way;
    }

    std::tm dep = {};
    std::tm arr = {};
    std::istringstream dep_ss(train.departure_time);
    std::istringstream arr_ss(train.arrival_time);

    dep_ss >> std::get_time(&dep, "%Y-%m-%dT%H:%M:%S");
    arr_ss >> std::get_time(&arr, "%Y-%m-%dT%H:%M:%S");

    std::time_t dep_time = std::mktime(&dep);
    std::time_t arr_time = std::mktime(&arr);

    if (dep_time == -1 || arr_time == -1 || arr_time < dep_time) {
        return "Invalid time";
    }

    int duration = static_cast<int>(arr_time - dep_time);
    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;

    std::ostringstream result;
    result << hours << "h " << minutes << "m";
    train.time_in_way = result.str();
    return train.time_in_way;
}