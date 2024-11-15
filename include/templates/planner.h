#pragma once
/**
 * @file polymorpshism.h
 * @author Carl Stahoviak
 * @brief Experiment with virtual functions and polymorphic types in the context
 * of the Tesla Supercharger problem.
 * @version 0.1
 * @date 2024-11-08
 * 
 * @copyright Copyright (c) 2024
 */
#include "network.h"
#include "node.h"

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace templates
{
  template<typename NodeType>
  struct PlannerResult
  {
    PlannerResult(std::vector<NodeType> route) : route(std::move(route)) {}
    std::vector<NodeType> route;
  };


  enum class PlannerType{
    SIMPLE,
    DERIVED,
    NONE
  };


  /**
   * @brief The Planner interface class defines two member functions:
   *  1. PlanRoute()
   *  2. ComputeCost(const NodeType&, const NodeType&) 
   */
  template<typename NodeType>
  class Planner
  {
    using PlannerResultType = PlannerResult<NodeType>;

    public:
      Planner() {
        for ( const Charger& charger : NETWORK ) {
          graph_[charger.name] = std::make_shared<NodeType>(charger);
        }
      }

      /**
       * @brief Constructs a graph of Node objects.
       * 
       * Note: The implementation and declaration of a template function (
       * including ctors) must appear in the header and not the cpp file.
       */
      template<size_t N>
      Planner(const std::array<Charger, N>& network) {
        for ( const Charger& charger : network ) {
          graph_[charger.name] = std::make_shared<NodeType>(charger);
        }
      }

      virtual PlannerResultType PlanRoute() = 0;
      virtual double ComputeCost(const NodeType&, const NodeType&) = 0;

    protected:
      std::unordered_map<std::string, std::shared_ptr<NodeType>> graph_;
  };


  /**
   * @brief The SimplePlanner will use the Node type.
   */
  class SimplePlanner : public Planner<Node>
  {
    public:
      template<size_t N>
      SimplePlanner(const std::array<Charger, N>& network) : Planner(network) {}

      PlannerResult<Node> PlanRoute() override;
      double ComputeCost(const Node&, const Node&) override;
  };

  /**
   * @brief The DerivedPlanner will use the DerivedNode type.
   */
  class DerivedPlanner : public Planner<DerivedNode>
  {
    public:
      /**
       * @brief Constructs a graph of DerivedNode objects.
       */
      template<size_t N>
      DerivedPlanner(const std::array<Charger, N>& network) : Planner(network) {}

      PlannerResult<DerivedNode> PlanRoute() override;
      double ComputeCost(const DerivedNode& node1, const DerivedNode& node2) override;
  };

  /**
   * @brief It doesn't seem like using a templated interface class (Planner) in
   * combination with an OOP Factory style function (GetPlanner) that returns a 
   * unique_ptr to the base class (Planner) is going to work.
   * 
   * @tparam NodeType 
   * @param type 
   * @return std::unique_ptr<Planner<NodeType>> 
   */
  template<typename NodeType>
  inline std::unique_ptr<Planner<NodeType>> GetPlanner(PlannerType type)
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

/**
 * @brief Atttempting to implement the unique_ptr downcast solution from:
 * https://stackoverflow.com/questions/21174593/downcasting-unique-ptrbase-to-unique-ptrderived
 * 
 * @tparam Derived 
 * @tparam Base 
 * @tparam Del 
 * @param p 
 * @return std::unique_ptr<Derived, Del> 
 */
// template<typename Derived, typename Base, typename Del>
// inline std::unique_ptr<Derived, Del> 
//   static_unique_ptr_cast(std::unique_ptr<Base, Del>&& p)
// {
//     auto d = static_cast<Derived *>(p.release());
//     return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
// }