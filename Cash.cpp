#include <fstream>
#include <string>
#include <iostream>

#include "Cash.h"

Cash::Cash(json& js):js(js){}
Cash::Cash(){};	
Cash::Cash(const Cash& a){
	js=a.js;
}
Cash::~Cash(){};


Cash& Cash::record(std::string time, std::string too, std::string from){ // check by id, does such file exist .... проверка по айди, есть ли такой файл
	std::string path = time + too + from + "_json_cash.json";
	std::fstream out_file(path, std::ios::out);
	if (!out_file) {
		std::cerr << "error: file not open " << path << std::endl;
		return *this;
	}
	out_file << js.dump(4);

	out_file.close();
	return *this;
}
Cash& Cash::read(std::string time, std::string too, std::string from){
	std::string path = time + too + from +"_json_cash.json";
	std::ifstream file(path, std::ios::in);

	if (!file) {
		std::cerr << "error: file not open " << path << std::endl;
		return *this;
	}
	try{
		js = json::parse(file);
	}catch(const json::parse_error& e){
		std::cerr << "error: " << e.what() << std::endl;
	}	
	file.close();
	return *this;
}

Cash& Cash::save_js(json& js){
	this->js = js;
	return *this;
}

bool Cash::is_new(std::string time, std::string too, std::string from){
	std::string path = time + too + from +"_json_cash.json";
	std::ifstream file(path, std::ios::in);
	if (!file) {
		return true;
	}
	file.close();
	return false;
}