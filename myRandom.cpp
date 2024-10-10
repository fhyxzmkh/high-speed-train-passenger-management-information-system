#include "myRandom.h"

std::string randomString(const std::string& charset, std::size_t length) {
    const std::size_t max_index = charset.size() - 1;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, max_index);

    std::string random_string;
    for (std::size_t i = 0; i < length; ++i) {
        random_string += charset[distribution(generator)];
    }

    return std::move(random_string);
}

std::string randomName(std::size_t length) {
    return randomString(CHARSET_NAME, length);
}

std::string randomID(std::size_t length) {
    return randomString(CHARSET_ID, length);
}

std::string randomCode(std::size_t length) {
    return randomString(CHARSET_CODE, length);
}

std::pair<std::string, std::string> randomStation() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, 5);

    int index1, index2;
    do {
        index1 = distribution(generator);
        index2 = distribution(generator);
    } while (index1 >= index2);

    std::string start_station = STATIONS[index1].first;
    std::string end_station = STATIONS[index2].first;

    return std::make_pair(start_station, end_station);
}

CarriageType randomCarriageType() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(1, 2);

    return static_cast<CarriageType>(distribution(generator));
}

std::size_t randomNumber(std::size_t min, std::size_t max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}

std::size_t randomCarriageNumber(CarriageType ctype_) {
    if (ctype_ == CarriageType::CARRIAGE_TYPE_FIRST_CLASS) {
        return randomNumber(1, 2);
    }
    else {
        return randomNumber(3, 5);
    }
}

std::size_t randomSeatNumber(CarriageType ctype_) {
    if (ctype_ == CarriageType::CARRIAGE_TYPE_FIRST_CLASS) {
        return randomNumber(1, 5);
    }
    else {
        return randomNumber(1, 9);
    }
}

