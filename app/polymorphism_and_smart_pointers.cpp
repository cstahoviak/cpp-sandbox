/**
 * @file polymorphism_and_smart_pointers.cpp
 * @author Carl Stahoviak
 * @brief Experiment with virtual functions, polymorphic types and smart
 * pointers in the context of the Tesla Supercharger problem.
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 */

#include "smart_pointers/planner.h"

#include <iostream>

using namespace smart_pointers;


int main()
{
  // Experiment with downcasting shared_ptrs.
  {
    std::cout << "Experimenting with downcasting and std::shared_ptr." << std::endl;

    // Create a Node and a Derived Node
    const std::shared_ptr<Node> node = std::make_shared<Node>(NETWORK[0]);
    const std::shared_ptr<DerivedNode> derived = 
      std::make_shared<DerivedNode>(NETWORK[0]);

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
    auto another_derived = std::make_shared<DerivedNode>(NETWORK[1]);
    another_derived.get()->parent(derived);
    std::cout << another_derived << std::endl;
  }
  std::cout << "\n";

  // Use the SimplePlanner.
  {
    // Create a SimplePlanner via OOP factory construction.
    std::unique_ptr<Planner> planner = GetPlanner(PlannerType::SIMPLE);

    // Plan a route and output the result
    PlannerResult result = planner.get()->PlanRoute();
    std::cout << "\nPlanning route with the SimplePlanner." << std::endl;
    for ( const std::shared_ptr<Node>& node : result.route ) {
      std::cout << node << std::endl;
    }
  }
  std::cout << "\n";

  // Use the DeriveedPlanner.
  {
    // Create a DerivedPlanner via OOP factory construction.
    std::unique_ptr<Planner> planner = GetPlanner(PlannerType::DERIVED);

    // Plan a route and output the result
    PlannerResult result = planner.get()->PlanRoute();
    std::cout << "\nPlanning route with the SimplePlanner." << std::endl;
    for ( const std::shared_ptr<Node>& node : result.route ) {
      // Output each node in the route as a DerivedNode.
      std::cout << std::static_pointer_cast<DerivedNode>(node) << std::endl;
    }
  }
}