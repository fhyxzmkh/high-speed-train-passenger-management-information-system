#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

#include "passenger.h"
#include "CONSTANTS.h"
#include "myRandom.h"


// 车厢
struct Carriage {
	std::size_t seat_number;								// 座位数
	std::vector<bool> seat;									// 座位表
	CarriageType carrige_type;								// 车厢类型
	std::shared_ptr<PassengerNode> passengers;				// 乘客										// 下一节车厢
};

struct CarriageNode {
	Carriage value;
	std::shared_ptr<CarriageNode> next;
};


// 列车
struct Train {
	std::string code;										// 列车号	
	std::shared_ptr<CarriageNode> carriages;				// 车厢

	std::size_t seat_count = TRAIN_SEAT_NUMBER;				// 座位数
	std::size_t seat_available = TRAIN_SEAT_NUMBER;			// 可用座位数
	std::string start_station;								// 起始站
	std::string end_station;								// 终点站

	void printInfo();
	std::size_t findMinPassengerCarriage(std::shared_ptr<CarriageNode>& head, std::size_t type_);
	void insertPassengerNode(std::shared_ptr<CarriageNode>& carriage, Passenger& passenger);
	void deletePassengerNode(std::shared_ptr<CarriageNode>& carriage, Passenger& passenger);
	void printAllCarriages(std::shared_ptr<CarriageNode>& head);
	std::size_t getCarriageAvailableSeat(std::shared_ptr<CarriageNode>& p);
	std::size_t getCarriageUsedSeat(std::shared_ptr<CarriageNode>& p);
};

