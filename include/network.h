#pragma once
/**
 * @file netowork.h
 * @author Carl Stahoviak
 * @brief 
 * @version 0.1
 * @date 2024-11-11
 * 
 * @copyright Copyright (c) 2024
 */
#include <array>
#include <string>

struct Charger {
  std::string name;
  double x{0};
  double y{0};
};

extern std::array<Charger, 10> NETWORK;