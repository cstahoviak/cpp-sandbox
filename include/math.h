#pragma once
/**
 * @file math.h
 * @author Carl Stahoviak
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "network.h"

#include <cmath>

namespace math
{
  double distance(const Charger& charger1, const Charger& charger2) {
    double dx = charger1.x - charger2.x;
    double dy = charger1.y - charger2.y;
    return std::sqrt(dx * dx + dy * dy);
  }
}