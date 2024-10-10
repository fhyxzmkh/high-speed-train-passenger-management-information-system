#include "menu.h"

std::string currentStation = STATIONS[0].first;
bool isRuning = false;
BstTree tree;

void mainMenu(Train& t) {
    std::cout << "\n欢迎使用高铁列车旅客管理信息系统..." << '\n';
    std::cout << "==============菜单===============" << '\n';
    std::cout << "1、查询信息" << '\n';
    std::cout << "2、购票" << '\n';
    std::cout << "3、手动补票" << '\n';
    std::cout << "4、退票" << '\n';
    std::cout << "5、启动列车" << '\n';
    std::cout << "6、前往下一站" << '\n';
    std::cout << "7、统计" << '\n';
    std::cout << "8、退出" << '\n';

    int opt{};

    std::cout << "\n请输入选项：";
    std::cin >> opt;
    std::cout << "" << '\n';

    switch (opt) {
    case 1:
        system("cls");

        while (requireMenu(t));
        break;
    case 2:
        system("cls");

        if (isRuning) {
            std::cout << "列车运行中，无法购票,请前往补票...\n";
            break;
        }
        sellticket(t);
        break;
    case 3:
        system("cls");

        manualPurchaseTicket(t);
        break;
    case 4:
        system("cls");

        if (isRuning) {
            std::cout << "列车运行中，无法退票...\n";
            break;
        }
        
        bounceTicket(t);
        break;
    case 5:
        system("cls");

        if (isRuning) {
            std::cout << "列车已启动...\n";
            break;
        }
        else {
            isRuning = true;
            passengerGetIn(t);
        }
        
        break;
    case 6:
        system("cls");

        if (currentStation == "Beijing") {
            std::cout << "已到达终点站，无法前往下一站！\n";
            break;
        }

        if (!isRuning) {
            std::cout << "请先启动列车...\n";
            break;
        }

        arriveNextStation();
        if (currentStation == "Beijing")
            isRuning = false;
        passengerGetOut(t);
        passengerGetIn(t);
        break;
    case 7:
        system("cls");

        if (isRuning) {
            std::cout << "列车运行中，暂时无法查看数据...\n";
            break;
        }
        countTrainInfo(t);
        break;
    case 8:
        exit(0);
    default:
        break;
    }

}


bool requireMenu(Train& t) {
    std::cout << "\n=====查询菜单=====\n";
    std::cout << "1、查询列车信息" << '\n';
    std::cout << "2、查询当前站点" << '\n';
    std::cout << "3、查询下一站点" << '\n';
    std::cout << "4、查询所有购票乘客" << '\n';
    std::cout << "5、查询当前站点上下车旅客数" << '\n';
    std::cout << "6、查询下一站点上下车旅客数" << '\n';
    std::cout << "7、返回主菜单" << '\n';

    int opt{};

    std::cout << "\n请输入选项：";
    std::cin >> opt;
    std::cout << "" << '\n';

    switch (opt)
    {
    case 1:
        system("cls");

        t.printInfo();
        break;
    case 2:
        system("cls");

        std::cout << "当前站点：" << currentStation << '\n';
        break;
    case 3:
        system("cls");

        if (getNextStation().empty()) std::cout << "当前为终点站，无下一站！\n";
        else std::cout << "下一站为：" << getNextStation() << '\n';
        break;
    case 4:
        system("cls");

        tree.inorder();
        break;
    case 5:
        system("cls");

        if (currentStation == "Shanghai") {
            std::cout << "当前站为始发站，无下车信息！" << '\n';
            std::cout << "当前站点上车人数：" << getCurrentStationGetInNum() << '\n';
            break;
        }
        std::cout << "当前站点上车人数：" << getCurrentStationGetInNum() << '\n';
        std::cout << "当前站点下车人数：" << getCurrentStationGetOutNum() << '\n';
        break;
    case 6:
        system("cls");

        if (getNextStation().empty()) {
            std::cout << "已到达终点站，无下一站！" << '\n';
            break;
        }
        std::cout << "下一站为：" << getNextStation() << '\n';
        std::cout << "下一站点上车人数：" << getNextStationGetInNum() << '\n';
        std::cout << "下一站点下车人数：" << getNextStationGetOutNum() << '\n';
        break;
    case 7:
        return false;
    default:
        break;
    }

    return true;
}

Passenger createPassenger() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Passenger p;
    p.id = randomID(4);
    p.name = randomName(3);

    auto stations_ = randomStation();
    p.start_station = stations_.first;
    p.end_station = stations_.second;

    auto type_ = randomCarriageType();
    if (type_ == CarriageType::CARRIAGE_TYPE_FIRST_CLASS)
        p.carriage_type = 1;
    else
        p.carriage_type = 2;

    int a_{}, b_{};
    for (const auto& station : STATIONS) {
        if (station.first == stations_.first) a_ = station.second;
        if (station.first == stations_.second) b_ = station.second;
    }
    p.price = static_cast<size_t>(std::abs(a_ - b_)) * (type_ == CarriageType::CARRIAGE_TYPE_FIRST_CLASS ? FIRST_CLASS_SEAT_PRICE : SECOND_CLASS_SEAT_PRICE);

    p.carriage_number = 0; // 此时还未确定
    p.seat_number = 0; // 此时还未确定

    return p;
}

