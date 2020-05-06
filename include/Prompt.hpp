/**
 * @file Prompt.hpp
 * @author MineBill (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2019-02-22
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include <string>

class Prompt {
   public:
    Prompt(const char* _p, char _e);
    std::string collect();

    private:
    std::string prompt;
    char end;
};