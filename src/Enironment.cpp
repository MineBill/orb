#include "include/Environment.hpp"

Environment::Environment(Environment *_p) : parent(_p) {}

Primitive *Environment::get(std::string id) {
    if (items.find(id) != items.end())
        return items[id];
    else if (parent != nullptr && parent->contains(id))
        return parent->get(id);
    else
        return nullptr;
}

void Environment::set(std::string id, Primitive *val) { items[id] = val; }

bool Environment::contains(std::string id) {
    if (items.find(id) != items.end())
        return true;
    else if (parent != nullptr && parent->contains(id))
        return true;
    else
        return false;
}