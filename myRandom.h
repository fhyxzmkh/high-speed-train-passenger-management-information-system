#pragma once

#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <tuple>

#include "CONSTANTS.h"

const std::string CHARSET_ID{ "0123456789" };
const std::string CHARSET_NAME{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::string CHARSET_CODE{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };

std::string randomString(const std::string&, std::size_t);

std::string randomName(std::size_t);

std::string randomID(std::size_t);

std::string randomCode(std::size_t);

std::pair<std::string, std::string> randomStation();

CarriageType randomCarriageType();

std::size_t randomNumber(std::size_t, std::size_t);

std::size_t randomCarriageNumber(CarriageType);

std::size_t randomSeatNumber(CarriageType);
