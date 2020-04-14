#pragma once

#include "common/retcode.h"

/**
 * @brief      Macro to throw errcode or continue if SUCCESS.
 *
 * @param      func  The function to execute.
 *
 * @return     void.
 */
#define THROW_OR_CONTINUE(func) \
  {                             \
    RETCODE MACRO_ret = (func); \
    if (MACRO_ret != SUCCESS) { \
      return MACRO_ret;         \
    };                          \
  }

#define RAII(destructor) __attribute__((cleanup(destructor)))
