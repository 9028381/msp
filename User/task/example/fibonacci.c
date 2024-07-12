#include "fibonacci.h"
#include "../../utils/log.h"
#include "../task.h"

/* fibonacci times=4
 * para:  0 fib(n) fib(n-1) times
 * para:  0 1 0 4
 * para:  0 1 1 3
 * para:  0 2 1 2
 * para:  0 3 2 1
 * para:  0 5 3 0
 */
void fibonacci_timed_next(void *para) {
  uint32_t data = (uint32_t)para;

  uint8_t times = data & 0xff;
  uint8_t fib1 = (data >> 8) & 0xff;
  uint8_t fib2 = (data >> 16) & 0xff;

  PRINTLN("%d", fib2);

  times -= 1;
  if (times == 0)
    return;

  uint8_t fib3 = fib1 + fib2;

  data = (fib3 << 16) | (fib2 << 8) | times;

  Task t = task_new(fibonacci_timed_next, (void *)data);
  task_timed_append(&task.timed, t, fib2);
}

void fibonacci_timed_print(unsigned int later, uint8_t times) {
  uint32_t para = (1 << 16) | (0 << 8) | times;
  Task t = task_new(fibonacci_timed_next, (void *)para);
  task_timed_append(&task.timed, t, later);
}
