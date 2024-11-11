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
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <unordered_map>
#include <vector>


struct Charger{
  std::string name;
  double x{0};
  double y{0};
};


struct Node
{
  Node(const Charger charger) : charger_(std::move(charger)) {}
  // virtual ~Node();

  double duration{0};

  const Charger& charger() const { return charger_; }
  const std::string& name() const { return charger_.name; }

  private:
    Charger charger_;
};

/**
 * @brief The Derived node adds the following attributes on top of the Node.
 * 1. cost
 * 2. parent
 */
struct DerivedNode : public Node, std::enable_shared_from_this<DerivedNode>
{
  DerivedNode(const Charger charger) : Node(charger) {}

  double cost{std::numeric_limits<double>::max()};

  std::weak_ptr<DerivedNode> parent() const { return parent_ ; }
  void parent(std::shared_ptr<DerivedNode> parent) {
    parent_ = std::move(parent);
  }

  private:
    std::weak_ptr<DerivedNode> parent_;
};


// String stream operator overloads.
std::ostream& operator<<(std::ostream&, const Node&);
std::ostream& operator<<(std::ostream&, const DerivedNode&);
std::ostream& operator<<(std::ostream&, const std::shared_ptr<Node>&);
std::ostream& operator<<(std::ostream&, const std::shared_ptr<DerivedNode>&);

// TODO: Would like to overload operator<< for shared_ptrs like this, but it's
// not working. Not sure why.
// template<typename T>
// std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<T>&);


template<typename NodeType>
struct PlannerResult
{
  PlannerResult(std::vector<NodeType> route) : route(std::move(route)) {}
  std::vector<NodeType> route;
};


/**
 * @brief The Planner interface class defines two member functions:
 *  1. PlanRoute()
 *  2. ComputeCost(const Node&, const Node&) 
 */
template<typename NodeType>
class Planner
{
  using PlannerResultType = PlannerResult<NodeType>;

  public:
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
    /**
     * @brief Constructs a graph of Node objects.
     * 
     * Note: The implementation and declaration of a templarte function (
     * including ctors) must appear in the header and not the cpp file.
     */
    template<size_t N>
    SimplePlanner(const std::array<Charger, N>& network) {
      for ( const Charger& charger : network ) {
        graph_[charger.name] = std::make_shared<Node>(charger);
      }
    }

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
    DerivedPlanner(const std::array<Charger, N>& network) {
      size_t idx{0};
      for ( const Charger& charger : network ) {
        graph_[charger.name] = std::make_shared<DerivedNode>(charger);
        graph_.at(charger.name).get()->cost = idx;
        idx++;
      }
    }

    PlannerResult<DerivedNode> PlanRoute() override;
    double ComputeCost(const DerivedNode& node1, const DerivedNode& node2) override;
};

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