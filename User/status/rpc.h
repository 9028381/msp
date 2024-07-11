#ifndef __RPC_H__
#define __RPC_H__

#include "../config.h"
#include "stdint.h"

struct Procedure {
  void (*fn)(uint16_t var, void *para);
  void *para;
};

typedef struct Procedure RPC[STATUS_RPC_ID_LIMIT];

void status_rpc_init(RPC rpc);
void rpc_call_id(RPC rpc, uint8_t id, uint16_t var);

#endif // !__RPC_H__
