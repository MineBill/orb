/**
 * @file Prompt.cpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "include/Prompt.hpp"
#include <iostream>

void print_dots(int times) {
    for (int i = 0; i < times; i++) std::cout << ".";
    std::cout << " ";
}

Prompt::Prompt(const char* _p, char _e) : prompt(_p), end(_e) {}

std::string Prompt::collect() {
    int c;
    std::string ret;
    std::cout << prompt << " ";
    while ((c = std::cin.get()) != end) {
        if (c == '\n') {
            print_dots(prompt.length());
            continue;
        }
        ret += c;
    }
    ret += end;
    std::cin.clear();
    std::cin.get();  // Clear the last \n char.
    return ret;
}