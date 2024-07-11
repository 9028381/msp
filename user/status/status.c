/*
 * @Author: zl 2293721550@qq.com
 * @Date: 2024-07-09 17:16:47
 * @LastEditors: zl 2293721550@qq.com
 * @LastEditTime: 2024-07-11 14:11:48
 * @FilePath: \workspace_ccstheia\empty_LP_MSPM0G3507_nortos_ticlang\User\status\status.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "status.h"
#include "rpc.h"

struct Status status;

void status_init(struct Status *status) {
  status->times = 0;
  status_rpc_init(status->rpc);
  // sensor init
  status_wheels_init(status->wheels);
}

void status_next(struct Status *status) {
  status->times++;
  // sensor next
  status_wheels_next(status->wheels);
}

void status_drive(struct Status *status) {
  status_wheels_drive(status->wheels);
}
