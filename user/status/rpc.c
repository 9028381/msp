#include "rpc.h"
#include "../utils/log.h"
#include "User/status/wheel.h"
#include "status.h"
#include "stdlib.h"
#include "wheel.h"


void rpc_register(RPC rpc, uint8_t id, const char *describe,
                  void fn(uint16_t, void *), void *para);

void store_uint(uint16_t var, void *p) { *(unsigned int *)p = var; }
void store_int(uint16_t var, void *p) { *(int *)p = (int16_t)var; }
void store_short(uint16_t var, void *p) { *(short *)p = (int16_t)var; }
void store_float(uint16_t var, void *p) {
  *(float *)p = (float)(int16_t)var / 1000;
}

#define STORE_VAR(x)                                                           \
  _Generic((x), int: store_int, float: store_float, unsigned int: store_uint, short: store_short)

#define RPC_DECLARE_VAR(id, var)                                               \
  rpc_register(rpc, id, #var, STORE_VAR(var), &var)

void rpc_declare(RPC rpc) {
  // rpc register var in there.
  // rpc_register(rpc, 0, "a", store_float, &a);
  // RPC_DECLARE_VAR(0, status.wheels[FONT_LEFT].target);
	// void *p = NULL; //&status.wheels[FONT_LEFT].target;
	// TRACE(p, "%p");
	// rpc_register(rpc, 0, "target", store_short, p);
	RPC_DECLARE_VAR(0, status.wheels[FONT_LEFT].target);
    RPC_DECLARE_VAR(1, status.wheels[FONT_RIGHT].target);
}

void status_rpc_init(RPC rpc) {
  INFO("rpc init.");

  for (unsigned int i = 0; i < STATUS_RPC_ID_MAX; i++) {
    rpc[i].fn = NULL;
    rpc[i].para = NULL;
  }

  rpc_declare(rpc);
}

void rpc_register(RPC rpc, uint8_t id, const char *describe,
                  void fn(uint16_t, void *), void *para) {
  // do something
  if (id >= STATUS_RPC_ID_MAX) {
    THROW_ERROR("RPC_REGISTER_ERROR id more than or equal to STATUS_RPC_ID_MAX "
                "(id=%d, STATUS_RPC_ID_MAX=%d). Will ignore.",
                id, STATUS_RPC_ID_MAX);
    return;
  }

  if (rpc[id].fn != NULL)
    THROW_ERROR("RPC_REGISTER_ERROR redefine id=%d. Will override.", id);

  INFO("PRC register id=%d describe=%s", id, describe);
  rpc[id].fn = fn;
  rpc[id].para = para;
}

void rpc_call(struct Procedure *proc, uint16_t var) {
  proc->fn(var, proc->para);
}

void rpc_call_id(RPC rpc, uint8_t id, uint16_t var) {
  if (rpc[id].fn == NULL) {
    THROW_ERROR(
        "RPC_CALL_ERROR no register this procedure (id=%d). Will ignore.", id);
    return;
  }
  rpc_call(&rpc[id], var);
}
