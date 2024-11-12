/**
 * @file manager.h
 * @author Carl Stahoviak
 * @brief 
 * @version 0.1
 * @date 2024-11-11
 * 
 * @copyright Copyright (c) 2024
 */
#include "planner.h"

#include <experimental/propagate_const>


template<typename NodeType>
class Manager
{
  public:
    Manager(Planner<NodeType> planner) : planner_(std::move(planner)) {}

    const std::unique_ptr<Planner<NodeType>>& planner() const { return planner_; }

  private:
    std::unique_ptr<Planner<NodeType>> planner_;
};


class PimplManager
{
  private:
    class Planner; // forward declaration of the implementation class

    // One implementation example: see below for other design options and trade-offs
    std::experimental::propagate_const< // const-forwarding pointer wrapper
        std::unique_ptr<                // unique-ownership opaque pointer
            Planner>> pImpl;               // to the forward-declared implementation class
};