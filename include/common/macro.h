/**
 * @file macro.h
 *
 * @brief      Provides defines for using inside library. These macro shorten
 *             the code and make it easier to read.
 *
 * @author     Alexander Stanovoy
 */

#pragma once

#include "common/retcode.h"

/**
 * @brief      Macro to throw errcode or continue if SUCCESS.
 *
 * @param      func  The function to execute.
 *
 * @since      0.0.1
 */
#define THROW_OR_CONTINUE(func) \
  {                             \
    RETCODE MACRO_ret = (func); \
    if (MACRO_ret != SUCCESS) { \
      return MACRO_ret;         \
    };                          \
  }

/**
 * @brief      Macro for setting up the **RAII** pattern for data structure.
 *
 * @param      destructor  The destructor for structure.
 *
 * @since      0.0.1
 */
#define RAII(destructor) __attribute__((cleanup(destructor)))
