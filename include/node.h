#pragma once
/**
 * @file node.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "network.h"

#include <limits>
#include <memory>

  struct Node
  {
    Node(Charger charger) : charger_(std::move(charger)) {}

    double duration{0};

    const Charger& charger() const { return charger_; }
    const std::string& name() const { return charger_.name; }

    private:
      Charger charger_;
  };

  /**
   * @brief The Derived node adds the following attributes to the Node.
   * 1. cost
   * 2. parent
   */
  struct DerivedNode : public Node, std::enable_shared_from_this<DerivedNode>
  {
    DerivedNode(Charger charger) : Node(charger) {}

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