void insertCarriageNode(std::shared_ptr<CarriageNode>& head, std::shared_ptr<CarriageNode>& tail, Carriage c) {
    auto node = std::make_shared<CarriageNode>();
    node->value = c;
    node->next = nullptr;

    if (head == nullptr) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }
}

std::shared_ptr<CarriageNode> createCarriage() {
    const Carriage carriages_[MAX_CARRIAGE_NUM]{
        { MAX_FIRST_CLASS_SEAT, std::vector<bool>(MAX_FIRST_CLASS_SEAT, true), CarriageType::CARRIAGE_TYPE_FIRST_CLASS, nullptr},
        { MAX_FIRST_CLASS_SEAT, std::vector<bool>(MAX_FIRST_CLASS_SEAT, true), CarriageType::CARRIAGE_TYPE_FIRST_CLASS, nullptr },
        { MAX_SECOND_CLASS_SEAT, std::vector<bool>(MAX_SECOND_CLASS_SEAT, true), CarriageType::CARRIAGE_TYPE_SECOND_CLASS, nullptr },
        { MAX_SECOND_CLASS_SEAT, std::vector<bool>(MAX_SECOND_CLASS_SEAT, true), CarriageType::CARRIAGE_TYPE_SECOND_CLASS, nullptr },
        { MAX_SECOND_CLASS_SEAT, std::vector<bool>(MAX_SECOND_CLASS_SEAT, true), CarriageType::CARRIAGE_TYPE_SECOND_CLASS, nullptr },
    };

    std::shared_ptr<CarriageNode> carriages{};
    std::shared_ptr<CarriageNode> tail{};

    for (const auto& c : carriages_)
        insertCarriageNode(carriages, tail, c);

    return carriages;
}

void insertPassengerToCarriage(Passenger& p_, Train& t_) {
    std::size_t idx = t_.findMinPassengerCarriage(t_.carriages, p_.carriage_type);
    p_.carriage_number = idx;

    auto carriage = t_.carriages;
    for (int i = 1; i < idx; ++i) {
        carriage = carriage->next;
    }

    // 插入乘客到车厢中
    t_.insertPassengerNode(carriage, p_);
}

void delPassengerFromCarriage(Passenger& p_, Train& t_) {
    std::size_t idx = p_.carriage_number;
    std::cout << "idx: " << idx << std::endl;

    auto carriage = t_.carriages;
    for (int i = 1; i < idx; ++i) {
        carriage = carriage->next;
    }

    t_.deletePassengerNode(carriage, p_);
}

bool isValidStation(std::string ss, std::string es)
{
    int a = -1, b = -1, c = -1;
    for (const auto& station : STATIONS) {
        if (station.first == ss) {
            a = station.second;
            break;
		}
	}
    for (const auto& station : STATIONS) {
        if (station.first == es) {
            b = station.second;
            break;
        }
    }
    for (const auto& station : STATIONS) {
        if (station.first == currentStation) {
            c = station.second;
            break;
        }
    }
    return a > -1 && b > -1 && a < b && (a > c || (a == c && !c && !isRuning)) && b < 6;
}

void sellticket(Train& t) {
    if (t.seat_available <= 0) {
        std::cout << "当前列车已满员，请等候下一列...\n";
        return;
    }
        
    Passenger p = createPassenger();
    
    if (tree.searchPassengerById(p.id)) {
        std::cout << "请勿重复购票！\n";
        return;
    }

    t.seat_available -= 1;
    std::cout << "购票成功！当前剩余票数：" << t.seat_available << '\n';

    p.printInfo();

    // 插入乘客到列车二叉排序树中
    auto pNode = std::make_shared<PassengerNode>();

    pNode->value.id = p.id;
    pNode->value.name = p.name;
    pNode->value.start_station = p.start_station;
    pNode->value.end_station = p.end_station;
    pNode->value.price = p.price;
    pNode->value.carriage_type = p.carriage_type;
    pNode->value.carriage_number = p.carriage_number;
    pNode->value.seat_number = p.seat_number;

    tree.insert(pNode->value.price, pNode);
    
}

