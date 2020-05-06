/**
 * @file ErrTypes.hpp
 * @author MineBill (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-02-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#define CODE(c) (c + 100)
#define INVALID_VAR_NAME CODE(1)
#define UNEXPECTED_SYMBOL CODE(2)
#define NON_SYMB_ASSIGN CODE(3)
#define NON_SYMB_PARAM CODE(4)
#define UNKNOWN_FN_CALL CODE(5)
#define INVALID_OP CODE(6)
#define UNINITIALIZED_VAR CODE(7)