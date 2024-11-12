/**
 * @file node.cpp
 * @author Carl Stahoviak
 * @brief 
 * @version 0.1
 * @date 2024-11-12
 * 
 * @copyright Copyright (c) 2024
 */
#include "node.h"

#include <iomanip>


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