#include "train.h"

void Train::printInfo() {
    std::cout << "ʣ����Ʊ����" << this->seat_available << '\n';
    printAllCarriages(carriages);
}

std::size_t Train::getCarriageAvailableSeat(std::shared_ptr<CarriageNode>& p) {
    return std::count(p->value.seat.begin(), p->value.seat.end(), true); // ������λ
}

std::size_t Train::getCarriageUsedSeat(std::shared_ptr<CarriageNode>& p) {
    return std::count(p->value.seat.begin(), p->value.seat.end(), false); // ������λ
}

std::size_t Train::findMinPassengerCarriage(std::shared_ptr<CarriageNode>& head, std::size_t type_) {
    CarriageType type{};
    if (type_ == 1) type = CarriageType::CARRIAGE_TYPE_FIRST_CLASS;
    else if (type_ == 2) type = CarriageType::CARRIAGE_TYPE_SECOND_CLASS;

    // ����ָ�����ͳ����п�����λ���ĳ�����
    std::size_t maxAvailableSeat{ 0 };

    
    for (auto p = head; p; p = p->next) {
        if (p->value.carrige_type != type) {
            continue; // ������ƥ��ĳ�������
        }
            
        std::size_t curAvailableSeat = getCarriageAvailableSeat(p);
        maxAvailableSeat = std::max(maxAvailableSeat, curAvailableSeat);
    }

    std::size_t idx{};
    for (auto p = head; p; p = p->next) {
        idx += 1;
        if (p->value.carrige_type != type) continue; // ������ƥ��ĳ�������

        if (maxAvailableSeat == getCarriageAvailableSeat(p))
            return idx;
        
    }

    return idx;
}

void Train::printAllCarriages(std::shared_ptr<CarriageNode>& head) {
    if (!head) {
        std::cout << "���г�������...\n";
        return;
    }

    int i{ 1 };
    for (auto p = head; p; p = p->next) {
        int seat_available_ = getCarriageAvailableSeat(p);
        std::cout << "���� " << i << " ʣ����λ����" << seat_available_ << '\n';
        i++;

        if (seat_available_ == 0) {
            std::cout << "�ó�������...\n";
            std::cout << '\n';
            continue;
        }
        else {
            std::cout << "������λ�ţ�\n";
            for (int j = 1; const auto & t : p->value.seat) {
                if (t) std::cout << j << ' ';
                j++;
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
}

void Train::insertPassengerNode(std::shared_ptr<CarriageNode>& carriage, Passenger& passenger) {
    
    if (this->seat_available == 0) {
        std::cout << "���г�����...\n";
        return;
    }
    
    auto node = std::make_shared<PassengerNode>();
    node->value = passenger;
    node->next = nullptr;

    // ����˿͵�����ĳ˿�������
    if (carriage->value.passengers == nullptr) {
        carriage->value.passengers = node;
    }
    else {
        auto tail = carriage->value.passengers;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
        tail->next = node;
    }

    // ������λ״̬
    std::size_t seat_number = randomSeatNumber(carriage->value.carrige_type);
    while (carriage->value.seat[seat_number - 1] == false) {
        seat_number = randomSeatNumber(carriage->value.carrige_type);
    }

    carriage->value.seat[seat_number - 1] = false;

    passenger.seat_number = seat_number;
}

void Train::deletePassengerNode(std::shared_ptr<CarriageNode>& carriage, Passenger& passenger) {
    if (carriage == nullptr || carriage->value.passengers == nullptr) {
        std::cout << "�ó���û�г˿�...\n";
        return;
    }

    // ���ɾ���ĳ˿��������ͷ�ڵ�
    if (carriage->value.passengers->value.id == passenger.id) {
        auto toDelete = carriage->value.passengers;
        carriage->value.passengers = toDelete->next;
        // ������λ״̬
        carriage->value.seat[passenger.seat_number - 1] = true;
        return;
    }

    // �����������Ҫɾ���ĳ˿ͽڵ�
    auto current = carriage->value.passengers;
    while (current->next != nullptr && current->next->value.id != passenger.id) {
        current = current->next;
    }

    // ����ҵ���Ҫɾ���ĳ˿ͽڵ�
    if (current->next != nullptr) {
        auto toDelete = current->next;
        current->next = toDelete->next;
        // ������λ״̬
        std::cout << "OK\n";
        carriage->value.seat[passenger.seat_number - 1] = true;
    }
    else {
        std::cout << "δ�ҵ�ָ���˿�...\n";
    }
}

