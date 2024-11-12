/**
 * @file polymorphism.cpp
 * @author Carl Stahoviak
 * @brief Type definitions for polymorphism.h
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 */
#include "planner.h"

#include <cmath>
#include <memory>


double distance(const Charger& charger1, const Charger& charger2) {
  double dx = charger1.x - charger2.x;
  double dy = charger1.y - charger2.y;
  return std::sqrt(dx * dx + dy * dy);
}

std::ostream& operator<<(std::ostream& stream, const Node& node) {
  return stream << std::setprecision(4) << "Node(charger: " << node.name() <<
    ", duration: " << node.duration << ")";
}

std::ostream& operator<<(std::ostream& stream, const DerivedNode& node) {
  std::string parent_name{"NULL"};
  if ( auto parent = node.parent().lock() ) {
    parent_name = parent.get()->name();
  }

  return stream << std::setprecision(4) << "DerivedNode(charger: " << 
    node.name() << ", duration: " << node.duration << ", cost: " <<
      node.cost << ", parent: " << parent_name << ")";
}

std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<Node>& node) {
  return stream << node.get() << ": " << *node.get();
}

std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<DerivedNode>& node) {
  return stream << node.get() << ": " << *node.get();
} 

// template<typename T>
// std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<T>& item) {
//   return stream << item.get() << ": " << *item.get();
// }

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
  return distance(node1.charger(), node2.charger());
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