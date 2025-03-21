#include "rpc.h"
#include "../status/answer.h"
#include "../utils/log.h"
#include "User/device/gw_gray.h"
#include "User/device/wheel.h"
#include "User/status/cheat_sheet.h"
#include "User/status/record.h"
#include "User/status/status.h"
#include "stdlib.h"

void rpc_register(RPC rpc, uint8_t id, const char *describe,
                  void fn(uint16_t, void *), void *para);
void rpc_declare(RPC rpc);

void set_bool(uint16_t var, void *p) { *(bool *)p = (bool)var; }
void set_int(uint16_t var, void *p) { *(int *)p = (int16_t)var; }
void set_uint(uint16_t var, void *p) { *(unsigned int *)p = (uint16_t)var; }
void set_short(uint16_t var, void *p) { *(short *)p = (int16_t)var; }
void set_ushort(uint16_t var, void *p) { *(unsigned short *)p = (uint16_t)var; }
void set_float(uint16_t var, void *p) {
  *(float *)p = (float)(int16_t)var / 100;
}

/* #define TO_DEVICE INFO */
#define TO_DEVICE SCREEN_PRINT
void get_int(uint16_t var, void *p) { TO_DEVICE("%d", *(int *)p); }
void get_uint(uint16_t var, void *p) { TO_DEVICE("%u", *(unsigned int *)p); }
void get_short(uint16_t var, void *p) { TO_DEVICE("%hd", *(short *)p); }
void get_ushort(uint16_t var, void *p) {
  TO_DEVICE("%hu", *(unsigned short *)p);
}
void get_bool(uint16_t var, void *p) {
  TO_DEVICE("%s", *(bool *)p ? "true" : "false");
}
void get_float(uint16_t var, void *p) { TO_DEVICE("%f", *(float *)p); }

void echo(uint16_t var, void *p) { INFO("ECHO %hx %s", var, p) }

#define SET_VAR_FN(x)                                                          \
  _Generic((x),                                                                \
      int: set_int,                                                            \
      unsigned int: set_uint,                                                  \
      short: set_short,                                                        \
      unsigned short: set_ushort,                                              \
      bool: set_bool,                                                          \
      float: set_float)

#define GET_VAR_FN(x)                                                          \
  _Generic((x),                                                                \
      int: get_int,                                                            \
      unsigned int: get_uint,                                                  \
      short: get_short,                                                        \
      unsigned short: get_ushort,                                              \
      bool: get_bool,                                                          \
      float: get_float)

