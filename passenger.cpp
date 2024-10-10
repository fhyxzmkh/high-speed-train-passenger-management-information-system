#include "passenger.h"

void Passenger::printInfo() {
	std::cout << "===乘客信息===" << '\n';
	std::cout << "姓名：" << this->name << '\n';
	std::cout << "身份证号：" << this->id << '\n';
	std::cout << "起始站：" << this->start_station << '\n';
	std::cout << "终点站：" << this->end_station << '\n';
	std::cout << "票价：" << this->price << '\n';
	std::cout << "车厢类型：" << this->carriage_type << '\n';
	
	if (!this->carriage_number)
		std::cout << "车厢号：待分配" << '\n';
	else
		std::cout << "车厢号：" << this->carriage_number << '\n';

	if (!this->seat_number)
		std::cout << "座位号：待分配" << '\n';
	else
		std::cout << "座位号：" << this->seat_number << '\n';
}

