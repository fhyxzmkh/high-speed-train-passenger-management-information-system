#include "passenger.h"

void Passenger::printInfo() {
	std::cout << "===�˿���Ϣ===" << '\n';
	std::cout << "������" << this->name << '\n';
	std::cout << "���֤�ţ�" << this->id << '\n';
	std::cout << "��ʼվ��" << this->start_station << '\n';
	std::cout << "�յ�վ��" << this->end_station << '\n';
	std::cout << "Ʊ�ۣ�" << this->price << '\n';
	std::cout << "�������ͣ�" << this->carriage_type << '\n';
	
	if (!this->carriage_number)
		std::cout << "����ţ�������" << '\n';
	else
		std::cout << "����ţ�" << this->carriage_number << '\n';

	if (!this->seat_number)
		std::cout << "��λ�ţ�������" << '\n';
	else
		std::cout << "��λ�ţ�" << this->seat_number << '\n';
}

