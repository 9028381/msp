#include "User/status/rpc.h"
#include "../utils/log.h"
#include "User/status/wheel.h"
#include "status.h"
#include "stdlib.h"
#include "wheel.h"

void rpc_register(RPC rpc, uint8_t id, const char *describe,
                  void fn(uint16_t, void *), void *para);

void set_int(uint16_t var, void *p) { *(int *)p = (int16_t)var; }
void set_uint(uint16_t var, void *p) { *(unsigned int *)p = (uint16_t)var; }
void set_short(uint16_t var, void *p) { *(short *)p = (int16_t)var; }
void set_ushort(uint16_t var, void *p) { *(unsigned short *)p = (uint16_t)var; }
void set_float(uint16_t var, void *p) {
  *(float *)p = (float)(int16_t)var / 1000;
}

void get_int(uint16_t var, void *p) { INFO("GET %d", *(int *)p); }
void get_uint(uint16_t var, void *p) { INFO("GET %u", *(unsigned int *)p); }
void get_short(uint16_t var, void *p) { INFO("GET %hd", *(short *)p); }
void get_ushort(uint16_t var, void *p) {
  INFO("GET %hu", *(unsigned short *)p);
}
void get_float(uint16_t var, void *p) { INFO("GET %f", *(float *)p); }

void echo(uint16_t var, void *p) { INFO("ECHO %hx %s", var, p) }

#define SET_VAR_FN(x)                                                          \
  _Generic((x),                                                                \
      int: set_int,                                                            \
      unsigned int: set_uint,                                                  \
      short: set_short,                                                        \
      unsigned short: set_ushort,                                              \
      float: set_float)

#define GET_VAR_FN(x)                                                          \
  _Generic((x),                                                                \
      int: get_int,                                                            \
      unsigned int: get_uint,                                                  \
      short: get_short,                                                        \
      unsigned short: get_ushort,                                              \
      float: get_float)

#define RPC_DECLARE_SET_VAR(id, var)                                           \
  rpc_register(rpc, id, "SET " #var, SET_VAR_FN(var), &var)

#define RPC_DECLARE_GET_VAR(id, var)                                           \
  rpc_register(rpc, id, "GET " #var, GET_VAR_FN(var), &var)

#define RPC_DECLARE_CALL_FN(id, fn, para)                                      \
  rpc_register(rpc, id, "FN " #fn, fn, para)

void rpc_declare(RPC rpc) {
  /// rpc register var in there.
  /// rpc_register(rpc, 0, "a", store_float, &a);
  /// RPC_DECLARE_SET_VAR(0, a);
  /// RPC_DECLARE_GET_VAR(1, a);
  /// RPC_DECLARE_CALL_FN(2, echo, "Hello World!");
  RPC_DECLARE_SET_VAR(0, status.wheels[FONT_LEFT].target);
  RPC_DECLARE_SET_VAR(1, status.wheels[FONT_RIGHT].target);
}

void status_rpc_init(RPC rpc) {
  INFO("rpc init.");

  for (unsigned int i = 0; i < STATUS_RPC_ID_LIMIT; i++) {
    rpc[i].fn = NULL;
    rpc[i].para = NULL;
  }

  rpc_declare(rpc);
}

void rpc_register(RPC rpc, uint8_t id, const char *describe,
                  void fn(uint16_t, void *), void *para) {
  if (id >= STATUS_RPC_ID_LIMIT) {
    THROW_ERROR(
        "RPC_REGISTER_ERROR id more than or equal to STATUS_RPC_ID_LIMIT "
        "(id=%d, STATUS_RPC_ID_LIMIT=%d). Will ignore.",
        id, STATUS_RPC_ID_LIMIT);
    return;
  }

  if (rpc[id].fn != NULL)
    THROW_ERROR("RPC_REGISTER_ERROR redefine id=%d. Will override.", id);

  INFO("PRC_REGISTER id=%d %s", id, describe);
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

  if (id >= STATUS_RPC_ID_LIMIT) {
    THROW_ERROR("RPC_CALL_ERROR id more than or equal to STATUS_RPC_ID_LIMIT"
                "(id=%d, STATUS_RPC_ID_LIMIT=%d). Will ignore.",
                id, STATUS_RPC_ID_LIMIT);
    return;
  }

  rpc_call(&rpc[id], var);
}
