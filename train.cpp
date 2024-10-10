#include "train.h"

void Train::printInfo() {
    std::cout << "剩余总票数：" << this->seat_available << '\n';
    printAllCarriages(carriages);
}

std::size_t Train::getCarriageAvailableSeat(std::shared_ptr<CarriageNode>& p) {
    return std::count(p->value.seat.begin(), p->value.seat.end(), true); // 可用座位
}

std::size_t Train::getCarriageUsedSeat(std::shared_ptr<CarriageNode>& p) {
    return std::count(p->value.seat.begin(), p->value.seat.end(), false); // 已用座位
}

std::size_t Train::findMinPassengerCarriage(std::shared_ptr<CarriageNode>& head, std::size_t type_) {
    CarriageType type{};
    if (type_ == 1) type = CarriageType::CARRIAGE_TYPE_FIRST_CLASS;
    else if (type_ == 2) type = CarriageType::CARRIAGE_TYPE_SECOND_CLASS;

    // 返回指定类型车厢中可用座位最多的车厢编号
    std::size_t maxAvailableSeat{ 0 };

    
    for (auto p = head; p; p = p->next) {
        if (p->value.carrige_type != type) {
            continue; // 跳过不匹配的车厢类型
        }
            
        std::size_t curAvailableSeat = getCarriageAvailableSeat(p);
        maxAvailableSeat = std::max(maxAvailableSeat, curAvailableSeat);
    }

    std::size_t idx{};
    for (auto p = head; p; p = p->next) {
        idx += 1;
        if (p->value.carrige_type != type) continue; // 跳过不匹配的车厢类型

        if (maxAvailableSeat == getCarriageAvailableSeat(p))
            return idx;
        
    }

    return idx;
}

void Train::printAllCarriages(std::shared_ptr<CarriageNode>& head) {
    if (!head) {
        std::cout << "该列车不存在...\n";
        return;
    }

    int i{ 1 };
    for (auto p = head; p; p = p->next) {
        int seat_available_ = getCarriageAvailableSeat(p);
        std::cout << "车厢 " << i << " 剩余座位数：" << seat_available_ << '\n';
        i++;

        if (seat_available_ == 0) {
            std::cout << "该车厢已满...\n";
            std::cout << '\n';
            continue;
        }
        else {
            std::cout << "可用座位号：\n";
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
        std::cout << "该列车已满...\n";
        return;
    }
    
    auto node = std::make_shared<PassengerNode>();
    node->value = passenger;
    node->next = nullptr;

    // 插入乘客到车厢的乘客链表中
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

    // 更新座位状态
    std::size_t seat_number = randomSeatNumber(carriage->value.carrige_type);
    while (carriage->value.seat[seat_number - 1] == false) {
        seat_number = randomSeatNumber(carriage->value.carrige_type);
    }

    carriage->value.seat[seat_number - 1] = false;

    passenger.seat_number = seat_number;
}

void Train::deletePassengerNode(std::shared_ptr<CarriageNode>& carriage, Passenger& passenger) {
    if (carriage == nullptr || carriage->value.passengers == nullptr) {
        std::cout << "该车厢没有乘客...\n";
        return;
    }

    // 如果删除的乘客是链表的头节点
    if (carriage->value.passengers->value.id == passenger.id) {
        auto toDelete = carriage->value.passengers;
        carriage->value.passengers = toDelete->next;
        // 更新座位状态
        carriage->value.seat[passenger.seat_number - 1] = true;
        return;
    }

    // 遍历链表查找要删除的乘客节点
    auto current = carriage->value.passengers;
    while (current->next != nullptr && current->next->value.id != passenger.id) {
        current = current->next;
    }

    // 如果找到了要删除的乘客节点
    if (current->next != nullptr) {
        auto toDelete = current->next;
        current->next = toDelete->next;
        // 更新座位状态
        std::cout << "OK\n";
        carriage->value.seat[passenger.seat_number - 1] = true;
    }
    else {
        std::cout << "未找到指定乘客...\n";
    }
}

