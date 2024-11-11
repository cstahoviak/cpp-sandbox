/**
 * @file polymorphism.cpp
 * @author Carl Stahoviak
 * @brief Experiment with virtual functions and polymorphic types in the context
 * of the Tesla Supercharger problem.
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 */
#include "polymorphism.h"

std::array<Charger, 10> network {{
  {"charger_0", 0, 0},
  {"charger_1", 1, 1},
  {"charger_2", 2, 2},
  {"charger_3", 3, 3},
  {"charger_4", 4, 4},
  {"charger_5", 5, 5},
  {"charger_6", 6, 6},
  {"charger_7", 7, 7},
  {"charger_8", 8, 8},
  {"charger_9", 9, 9},
}};


int main() {
  // Create a Node and a Derived Node
  const std::shared_ptr<Node> node = std::make_shared<Node>(network[0]);
  const std::shared_ptr<DerivedNode> derived = 
    std::make_shared<DerivedNode>(network[0]);

  // Experiment with different ways of up-casting a DerivedNode to a Node.
  const std::shared_ptr<Node> derived_as_node = derived;
  const std::shared_ptr<Node> derived_as_node2 = derived.get()->shared_from_this();

  std::cout << "Outputting the DerivedNode:" << std::endl;
  std::cout << "(as DerivedNode): " << derived << std::endl;
  std::cout << "(as Node): " << derived_as_node << std::endl;
  std::cout << "(as Node): " << derived_as_node2 << std::endl;
  std::cout << "(as Node): " << static_cast<Node>(*derived.get()) << std::endl;
  std::cout << "(as Node): " << static_cast<std::shared_ptr<Node>>(derived) << std::endl;
  
  // Assign the derived node as the parent of another DerivedNode
  std::cout << "\nAssign the DerivedNode's parent:" << std::endl;
  auto another_derived = std::make_shared<DerivedNode>(network[1]);
  another_derived.get()->parent(derived);
  std::cout << another_derived << std::endl;

  // Plan a route with the SimplePlanner
  SimplePlanner simple_planner(network);
  PlannerResult<Node> result = simple_planner.PlanRoute();
  std::cout << "\nRoute planned with the SimplePlanner (size: " <<
    result.route.size() << "):" << std::endl;
  for (const auto& node : result.route ) {
    std::cout << node << std::endl;
  }

  // Plan a route with the DerivedPlanner
  DerivedPlanner planner(network);
  PlannerResult<DerivedNode> result2 = planner.PlanRoute();

  // Output the result of the DerivedPlanner as Nodes
  std::cout << "\nOutput result of DerivedPlanner::PlanRoute as Nodes (size: "
    << result2.route.size() << "):" << std::endl;
  for (const DerivedNode& node : result2.route ) {
    std::cout << static_cast<Node>(node) << std::endl;
  }

  // Output the result of the DerivedPlanner as DerivedNodes
  std::cout << "\nOutput result of DerivedPlanner::PlanRoute as DerivedNodes "
    "(size: " << result2.route.size() << "):" << std::endl;
  for (const DerivedNode& node : result2.route ) {
    std::cout << node << std::endl;
  }
  
}