/**
 * @file polymorphism_and_templates.cpp
 * @author Carl Stahoviak
 * @brief Experiment with virtual functions, polymorphic types and templating
 * in the context of the Tesla Supercharger problem.
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 */
// #include "manager.h"
#include "templates/planner.h"

#include <iostream>

using namespace templates;


int main()
{
  // Use the planners via direct construction.
  {
    // Plan a route with the SimplePlanner
    SimplePlanner simple_planner(NETWORK);
    PlannerResult<Node> result = simple_planner.PlanRoute();
    std::cout << "\nRoute planned with the SimplePlanner (size: " <<
      result.route.size() << "):" << std::endl;
    for (const auto& node : result.route ) {
      std::cout << node << std::endl;
    }

    // Plan a route with the DerivedPlanner
    DerivedPlanner planner(NETWORK);
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

  // Use the planners via OOP-factory construction.
  // NOTE: Attempting to compile the scope below with throw an error rerlated
  // to the GetPlanner factory function.
  // {
  //   // Plan a route with the SimplePlanner
  //   std::unique_ptr<Planner<Node>> simple_planner = 
  //     GetPlanner<Node>(PlannerType::SIMPLE);
  //   PlannerResult<Node> result = simple_planner.get()->PlanRoute();
  //   std::cout << "\nRoute planned with the SimplePlanner (size: " <<
  //     result.route.size() << "):" << std::endl;
  //   for (const auto& node : result.route ) {
  //     std::cout << node << std::endl;
  //   }

  //   // Plan a route with the DerivedPlanner
  //   std::unique_ptr<Planner<DerivedNode>> planner =
  //     GetPlanner<DerivedNode>(PlannerType::DERIVED);
  //   PlannerResult<DerivedNode> result2 = planner.get()->PlanRoute();

  //   // Output the result of the DerivedPlanner as Nodes
  //   std::cout << "\nOutput result of DerivedPlanner::PlanRoute as Nodes (size: "
  //     << result2.route.size() << "):" << std::endl;
  //   for (const DerivedNode& node : result2.route ) {
  //     std::cout << static_cast<Node>(node) << std::endl;
  //   }

  //   // Output the result of the DerivedPlanner as DerivedNodes
  //   std::cout << "\nOutput result of DerivedPlanner::PlanRoute as DerivedNodes "
  //     "(size: " << result2.route.size() << "):" << std::endl;
  //   for (const DerivedNode& node : result2.route ) {
  //     std::cout << node << std::endl;
  //   }
  // }
}