#ifndef __RPC_H__
#define __RPC_H__

#include "../config.h"
#include "stdint.h"

struct Procedure {
  void fn(uint16_t, void *);
  void *para;
};

struct RPC {
  struct Procedure procedures[STATUS_RPC_ID_MAX];
  uint16_t stack;
};

#endif // !__RPC_H__
