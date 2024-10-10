#pragma once

// ��������
enum class CarriageType {
	CARRIAGE_TYPE_FIRST_CLASS = 1,		// һ��
	CARRIAGE_TYPE_SECOND_CLASS = 2,		// ����
};

// �궨Ʊ��
constexpr std::size_t SECOND_CLASS_SEAT_PRICE = 150;
constexpr std::size_t FIRST_CLASS_SEAT_PRICE = SECOND_CLASS_SEAT_PRICE + 100;

// �궨��λ��
constexpr std::size_t MAX_FIRST_CLASS_SEAT = 5;
constexpr std::size_t MAX_SECOND_CLASS_SEAT = 9;

// �궨������
constexpr std::size_t FIRST_CLASS_CARRIAGE_NUM = 2;
constexpr std::size_t SECOND_CLASS_CARRIAGE_NUM = 3;
constexpr std::size_t MAX_CARRIAGE_NUM = FIRST_CLASS_CARRIAGE_NUM + SECOND_CLASS_CARRIAGE_NUM;

// �г�����λ��
constexpr std::size_t TRAIN_SEAT_NUMBER = FIRST_CLASS_CARRIAGE_NUM * MAX_FIRST_CLASS_SEAT + SECOND_CLASS_CARRIAGE_NUM * MAX_SECOND_CLASS_SEAT;

// ;��վ��
constexpr std::size_t STATION_NUM = 6;

const std::pair<std::string, std::size_t> STATIONS[STATION_NUM]{
	std::make_pair("Shanghai", 0),
	std::make_pair("Suzhou", 1),
	std::make_pair("Nanjing", 2),
	std::make_pair("Jinan", 3),
	std::make_pair("Tianjing", 4),
	std::make_pair("Beijing", 5),
};