void manualPurchaseTicket(Train& t) {
    if (t.seat_available <= 0) {
        std::cout << "当前列车已满员，无法补票...\n";
        return;
    }

    Passenger p;
    std::cout << "请输入乘客姓名：";
    std::cin >> p.name;
    std::cout << "请输入乘客ID：";
    std::cin >> p.id;

    if (tree.searchPassengerById(p.id)) {
        std::cout << "请勿重复购票！\n";
        return;
    }

    std::cout << "请输入乘客起始站：";
    std::cin >> p.start_station;
    std::cout << "请输入乘客终点站：";
    std::cin >> p.end_station;

    if (!isValidStation(p.start_station, p.end_station)) {
        std::cout << "非法的站点信息！\n";
        return;
    }

    std::cout << "请输入车厢等第(一等：1 二等：2)：";
    std::cin >> p.carriage_type;

    int a_{}, b_{};
    for (const auto& station : STATIONS) {
        if (station.first == p.start_station) a_ = station.second;
        if (station.first == p.end_station) b_ = station.second;
    }
    p.price = static_cast<size_t>(std::abs(a_ - b_)) * (p.carriage_type == 1 ? FIRST_CLASS_SEAT_PRICE : SECOND_CLASS_SEAT_PRICE);

    p.carriage_number = 0; // 此时还未确定
    p.seat_number = 0; // 此时还未确定

    p.printInfo();

    t.seat_available -= 1;
    std::cout << "\n购票成功！当前剩余票数：" << t.seat_available << '\n';

    auto pNode = std::make_shared<PassengerNode>();

    pNode->value.id = p.id;
    pNode->value.name = p.name;
    pNode->value.start_station = p.start_station;
    pNode->value.end_station = p.end_station;
    pNode->value.price = p.price;
    pNode->value.carriage_type = p.carriage_type;
    pNode->value.carriage_number = p.carriage_number;
    pNode->value.seat_number = p.seat_number;

    tree.insert(pNode->value.price, pNode);

}

void bounceTicket(Train& t) {
    std::string id_{};
	std::cout << "请输入要退票的乘客ID：";
	std::cin >> id_;

    // 乘客是否存在？
    if (tree.searchPassengerById(id_) == false) {
		std::cout << "未找到该乘客！\n";
		return;
	}
    t.seat_available += 1;

    tree.deletePassengInfo(id_);

    std::cout << "退票成功！当前剩余票数：" << t.seat_available << '\n';

}

std::string getNextStation() {
    for (int i = 0; i < STATION_NUM; ++i) {
        if (STATIONS[i].first == currentStation) {
            if (i == 5) {
                return "";
            }
            else {
                return STATIONS[i + 1].first;
            }
        }

    }
}

void arriveNextStation() {
    auto nextStation = getNextStation();
    if (!nextStation.empty()) {
        currentStation = nextStation;
        std::cout << "成功抵达：" << currentStation << '\n';
    }
    else {
        std::cout << "已抵达终点站，无法前往下一站....\n";
    }
        
}

// 当前站点上车人数
std::size_t getCurrentStationGetInNum() {
    return tree.getPassengerGetInCountByStations(currentStation);
}

// 当前站点下车人数
std::size_t getCurrentStationGetOutNum() {
    return tree.getPassengerGetOutCountByStations(currentStation);
}

// 下一站点上车人数
std::size_t getNextStationGetInNum() {
    return tree.getPassengerGetInCountByStations(getNextStation());
}

// 下一站点下车人数
std::size_t getNextStationGetOutNum() {
    return tree.getPassengerGetOutCountByStations(getNextStation());
}

void passengerGetIn(Train& t) {
    auto pList = tree.getPassengerInfo();

    for (auto& p : pList) {
        if (p.start_station != currentStation) continue;

        insertPassengerToCarriage(p, t);

        tree.updatePassengInfo(p);
        
        std::cout << "以下为上车乘客信息一览：\n";
        p.printInfo();
    }
    
}

void passengerGetOut(Train& t) {
    auto pList = tree.getPassengerInfo();

    for (auto& p : pList) {
        if (p.end_station != currentStation) continue;

        delPassengerFromCarriage(p, t);
        t.seat_available += 1;

        std::cout << "以下为下车乘客信息一览：\n";
        p.printInfo();
    }
}

std::size_t getStationIdx(std::string station_) {
    for (int i = 0; i < STATION_NUM; ++i) {
		if (STATIONS[i].first == station_) return STATIONS[i].second;
	}
	return 0;
}

void countTrainInfo(Train& t) {
    auto passengersList = tree.getPassengerInfo();
    std::vector<std::size_t> stationGetInNum(STATION_NUM, 0), stationGetOutNum(STATION_NUM, 0);

    int sum{};
    for (const auto& p : passengersList) {
        sum += p.price;
        stationGetInNum[getStationIdx(p.start_station)] += 1;
        stationGetOutNum[getStationIdx(p.end_station)] += 1;
    }

    std::cout << "当前列车总收入：" << sum << '\n';
    std::cout << "===各站点上下车情况===" << '\n';

    for (int i = 0; i < STATION_NUM; ++i) {
        std::cout << "站点：" << STATIONS[i].first << '\n';
        std::cout << "上车人数：" << stationGetInNum[i] << '\n';
        std::cout << "下车人数：" << stationGetOutNum[i] << '\n';
	}
}
