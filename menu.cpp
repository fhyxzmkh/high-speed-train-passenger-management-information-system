#include "menu.h"

std::string currentStation = STATIONS[0].first;
bool isRuning = false;
BstTree tree;

void mainMenu(Train& t) {
    std::cout << "\n��ӭʹ�ø����г��ÿ͹�����Ϣϵͳ..." << '\n';
    std::cout << "==============�˵�===============" << '\n';
    std::cout << "1����ѯ��Ϣ" << '\n';
    std::cout << "2����Ʊ" << '\n';
    std::cout << "3���ֶ���Ʊ" << '\n';
    std::cout << "4����Ʊ" << '\n';
    std::cout << "5�������г�" << '\n';
    std::cout << "6��ǰ����һվ" << '\n';
    std::cout << "7��ͳ��" << '\n';
    std::cout << "8���˳�" << '\n';

    int opt{};

    std::cout << "\n������ѡ�";
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
            std::cout << "�г������У��޷���Ʊ,��ǰ����Ʊ...\n";
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
            std::cout << "�г������У��޷���Ʊ...\n";
            break;
        }
        
        bounceTicket(t);
        break;
    case 5:
        system("cls");

        if (isRuning) {
            std::cout << "�г�������...\n";
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
            std::cout << "�ѵ����յ�վ���޷�ǰ����һվ��\n";
            break;
        }

        if (!isRuning) {
            std::cout << "���������г�...\n";
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
            std::cout << "�г������У���ʱ�޷��鿴����...\n";
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
    std::cout << "\n=====��ѯ�˵�=====\n";
    std::cout << "1����ѯ�г���Ϣ" << '\n';
    std::cout << "2����ѯ��ǰվ��" << '\n';
    std::cout << "3����ѯ��һվ��" << '\n';
    std::cout << "4����ѯ���й�Ʊ�˿�" << '\n';
    std::cout << "5����ѯ��ǰվ�����³��ÿ���" << '\n';
    std::cout << "6����ѯ��һվ�����³��ÿ���" << '\n';
    std::cout << "7���������˵�" << '\n';

    int opt{};

    std::cout << "\n������ѡ�";
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

        std::cout << "��ǰվ�㣺" << currentStation << '\n';
        break;
    case 3:
        system("cls");

        if (getNextStation().empty()) std::cout << "��ǰΪ�յ�վ������һվ��\n";
        else std::cout << "��һվΪ��" << getNextStation() << '\n';
        break;
    case 4:
        system("cls");

        tree.inorder();
        break;
    case 5:
        system("cls");

        if (currentStation == "Shanghai") {
            std::cout << "��ǰվΪʼ��վ�����³���Ϣ��" << '\n';
            std::cout << "��ǰվ���ϳ�������" << getCurrentStationGetInNum() << '\n';
            break;
        }
        std::cout << "��ǰվ���ϳ�������" << getCurrentStationGetInNum() << '\n';
        std::cout << "��ǰվ���³�������" << getCurrentStationGetOutNum() << '\n';
        break;
    case 6:
        system("cls");

        if (getNextStation().empty()) {
            std::cout << "�ѵ����յ�վ������һվ��" << '\n';
            break;
        }
        std::cout << "��һվΪ��" << getNextStation() << '\n';
        std::cout << "��һվ���ϳ�������" << getNextStationGetInNum() << '\n';
        std::cout << "��һվ���³�������" << getNextStationGetOutNum() << '\n';
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

    p.carriage_number = 0; // ��ʱ��δȷ��
    p.seat_number = 0; // ��ʱ��δȷ��

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

    // ����˿͵�������
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
        std::cout << "��ǰ�г�����Ա����Ⱥ���һ��...\n";
        return;
    }
        
    Passenger p = createPassenger();
    
    if (tree.searchPassengerById(p.id)) {
        std::cout << "�����ظ���Ʊ��\n";
        return;
    }

    t.seat_available -= 1;
    std::cout << "��Ʊ�ɹ�����ǰʣ��Ʊ����" << t.seat_available << '\n';

    p.printInfo();

    // ����˿͵��г�������������
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
        std::cout << "��ǰ�г�����Ա���޷���Ʊ...\n";
        return;
    }

    Passenger p;
    std::cout << "������˿�������";
    std::cin >> p.name;
    std::cout << "������˿�ID��";
    std::cin >> p.id;

    if (tree.searchPassengerById(p.id)) {
        std::cout << "�����ظ���Ʊ��\n";
        return;
    }

    std::cout << "������˿���ʼվ��";
    std::cin >> p.start_station;
    std::cout << "������˿��յ�վ��";
    std::cin >> p.end_station;

    if (!isValidStation(p.start_station, p.end_station)) {
        std::cout << "�Ƿ���վ����Ϣ��\n";
        return;
    }

    std::cout << "�����복��ȵ�(һ�ȣ�1 ���ȣ�2)��";
    std::cin >> p.carriage_type;

    int a_{}, b_{};
    for (const auto& station : STATIONS) {
        if (station.first == p.start_station) a_ = station.second;
        if (station.first == p.end_station) b_ = station.second;
    }
    p.price = static_cast<size_t>(std::abs(a_ - b_)) * (p.carriage_type == 1 ? FIRST_CLASS_SEAT_PRICE : SECOND_CLASS_SEAT_PRICE);

    p.carriage_number = 0; // ��ʱ��δȷ��
    p.seat_number = 0; // ��ʱ��δȷ��

    p.printInfo();

    t.seat_available -= 1;
    std::cout << "\n��Ʊ�ɹ�����ǰʣ��Ʊ����" << t.seat_available << '\n';

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
	std::cout << "������Ҫ��Ʊ�ĳ˿�ID��";
	std::cin >> id_;

    // �˿��Ƿ���ڣ�
    if (tree.searchPassengerById(id_) == false) {
		std::cout << "δ�ҵ��ó˿ͣ�\n";
		return;
	}
    t.seat_available += 1;

    tree.deletePassengInfo(id_);

    std::cout << "��Ʊ�ɹ�����ǰʣ��Ʊ����" << t.seat_available << '\n';

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
        std::cout << "�ɹ��ִ" << currentStation << '\n';
    }
    else {
        std::cout << "�ѵִ��յ�վ���޷�ǰ����һվ....\n";
    }
        
}

