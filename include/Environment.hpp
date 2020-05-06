/**
 * @file Environment.hpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-21
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include <map>
#include "include/Primitives.hpp"

class Environment {
   public:
    Environment(Environment *parent);

    Primitive *get(std::string id);
    void set(std::string id, Primitive *val);
    bool contains(std::string id);

   private:
    Environment *parent;
    std::map<std::string, Primitive *> items;
};