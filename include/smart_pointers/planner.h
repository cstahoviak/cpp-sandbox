#pragma once
/**
 * @file planner.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 */
#include "node.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>


namespace smart_pointers
{
  struct PlannerResult
  {
    PlannerResult(std::vector<std::shared_ptr<Node>> route) : 
      route(std::move(route)) {}

    std::vector<std::shared_ptr<Node>> route;
  };


  enum class PlannerType{
    SIMPLE,
    DERIVED,
    NONE
  };


  /**
   * @brief The Planner interface class defines two member functions:
   *  1. PlanRoute()
   *  2. ComputeCost(const Node&, const Node&) 
   */
  class Planner
  {
    public:
      virtual PlannerResult PlanRoute() = 0;
      virtual double ComputeCost(const Node&, const Node&) = 0;

    protected:
      std::unordered_map<std::string, std::shared_ptr<Node>> graph_;
  };


  /**
   * @brief The SimplePlanner will use the Node type.
   */
  class SimplePlanner : public Planner
  {
    public:
      SimplePlanner() {
        std::cout << "SimplePlanner default ctor." << std::endl;
        for ( const Charger& charger : NETWORK ) {
          graph_[charger.name] = std::make_shared<Node>(charger);
          std::cout << "Creating " << graph_.at(charger.name) << std::endl;
        }
      }

      /**
       * @brief Constructs a graph of Node objects.
       * 
       * Note: The implementation and declaration of a template function (
       * including ctors) must appear in the header and not the cpp file.
       */
      template<size_t N>
      SimplePlanner(const std::array<Charger, N>& network) {
        std::cout << "SimplePlanner ctor." << std::endl;
        for ( const Charger& charger : network ) {
          graph_[charger.name] = std::make_shared<Node>(charger);
          std::cout << "Creating " << graph_.at(charger.name) << std::endl;
        }
      }

      PlannerResult PlanRoute() override;
      double ComputeCost(const Node&, const Node&) override;
  };

  /**
   * @brief The DerivedPlanner will use the DerivedNode type.
   */
  class DerivedPlanner : public Planner
  {
    public:
      DerivedPlanner() {
        std::cout << "DerivedPlanner default ctor." << std::endl;
        for ( const Charger& charger : NETWORK ) {
          graph_[charger.name] = std::make_shared<DerivedNode>(charger);
          std::cout << "Creating " << graph_.at(charger.name) << std::endl;
        }
      }

      /**
       * @brief Constructs a graph of Node objects.
       * 
       * Note: The implementation and declaration of a template function (
       * including ctors) must appear in the header and not the cpp file.
       */
      template<size_t N>
      DerivedPlanner(const std::array<Charger, N>& network) {
        std::cout << "DerivedPlanner ctor." << std::endl;
        for ( const Charger& charger : network ) {
          graph_[charger.name] = std::make_shared<DerivedNode>(charger);
          std::cout << "Creating " << graph_.at(charger.name) << std::endl;
        }
      }

      PlannerResult PlanRoute() override;
      double ComputeCost(const Node& node1, const Node& node2) override;
  };

  /**
   * @brief 
   * 
   * @tparam NodeType 
   * @param type 
   * @return std::unique_ptr<Planner<NodeType>> 
   */
  inline std::unique_ptr<Planner> GetPlanner(PlannerType type)
  {
    switch( type )
    {
      case PlannerType::SIMPLE:
        return std::make_unique<SimplePlanner>();

      case PlannerType::DERIVED:
        return std::make_unique<DerivedPlanner>();

      default:
        throw std::invalid_argument("Cannot create Planner from the provided PlannerType.");
    }
  }
}