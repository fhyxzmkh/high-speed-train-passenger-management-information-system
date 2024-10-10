#pragma once

#include "BstTree.h"


void mainMenu(Train& t);

bool requireMenu(Train& t);

Passenger createPassenger();

std::shared_ptr<CarriageNode> createCarriage();

void insertPassengerToCarriage(Passenger& p_, Train& t_);

void delPassengerFromCarriage(Passenger& p_, Train& t_);

bool isValidStation(std::string ss, std::string es);

void sellticket(Train& t);

void manualPurchaseTicket(Train& t);

void bounceTicket(Train& t);

std::string getNextStation();

void arriveNextStation();

std::size_t getCurrentStationGetInNum();

std::size_t getCurrentStationGetOutNum();

std::size_t getNextStationGetInNum();

std::size_t getNextStationGetOutNum();

void passengerGetIn(Train& t);

void passengerGetOut(Train& t);

void countTrainInfo(Train& t);