#ifndef __RPC_H__
#define __RPC_H__

#include "../config.h"
#include "stdint.h"

struct RemoteProcedure {
  void (*fn)(uint16_t remote_var, void *para);
  void *para;
};

typedef struct RemoteProcedure RPC[TASK_RPC_ID_LIMIT];

void task_rpc_init(RPC rpc);
void task_rpc_call_id(RPC rpc, uint8_t id, uint16_t remote_var);

#endif // !__RPC_H__
