#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "myRandom.h"

struct Passenger {
	std::string id;					// 身份证号
	std::string name;				// 姓名

	std::string start_station;		// 起始站
	std::string end_station;		// 终点站
	std::size_t price;				// 票价
	std::size_t carriage_type;		// 车厢类型
	std::size_t carriage_number;	// 车厢号
	std::size_t seat_number;		// 座位号

	void printInfo();
};

struct PassengerNode {
	Passenger value;
	std::shared_ptr<PassengerNode> next;
};