// ��ǰվ���ϳ�����
std::size_t getCurrentStationGetInNum() {
    return tree.getPassengerGetInCountByStations(currentStation);
}

// ��ǰվ���³�����
std::size_t getCurrentStationGetOutNum() {
    return tree.getPassengerGetOutCountByStations(currentStation);
}

// ��һվ���ϳ�����
std::size_t getNextStationGetInNum() {
    return tree.getPassengerGetInCountByStations(getNextStation());
}

// ��һվ���³�����
std::size_t getNextStationGetOutNum() {
    return tree.getPassengerGetOutCountByStations(getNextStation());
}

void passengerGetIn(Train& t) {
    auto pList = tree.getPassengerInfo();

    for (auto& p : pList) {
        if (p.start_station != currentStation) continue;

        insertPassengerToCarriage(p, t);

        tree.updatePassengInfo(p);
        
        std::cout << "����Ϊ�ϳ��˿���Ϣһ����\n";
        p.printInfo();
    }
    
}

void passengerGetOut(Train& t) {
    auto pList = tree.getPassengerInfo();

    for (auto& p : pList) {
        if (p.end_station != currentStation) continue;

        delPassengerFromCarriage(p, t);
        t.seat_available += 1;

        std::cout << "����Ϊ�³��˿���Ϣһ����\n";
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

    std::cout << "��ǰ�г������룺" << sum << '\n';
    std::cout << "===��վ�����³����===" << '\n';

    for (int i = 0; i < STATION_NUM; ++i) {
        std::cout << "վ�㣺" << STATIONS[i].first << '\n';
        std::cout << "�ϳ�������" << stationGetInNum[i] << '\n';
        std::cout << "�³�������" << stationGetOutNum[i] << '\n';
	}
}
