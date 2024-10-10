#include <iostream>
#include <random>
#include <ctime>
#include <memory>
#include <tuple>
#include <vector>

#include "passenger.h"
#include "train.h"
#include "myRandom.h"
#include "BstTree.h"
#include "menu.h"
#include "CONSTANTS.h"


Train initTrain() {
    std::cout << "==========列车信息==========" << '\n';
    Train t;
    t.code = randomCode(6);

    t.start_station = "Shanghai";
    t.end_station = "Beijing";

    std::cout << "Train code: " << t.code << '\n';
    std::cout << "Train seats: " << t.seat_count << '\n';
    std::cout << "This train from " << t.start_station << " to " << t.end_station << '\n';

    t.carriages = createCarriage();

    return t;
}

int main() {
    auto t = initTrain();

    while (1) mainMenu(t);
}