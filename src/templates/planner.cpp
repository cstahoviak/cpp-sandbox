/**
 * @file polymorphism.cpp
 * @author Carl Stahoviak
 * @brief Type definitions for polymorphism.h
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 */
#include "templates/planner.h"
#include "math.h"
#include "node.h"

#include <cmath>
#include <memory>

namespace templates
{
  PlannerResult<Node> SimplePlanner::PlanRoute()
  {
    std::vector<Node> route;
    size_t idx{0};
    for ( const auto& [name, node] : graph_ ) {
      route.emplace_back(node.get()->charger());
      route.back().duration = idx;
      idx++;
    }
    return PlannerResult<Node>(route);
  }

  double SimplePlanner::ComputeCost(const Node& node1, const Node& node2) {
    return math::distance(node1.charger(), node2.charger());
  }

  PlannerResult<DerivedNode> DerivedPlanner::PlanRoute()
  {
    std::vector<DerivedNode> route;
    size_t idx{0};
    for ( const auto& [name, node] : graph_ ) {
      DerivedNode new_node(node.get()->charger());
      new_node.duration = idx;
      new_node.cost = 0;

      if ( !route.empty() ) {
        new_node.cost = ComputeCost(new_node, *node.get());
        new_node.parent(node);
      }

      route.push_back(std::move(new_node));
      idx++;
    }
    return route;
  }

  double DerivedPlanner::ComputeCost(const DerivedNode& node1, const DerivedNode& node2) {
    return node1.cost + node2.cost;
  }
}