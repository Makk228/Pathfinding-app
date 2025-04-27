#include <string>
#include <vector>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
/*
struct 1
тип перевозки
станция отправления
станция прибытия
время отправления
время прибытия

struct 2
есть ли пересадка
вектор с маршрутом вида <начало - пересадка - конец>
*/
struct sub_thread
{
	std::string type;
	
	std::string thread;
	std::string departure_time;
	std::string arrival_time;
	std::string time_in_way; //

	std::string calculate_travel_time(sub_thread& train);
};

struct thread
{
	bool transfer;
	std::vector<sub_thread> sub_threads;
};

class Parse_js
{
	json js;

public:
	std::vector<thread> threads; 
	Parse_js(json& js);
	~Parse_js();
	Parse_js();
	void parse();
	void print();
};