#define RPC_DECLARE_SET_VAR(id, var)                                           \
  rpc_register(rpc, id, "SET " #var, SET_VAR_FN(var), &var)

#define RPC_DECLARE_GET_VAR(id, var)                                           \
  rpc_register(rpc, id, "GET " #var, GET_VAR_FN(var), &var)

#define RPC_DECLARE_CALL_FN(id, fn, para)                                      \
  rpc_register(rpc, id, "FN " #fn, fn, para)

void task_rpc_init(RPC rpc) {
  INFO("TASK_RPC_INIT.");

  for (unsigned int i = 0; i < TASK_RPC_ID_LIMIT; i++) {
    rpc[i].fn = NULL;
    rpc[i].para = NULL;
  }

  rpc_declare(rpc);
}

void rpc_register(RPC rpc, uint8_t id, const char *describe,
                  void fn(uint16_t remote_var, void *para), void *para) {
  if (id >= TASK_RPC_ID_LIMIT) {
    THROW_WARN("RPC_REGISTER_ERROR id more than or equal to TASK_RPC_ID_LIMIT"
               " (id=%d, TASK_RPC_ID_LIMIT=%d). Will ignore.",
               id, TASK_RPC_ID_LIMIT);
    return;
  }

  if (rpc[id].fn != NULL)
    THROW_WARN("RPC_REGISTER_ERROR redefine id=%d. Will override.", id);

  INFO("RPC_REGISTER id=%d %s", id, describe);
  rpc[id].fn = fn;
  rpc[id].para = para;
}

void rpc_call(struct RemoteProcedure *proc, uint16_t var) {
  proc->fn(var, proc->para);
}

void task_rpc_call_id(RPC rpc, uint8_t id, uint16_t var) {
  if (rpc[id].fn == NULL) {
    THROW_WARN(
        "RPC_CALL_ERROR no register this procedure (id=%d). Will ignore.", id);
    return;
  }

  if (id >= TASK_RPC_ID_LIMIT) {
    THROW_WARN("RPC_CALL_ERROR id more than or equal to TASK_RPC_ID_LIMIT"
               " (id=%d, TASK_RPC_ID_LIMIT=%d). Will ignore.",
               id, TASK_RPC_ID_LIMIT);
    return;
  }

  rpc_call(&rpc[id], var);
}

void set_int_1000_times(uint16_t var, void *p) {
  *(int *)p = (int)(int16_t)var * 1000;
}

void rpc_declare(RPC rpc) {
  /// rpc register var in there.
  /// rpc_register(rpc, 0, "a", store_float, &a);
  /// RPC_DECLARE_SET_VAR(0, a);
  /// RPC_DECLARE_GET_VAR(1, a);
  /// RPC_DECLARE_CALL_FN(2, echo, "Hello World!");
  /* RPC_DECLARE_SET_VAR(0, status.wheels[FONT_LEFT].target); */
  /* RPC_DECLARE_SET_VAR(1, status.wheels[FONT_RIGHT].target); */
  RPC_DECLARE_SET_VAR(0, status.remote_position.forward);
  RPC_DECLARE_SET_VAR(1, status.remote_position.theta);
  RPC_DECLARE_SET_VAR(2, status.dir.target);
  RPC_DECLARE_SET_VAR(3, status.base_speed);
  RPC_DECLARE_SET_VAR(5, status.mode.remote);
  RPC_DECLARE_SET_VAR(6, status.mode.follow);
  RPC_DECLARE_SET_VAR(7, status.mode.turn);
  RPC_DECLARE_SET_VAR(11, status.pid.follow_gw.kp);
  RPC_DECLARE_SET_VAR(12, status.pid.follow_gw.ki);
  RPC_DECLARE_SET_VAR(13, status.pid.follow_gw.kd);
  RPC_DECLARE_SET_VAR(14, status.pid.follow_ms.kp);
  RPC_DECLARE_SET_VAR(15, status.pid.follow_ms.ki);
  RPC_DECLARE_SET_VAR(16, status.pid.follow_ms.kd);
  RPC_DECLARE_SET_VAR(20, status.pid.turn.kp);
  RPC_DECLARE_SET_VAR(21, status.pid.turn.ki);
  RPC_DECLARE_SET_VAR(22, status.pid.turn.kd);

  RPC_DECLARE_GET_VAR(50, status.wheels[FONT_LEFT].history);
  RPC_DECLARE_GET_VAR(51, status.wheels[FONT_RIGHT].history);
  RPC_DECLARE_GET_VAR(52, status.dir.target);
  RPC_DECLARE_GET_VAR(53, status.base_speed);
  RPC_DECLARE_GET_VAR(60, status.pid.follow_gw.kp);
  RPC_DECLARE_GET_VAR(61, status.pid.follow_gw.ki);
  RPC_DECLARE_GET_VAR(62, status.pid.follow_gw.kd);
  RPC_DECLARE_GET_VAR(63, status.pid.turn.kp);
  RPC_DECLARE_GET_VAR(64, status.pid.turn.ki);
  RPC_DECLARE_GET_VAR(65, status.pid.turn.kd);
  RPC_DECLARE_GET_VAR(111, status.pid.follow_ms.kp);
  RPC_DECLARE_GET_VAR(112, status.pid.follow_ms.ki);
  RPC_DECLARE_GET_VAR(113, status.pid.follow_ms.kd);
  RPC_DECLARE_GET_VAR(114, status.cheat_sheet.forward1);
  RPC_DECLARE_GET_VAR(115, status.cheat_sheet.forward2);
  RPC_DECLARE_GET_VAR(116, status.cheat_sheet.arc_continue1);
  RPC_DECLARE_GET_VAR(117, status.cheat_sheet.arc_continue2);

  RPC_DECLARE_GET_VAR(70, status.dir.origin);
  RPC_DECLARE_GET_VAR(71, status.sensor.gyro);

  RPC_DECLARE_SET_VAR(129, status.pid.follow_ms.kp);
  RPC_DECLARE_SET_VAR(130, status.pid.follow_ms.ki);
  RPC_DECLARE_SET_VAR(131, status.pid.follow_ms.kd);
  rpc_register(rpc, 132, "status.cheat_sheet.forward1", set_int_1000_times,
               &status.cheat_sheet.forward1);
  rpc_register(rpc, 133, "status.cheat_sheet.forward2", set_int_1000_times,
               &status.cheat_sheet.forward2);
  rpc_register(rpc, 134, "status.cheat_sheet.arc_continue1", set_int_1000_times,
               &status.cheat_sheet.arc_continue1);
  rpc_register(rpc, 135, "status.cheat_sheet.arc_continue2", set_int_1000_times,
               &status.cheat_sheet.arc_continue2);
  RPC_DECLARE_CALL_FN(88, cheat_sheet_rpc_recover, NULL);

  RPC_DECLARE_CALL_FN(100, echo, "hello");
  RPC_DECLARE_CALL_FN(101, record_once_switch, NULL);
  RPC_DECLARE_CALL_FN(102, repeat_open, NULL);

  RPC_DECLARE_CALL_FN(153, answer_select_rpc, NULL);
}
