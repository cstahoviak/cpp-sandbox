/**
 * @file planner.cpp
 * @author Carl Stahoviak
 * @brief Type definitions for smart_pointers/planner.h.
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "smart_pointers/planner.h"
#include "math.h"
#include "node.h"

namespace smart_pointers
{
  PlannerResult SimplePlanner::PlanRoute()
  {
    std::vector<std::shared_ptr<Node>> route;
    size_t idx{0};
    for ( const auto& [name, node] : graph_ ) {
      // Need to use make_* with emplace-like functions
      route.emplace_back(std::make_shared<Node>(node.get()->charger()));
      route.back().get()->duration = idx;
      idx++;
    }
    return PlannerResult(route);
  }

  double SimplePlanner::ComputeCost(const Node& node1, const Node& node2) {
    return math::distance(node1.charger(), node2.charger());
  }

  PlannerResult DerivedPlanner::PlanRoute()
  {
    std::vector<std::shared_ptr<Node>> route;
    size_t idx{0};

    // TODO: Can I unpack the node as DerivedNode instead of a Node?
    for ( const auto& [name, node] : graph_ ) {
      std::shared_ptr<DerivedNode> new_derived =
        std::make_shared<DerivedNode>(node.get()->charger());
      new_derived.get()->duration = idx;
      new_derived.get()->cost = 0;

      if ( !route.empty() ) {
        new_derived.get()->cost = ComputeCost(*new_derived.get(), *node.get());
        // Must remove constness from node to set parent
        // new_derived.get()->parent(std::const_pointer_cast<DerivedNode>(node));
        new_derived.get()->parent(std::static_pointer_cast<DerivedNode>(node));
      }

      route.push_back(std::move(new_derived));
      idx++;
    }
    return route;
  }

  double DerivedPlanner::ComputeCost(const Node& node1, const Node& node2) {
    // Downcast Node& to DerivedNode& via static_cast.
    return static_cast<const DerivedNode&>(node1).cost + 
      static_cast<const DerivedNode&>(node2).cost;
  }
}