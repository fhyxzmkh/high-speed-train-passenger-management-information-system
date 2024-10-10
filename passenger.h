#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "myRandom.h"

struct Passenger {
	std::string id;					// ���֤��
	std::string name;				// ����

	std::string start_station;		// ��ʼվ
	std::string end_station;		// �յ�վ
	std::size_t price;				// Ʊ��
	std::size_t carriage_type;		// ��������
	std::size_t carriage_number;	// �����
	std::size_t seat_number;		// ��λ��

	void printInfo();
};

struct PassengerNode {
	Passenger value;
	std::shared_ptr<PassengerNode> next;
};