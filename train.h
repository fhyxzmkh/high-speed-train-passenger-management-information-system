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


// ����
struct Carriage {
	std::size_t seat_number;								// ��λ��
	std::vector<bool> seat;									// ��λ��
	CarriageType carrige_type;								// ��������
	std::shared_ptr<PassengerNode> passengers;				// �˿�										// ��һ�ڳ���
};

struct CarriageNode {
	Carriage value;
	std::shared_ptr<CarriageNode> next;
};


// �г�
struct Train {
	std::string code;										// �г���	
	std::shared_ptr<CarriageNode> carriages;				// ����

	std::size_t seat_count = TRAIN_SEAT_NUMBER;				// ��λ��
	std::size_t seat_available = TRAIN_SEAT_NUMBER;			// ������λ��
	std::string start_station;								// ��ʼվ
	std::string end_station;								// �յ�վ

	void printInfo();
	std::size_t findMinPassengerCarriage(std::shared_ptr<CarriageNode>& head, std::size_t type_);
	void insertPassengerNode(std::shared_ptr<CarriageNode>& carriage, Passenger& passenger);
	void deletePassengerNode(std::shared_ptr<CarriageNode>& carriage, Passenger& passenger);
	void printAllCarriages(std::shared_ptr<CarriageNode>& head);
	std::size_t getCarriageAvailableSeat(std::shared_ptr<CarriageNode>& p);
	std::size_t getCarriageUsedSeat(std::shared_ptr<CarriageNode>& p);
};

