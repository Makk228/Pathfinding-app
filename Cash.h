#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Cash{  // from to time
	public:
	json js;
	Cash(json& js);
	Cash(const Cash& a);
	Cash();
	~Cash();
	Cash&  save_js(json& js);
	Cash& record(std::string time, std::string too, std::string from);
	Cash& read(std::string time, std::string too, std::string from);
	bool is_new(std::string time, std::string too, std::string from);
};